#include <sstream>
#include "minCircle.h"
#include "HybridAnomalyDetector.h"
HybridAnomalyDetector::HybridAnomalyDetector(){
	//cout<<threshold<<"here I am"<<endl;
}
HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

// Function to return the euclidean distance 
// between two points 
double dist(Point& a, Point& b) 
{ 
    return sqrt(pow(a.x - b.x, 2) 
                + pow(a.y - b.y, 2)); 
} 

/*void set_threshod(double new_threshold){
	HybridAnomalyDetector k;
	k.set_threshod(f);
	threshold=new_threshold;
}*/


void array_creation_from_vec2(const TimeSeries& ts, int index_table, float* array_column) {
	if (ts.m_ts_data_union.m_flight_data.empty()){
		return;	
	}
int vec_size = ts.m_ts_data_union.m_flight_data.size();

for (int i = 0; i < vec_size; i++)
	{
		float j=ts.m_ts_data_union.m_flight_data.at(i).at(index_table);
		*(array_column+i)=j;
		//cout<< *(array_column+i)<<endl;
	}
}
float temp_dev=0, max_dev=0;
bool corelated_higher_than_circle=false;
Point a=Point (0.f,0.f);
bool circle_time=false;
void HybridAnomalyDetector::learnNormal(const TimeSeries& ts){
	//cout<<"simple Hybrid anomaly cpp start work ok"<<endl;
	// learn normal and fill m_flight_data_normal
	// first, using func to get array of column in ts, while send arg as vec column and index.
	int vec_size = ts.m_ts_data_union.m_flight_data.size();
	
	float *column_arr1 = new float [vec_size];
	float *current1 = new float [vec_size];
	//float *column_arr1{ new float[vec_size]};
	float *column_arr2 = new float [vec_size];
	float *current2 = new float [vec_size];
	Line the_lnr_f;

	int vec_size_to_pearson=ts.m_ts_data_union.m_flight_data.size();
	float highest_coreltaion=0, temp_corelation=0;
	int index_feature1=0, index_feature2=0;
	int no_offeatures = ts.m_ts_data_union.m_flight_data[0].size();

	for (int i = 0; i < no_offeatures - 1; i++) {
		array_creation_from_vec2(ts,  i, column_arr1);
		
		for (int j = i+1; j < no_offeatures; j++) {
			array_creation_from_vec2(ts,  j, column_arr2);
			temp_corelation=pearson(column_arr1,column_arr2,vec_size_to_pearson);
			if((abs(temp_corelation)>abs(highest_coreltaion)) && (abs(temp_corelation) >= this->threshold)) {
				array_creation_from_vec2(ts, i, current1);
				array_creation_from_vec2(ts, j, current2);
				highest_coreltaion = temp_corelation;
				index_feature1=i;
				index_feature2=j;
				corelated_higher_than_circle=true;	
				}
			else if((abs(temp_corelation)>abs(highest_coreltaion)) && ((abs(temp_corelation) > 0.5) &&(abs(temp_corelation) < this->threshold)) && (corelated_higher_than_circle==false)) {
				array_creation_from_vec2(ts, i, current1);
				array_creation_from_vec2(ts, j, current2);
				highest_coreltaion = temp_corelation;
				index_feature1=i;
				index_feature2=j;	
				circle_time=true;
				}

		} 
		Point** lr = new Point*[vec_size_to_pearson];
		
		for(int i = 0; i < vec_size_to_pearson; i++) {
			Point *temp_p=new Point(current1[i],current2[i]);
			lr[i]=temp_p;
			}
		if(corelated_higher_than_circle==true){
			the_lnr_f=linear_reg (lr,vec_size_to_pearson);
		temp_dev=0, max_dev=0;
		for (int n = 0; n < vec_size_to_pearson; n++)
		{		
			temp_dev=abs(dev(*lr[n], lr, vec_size_to_pearson));
			if(temp_dev>max_dev){
				max_dev=temp_dev;
			}
		}
		}
		else if ((corelated_higher_than_circle==false)&&(circle_time==true)){
			Circle ans=findMinCircle(lr,vec_size_to_pearson);
			
			max_dev=ans.radius*0.9;
			a=ans.center;
		}
		correlatedFeatures the_features{.feature1=
		ts.m_ts_data_union.m_flight_data_headers[index_feature1],
		.feature2=ts.m_ts_data_union.m_flight_data_headers[index_feature2]
		,.corrlation=highest_coreltaion,.lin_reg=the_lnr_f,.threshold=1.2f*max_dev,.circle_mid_point=a};
		
		for(int i=0;i<vec_size_to_pearson;i++) {
				delete lr[i]; }
			delete [] lr;
			if(highest_coreltaion!=0) {
			cf.push_back(the_features); 
			highest_coreltaion=0; }
			circle_time=false;
			corelated_higher_than_circle=false;
			the_lnr_f=Line(0.f,0.f);
	}
	
	delete[] column_arr1;
	delete[] column_arr2;
	delete[] current1;
	delete[] current2;
//cout<<"simple anomaly cpp end work ok"<<endl;
}
vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries& ts)
{
	//cout<<"detect cpp start work ok"<<endl;
	std::vector<AnomalyReport> report_anumaly_vec;

	//#### checking with vec cf if anomaly with ts2 ####
	//get ts row lengh & column, for each line, get column var, check if ok (under threshold)
	//if not ok, fill Vec _anomaly

	//define vector of row
	vector<float> row_data_detect;
	vector<string> row_data_str_tetect;
	float feature1_det=0, feature2_det=0;
	//string detect_str_of_features;
	float detect_dev_check=0;
	// Create an input filestream
	char delimiter =',';
	//std::ifstream file_test(ts);
	int vec_size1 = ts.m_ts_data_union.m_flight_data.size();
	
	std::string str_det;
	bool k = true;
	int cf_lengh=0;
	if (!cf.empty()){		
		cf_lengh = cf.size();
	}		
	
	int time_step_detect=1;

	for (int i = 0; i < vec_size1; i++)
	{
	vector<float> j=ts.m_ts_data_union.m_flight_data.at(i);
		//std::cout << str_det << "\n"; 
		//row_data_str_tetect = split_det (str_det, delimiter);  
		int row_size=0;
		for (int o = 0; o < j.size()-1; o++) {      
				{
			feature1_det = j.at(o); 
			}
			for (int p = o+1; p < j.size(); p++) {      
						{
					feature2_det = j.at(p); 
					}
					for (int q = 0; q < cf_lengh; q++)
					{
						if(cf.at(q).feature1 == ts.m_ts_data_union.m_flight_data_headers.at(o)
						&& cf.at(q).feature2 == ts.m_ts_data_union.m_flight_data_headers.at(p)) {
							Point *check_detec = new Point(feature1_det,feature2_det);
							if(cf.at(q).corrlation>=this->threshold){
								detect_dev_check=abs(dev(*check_detec,cf.at(q).lin_reg));
								
								if(detect_dev_check>cf.at(q).threshold) {	
									stringstream detect_str_of_features;
									detect_str_of_features<<ts.m_ts_data_union.m_flight_data_headers.at(o)<<"-"<<
									ts.m_ts_data_union.m_flight_data_headers.at(p);
									
									AnomalyReport the_dev={detect_str_of_features.str(),time_step_detect};
									report_anumaly_vec.push_back(the_dev);
								}							
								delete check_detec;
							}
							else if ((cf.at(q).corrlation>0.5) &&(cf.at(q).corrlation<this->threshold))
							{
								detect_dev_check=dist(*check_detec,cf.at(q).circle_mid_point);
							if(detect_dev_check>cf.at(q).threshold) {	
									stringstream detect_str_of_features;
									detect_str_of_features<<ts.m_ts_data_union.m_flight_data_headers.at(o)<<"-"<<
									ts.m_ts_data_union.m_flight_data_headers.at(p);
									
									AnomalyReport the_dev={detect_str_of_features.str(),time_step_detect};
									report_anumaly_vec.push_back(the_dev);
								}							
								delete check_detec;
							}
						}
				}		
			}
		}
		time_step_detect+=1; //check - each next row do +1; &&&&&&&&&&&&&
	}
//cout<<"detect  end worked fine"<<endl;
return report_anumaly_vec;
}