#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "AnomalyDetector.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
//#include <cmath>
#include <iomanip>
#include <stdio.h>

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};
// you may add here helper classes
class ad_upperclass{
	public:
	HybridAnomalyDetector ad;
	vector<AnomalyReport> r;
	
};

// you may edit this class
class Command{ 
	protected:
		DefaultIO* dio;
		HybridAnomalyDetector* ad;
		vector<AnomalyReport>*r;
public:
	Command(DefaultIO* dio,ad_upperclass& global_ad_get):dio(dio),ad(&global_ad_get.ad),r(&global_ad_get.r){
		}
	virtual void execute()=0;
	virtual ~Command(){}
};

//Here goes the command classes :)
class Upload_csv: public Command{
	public:
	Upload_csv(DefaultIO *dio,ad_upperclass& global_ad):Command(dio,global_ad){}
	void execute()override {
	dio->write("Please upload your local train CSV file.");
	string k="";
	ofstream anomalyTrain ("anomalyTrain.csv");   
	k = dio->read();
    while(k!="done") {
        anomalyTrain << k << "\n";
		k = dio->read(); }
    anomalyTrain.close();
	dio->write("Upload complete.");
	dio->write("Please upload your local test CSV file.");
	ofstream anomalyTest ("anomalyTest.csv");   
	k = dio->read();
	
    while(k!="done"){
        anomalyTest << k << "\n";
		k = dio->read(); }
	dio->write("Upload complete.");
	anomalyTest.close();

	dio->write("Welcome to the Anomaly Detection Server.\n"
                "Please choose an option:\n"
                "1.upload a time series csv file\n"
                "2.algorithm settings\n"
                "3.detect anomalies\n"
                "4.display results\n"
                "5.upload anomalies and analyze results\n"
                "6.exit");


};
};

class change_threshold: public Command {
	public:
	change_threshold(DefaultIO *dio,ad_upperclass& global_ad):Command(dio,global_ad){}
	
	void execute()override {
		dio->write("The current correlation threshold is 0.9\n"
                    "Type a new threshold\n");

		string k="";
		double threshold=0;
		while((0>=threshold) || (threshold>=1)){
		k = dio->read();
		threshold=stod(k);
			if (stoi(k)<0 ||stoi(k)>1)
			{
				dio->write("please choose a value between 0 and 1.");
			}
		}
									
		ad->set_threshod(threshold);
		dio->write("Welcome to the Anomaly Detection Server.\n"
                "Please choose an option:\n"
                "1.upload a time series csv file\n"
                "2.algorithm settings\n"
                "3.detect anomalies\n"
                "4.display results\n"
                "5.upload anomalies and analyze results\n"
                "6.exit\n");		
		
	};
};

class run_csv: public Command {
	public:
	run_csv(DefaultIO *dio,ad_upperclass& global_ad):Command(dio,global_ad){}
	
	void execute()override {
		
		TimeSeries ts("anomalyTrain.csv");
		ad->learnNormal(ts);
		TimeSeries ts2("anomalyTest.csv");
		*r = ad->detect(ts2); 
		dio->write("anomaly detection complete.");
		dio->write("Welcome to the Anomaly Detection Server.\n"
                "Please choose an option:\n"
                "1.upload a time series csv file\n"
                "2.algorithm settings\n"
                "3.detect anomalies\n"
                "4.display results\n"
                "5.upload anomalies and analyze results\n"
                "6.exit\n");

	};
};
class get_anomalies: public Command {

	public:
	get_anomalies(DefaultIO *dio,ad_upperclass& global_ad):Command(dio,global_ad){}
	
	void execute()override {
		string temp="";
		for (AnomalyReport i: *r)
		{			
		string step_data = to_string(i.timeStep);
		string description_data =i.description;
		string concat= step_data+"\t"+description_data+"\n";
		dio->write(concat);
		}
		dio->write("Done.\n");
		dio->write("Welcome to the Anomaly Detection Server.\n"
                "Please choose an option:\n"
                "1.upload a time series csv file\n"
                "2.algorithm settings\n"
                "3.detect anomalies\n"
                "4.display results\n"
                "5.upload anomalies and analyze results\n"
                "6.exit\n");
	};
};
class zip {
	public:
		int str = 0;
		const string comma =",";
		int end = 0;
	zip(int thestr,int theend):str(thestr),end(theend){}
};

class anomalies_time_step: public Command {
	public:
	anomalies_time_step(DefaultIO *dio,ad_upperclass& global_ad):Command(dio,global_ad){}
	
	void execute()override {
		long ts_start = 0, current_start = -1;
		long ts_end = 0;
		string current_features ="";
		bool current_ts=true;
		
		vector <zip> ziped_ar;
		int counter=0;
		for (AnomalyReport i: *r)
		{	
			if(current_ts==true){
				ts_start=i.timeStep;
				current_features=i.description;
				current_ts=false;
				ts_end=ts_start;
				if(current_start!=-1){
					ts_start=current_start;
					counter+=1;
				}
			}
			else if(current_features==i.description){
				if((ts_start+1)==(i.timeStep-counter)){
					ts_end=i.timeStep;
					counter+=1;
				}
			}
			else{
				zip temp=(zip(ts_start,ts_end));
				ziped_ar.push_back(temp);
				current_ts=true;
				counter=0;
				current_start=i.timeStep;
			}
		}
		zip temp2=(zip(ts_start,ts_end));
		ziped_ar.push_back(temp2); //133 instead of 134!!!!!!!!!!!!
		
		
		string k="";
		k = dio->read();
		vector <zip> client_data;
    	string delimiter = ",";
		size_t pos = 0;
		long ts_start_byclient=0,ts_end_byclient=0;
		string start = "",end = "";
		//dio->write("Please upload your local anomalies file.");
		while(k!="done")
		{
		start = k.substr(0, k.find(delimiter));
		int sz=k.size();
		int coma_loc=k.find_first_of(",");
		for (int z = 0; z < (1+coma_loc); z++)
		{
			k.erase(0, pos + delimiter.length());
		}

		end = k.substr(0, k.find(delimiter));
		ts_start_byclient=stol(start);
		ts_end_byclient=stol(end);
		zip temp3=(zip(ts_start_byclient,ts_end_byclient));
        client_data.push_back(temp3);
		k = dio->read(); 
		}
		dio->write("Upload complete.");
		
		int P = client_data.size(); //num of deviations
		int N=0;
		int time_steps_overall=0;
		for (int i = 0; i < P; i++)
		{
		 time_steps_overall+=(int(client_data[i].end)-int(client_data[i].str))+1;
		}
		int numLines = 0;
		ifstream in("anomalyTest.csv");
		string unused;
		while (getline(in, unused))
			++numLines;

		N = numLines-time_steps_overall-1;
		int TP=0,FP=0;
		bool check_if_correct=false;
		for (int i = 0; i < ziped_ar.size(); i++) //real anomalies
		{
			for (int j = 0; j < P; j++) //anomalies from client
			{
				if((ziped_ar[i].end<client_data[j].str||ziped_ar[i].str>client_data[j].end)&&(check_if_correct != true)){
					check_if_correct = false;
				}
				else {
					check_if_correct = true;
				}
			}
			if(check_if_correct==true){
				TP+=1;
				check_if_correct=false;
			}
			else
			{
				FP+=1;
			}
		}
		//double True_positive_rate = double((int(1000*(double(TP) / double(P)))))/1000;
		//double False_alarm_rate = double((int(1000*(double(FP) / double(N)))))/1000;

		char buffer1 [10];
		sprintf (buffer1, "%.4lf\n",(double(TP) / double(P)));

		char buffer2 [10];
		sprintf (buffer2, "%.4lf\n",(double(FP)/double(N)));

		buffer1[5]=0;
		string temp_Tpr(buffer1);
		/*if(stof(temp_Tpr)==0.0){
			temp_Tpr="0" ;
		}*/
		buffer2[5]=0;
		string temp_Far(buffer2);
		/*if(stof(temp_Far)==0.0){
			temp_Far="0" ;
		}*/
		while(temp_Far.find(".")!=string::npos && temp_Far.substr( temp_Far.length() - 1, 1) == "0" || temp_Far.substr( temp_Far.length() - 1, 1) == "." )
		{
		temp_Far.pop_back();
		}
		while(temp_Tpr.find(".")!=string::npos && temp_Tpr.substr(temp_Tpr.length() - 1, 1) == "0" || temp_Tpr.substr(temp_Tpr.length() - 1, 1) == "." )
		{
		temp_Tpr.pop_back();
		}
		


		string temp_concat1 = "True Positive Rate: " + temp_Tpr +"\n";
		string temp_concat2 = "False Positive Rate: " + temp_Far;
		string conctemp=temp_concat1+temp_concat2;
		dio->write(conctemp);
		/*
		True Positive Rate: 0
		False Positive Rate: 0.015*/

		dio->write("Welcome to the Anomaly Detection Server.\n"
                "Please choose an option:\n"
                "1.upload a time series csv file\n"
                "2.algorithm settings\n"
                "3.detect anomalies\n"
                "4.display results\n"
                "5.upload anomalies and analyze results\n"
                "6.exit\n");
	};
};
#endif /* COMMANDS_H_ */