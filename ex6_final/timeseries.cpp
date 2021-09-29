#include "timeseries.h"
//#include <iostream>
//#include <fstream>
//#include <string.h>
//#include <vector>
//#include <iterator>
#include <regex>

/*
 *      Author: Israel
 */

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;
try
{
  /* code */

    while (getline (ss, item, delim)) {
        result.push_back (item);
    } 
}
catch(const std::exception& e)
{
  std::cerr << e.what() <<"split line simple check" <<'\n';
}
    return result;
}

TimeSeries::TimeSeries(const char* CSVfileName){
//define vector of row
//cout<<"constructor TS start"<<endl;
vector<float> row_data;
vector<string> row_data_str;
// Create an input filestream
 char delimiter=',';
 //cout<<"constructor TS *1* start"<<endl;
  ifstream file(CSVfileName);
  //cout<<"constructor TS *2* start"<<endl;
  string str;
  bool k = true;
  try
  {
  //cout<<" BEFORE WHILE t.s .h class while goes fine "<<endl;
  while (std::getline(file, str)) {
    
    if (!row_data.empty()) {
      row_data.clear();
    }
    //std::cout << str << "\n"; //delete it at end %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    row_data_str = split (str, delimiter); 
    if(row_data_str.empty()) {
      continue;
    }
    int row_size = row_data_str.size();
    try
    {
      /* code */
    if (k==true)
      {
        k=false;  
        try
        {
          /* code */
        
        for (int i = 0; i < row_size; i++) {     
          string k = row_data_str.at(i); 
          m_ts_data_union.m_flight_data_headers.push_back(k);
        }
        
        }
        catch(const std::exception& e)
        {
          std::cerr << e.what() <<"inner for loop check ts.cpp" <<'\n';
        }
        continue;
      }
      
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() <<"check the if for in t.s.g cpp" <<'\n';
    }
      try
      {
        /* code */
      
    for (int i = 0; i < row_size; i++) {      
      row_data.push_back(stof(row_data_str.at(i))); }
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() <<"for loop in t.s.cpp ident1" <<'\n';
      }
    m_ts_data_union.m_flight_data.push_back(row_data);    
  }
  /* code */
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() <<"time series data generation func cpp, while loop" <<'\n';
  }
  //cout<<" after WHILE t.s .h class while goes fine "<<endl;
}