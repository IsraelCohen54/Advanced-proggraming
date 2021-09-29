#include "CLI.h"
#include <string>
#include <iostream> 
#include <sstream> 

CLI::CLI(DefaultIO* dio) {
    this->dio=dio;
}
void CLI::start(){
    string end="6";
    dio->write("Welcome to the Anomaly Detection Server.\n"
                "Please choose an option:\n"
                "1.upload a time series csv file\n"
                "2.algorithm settings\n"
                "3.detect anomalies\n"
                "4.display results\n"
                "5.upload anomalies and analyze results\n"
                "6.exit");
    Upload_csv *upload;
    change_threshold *change_threshold_by_input;
    run_csv *train_detect;
    get_anomalies *the_anomalieas;
    //HybridAnomalyDetector global_ad;
    ad_upperclass global_ad;
    anomalies_time_step *report_from_client;
    while(true)
    {
        
        string line = dio->read();
        if (line!="6")
        {
            int choose=stoi(line);
            switch(choose) {
                case 1:
                    //cout<<"num1\n";
                    upload=new Upload_csv(dio,global_ad);
                    upload->execute();    
                    delete upload;
                    break;
                case 2:
                    //cout<<"num2\n";
                    change_threshold_by_input=new change_threshold(dio,global_ad);
                    change_threshold_by_input->execute();
                    delete change_threshold_by_input;
                    break;
                case 3:
                    //cout<<"num3\n";
                    train_detect=new run_csv(dio,global_ad);
                    train_detect->execute();
                    delete train_detect;
                    break;
                case 4:
                    //cout<<"num4\n";
                    the_anomalieas=new get_anomalies(dio,global_ad);
                    the_anomalieas->execute();
                    delete the_anomalieas;
                    break;
                case 5:
                    report_from_client=new anomalies_time_step(dio,global_ad);
                    report_from_client->execute();
                    delete report_from_client;
                    //break;
                default:
                    continue;
            }
        }
        if (line=="6")
        {
            break;
        }
    }
}

CLI::~CLI() {
}

