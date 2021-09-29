/*
 *      Author: Israel
 */
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>
using namespace std;

// Function to find mean and return it
float mean(float arr[], int n) 
{ 
    float avg = 0; 
    try
    {
        /* code */
    
    for(int i = 0; i < n; i++) 
        avg = avg + arr[i]; 
    return (avg / n); 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() <<"float mean util.cpp" <<'\n';
    }
}
// returns the variance of X and Y
float var(float* x, int size) { //float point to array, size goes for array boundaries
    float theMean = 0, sumArrayCellsSquared = 0, var = 0;
theMean = mean(x,size);
try
{
    /* code */
//compute sum squared, differences with mean
for (int i = 0; i < size; i++)
{
    sumArrayCellsSquared = sumArrayCellsSquared + x[i] * x[i]; 
}
float temp = sumArrayCellsSquared / size;
var = temp - (theMean * theMean);
return var;

}
catch(const std::exception& e)
{
    std::cerr << e.what() <<"check var util prob" <<'\n';
}
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
float sum = 0,xSum=0, ySum=0; 
try
{
    /* code */

for(int i = 0; i < size; i++)  {
        sum = sum + (x[i] - mean(x, size))*(y[i] - mean(y, size));
        }
}
catch(const std::exception& e)
{
    std::cerr << e.what() << "check cov indic XCV utic cpp"<<'\n';
}
return (sum / (size));
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
return (cov(x,y,size)/(sqrt((var(x,size))*(var(y,size)))));
}
// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size) {
    float a = 0, b = 0;
    float arrX[size], arrY[size]; //make 2 arrays for all the points - one for x one for y to use Cov func
    try
    {
        /* code */
    for (int i = 0; i < size; i++) {
        //arrX[i]=*(points+i)->x;//here is the prob! meybe check with someone why it didnt work
        //k=*points[i];
        //arrY[i]=points[i]->y;
        //Point k = points(i);
        arrX[i] = points[i]->x;
        arrY[i] = points[i]->y;
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() <<"lin_reg_basic creation util.cpp" <<'\n';
    }
    try
    {
        /* code */
    
    a = (cov(arrX,arrY,size))/(var(arrX,size));
    b = mean(arrY,size) - a * mean(arrX,size);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() <<"base lin reg 2 check util.cpp"<< '\n';
    }
    return Line(a,b);
}
// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size) {
    Line lineFromPoints = linear_reg (points,size);
    return dev(p, lineFromPoints);
}

// returns the deviation between point p and the line
float dev(Point p,Line l) {
    float yValueOfLine = l.f(p.x); //getting the Y value for X as it should be at Y axis on the line
    return (abs(yValueOfLine - (p.y))); //getting the deviation in Y axis
}
//check the progg with values:
/*
bool wrong(float val, float expected){
	return val<expected-0.001 || val>expected+0.001;
}*/
//my function checker: //************************remember deleate it!!!!!!!!!*******************\\//
/*int main(){
    const int N=10;
	float x[]={1,2,3,4,5,6,7,8,9,10};
	float y[]={2.1,4.2,6.1,8.1,10.3,12.2,14.4,16.1,18.2,20.3};
    cout<<"avg func is: "<<mean(x, 10)<<endl;
    cout<<"var is: "<<var(x,10)<<endl;
    cout<<"cov is: "<<cov(x,y,N)<<endl;
}*/


/////\\ this is a simple test to put you on the right track\\\\\//
/*int main(){
	const int N=10;
	float x[]={1,2,3,4,5,6,7,8,9,10};
	float y[]={2.1,4.2,6.1,8.1,10.3,12.2,14.4,16.1,18.2,20.3};

	Point* ps[N];
	for(int i=0;i<N;i++)
		ps[i]=new Point(x[i],y[i]);

	Line l=linear_reg(ps,N);
	Point p(4,8);

	float v[]={var(x,N),cov(x,y,N),pearson(x,y,N),l.a,l.b,l.f(4),dev(p,l)};
	float e[]={8.25,16.63,0.999,2.015,0.113,8.176,0.176};

	for(int i=0;i<7;i++)
		if(wrong(v[i],e[i]))
			cout<<"error for check "<<i<<" (-14)"<<endl;

	for(int i=0;i<N;i++)
		delete ps[i];

	cout<<"done"<<endl;
	return 0;
}*/