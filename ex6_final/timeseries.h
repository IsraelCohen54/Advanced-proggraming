#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class TimeSeries{

public: 

	TimeSeries(const char* CSVfileName) ;	
	// store the result
 
	struct ts_WHeaders
	{
	std::vector<string> m_flight_data_headers;
	std::vector<std::vector<float>> m_flight_data;

	//float * m_arrayOfFlopats2D;
	} m_ts_data_union;


	//trying to announce getdata func
	//getdata(vector<vector<float>>m_flight_data);
	//void vector<vector<float>> get_data();
	//vector<vector<float>>& get_data();
};
#endif /* TIMESERIES_H_ */
