#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
protected: 
	double threshold = 0.9;
	
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
	void set_threshod(double new_threshold){
		this->threshold=new_threshold;
	}
	double get_threshod(){
		return this->threshold;
	}
};
#endif /* HYBRIDANOMALYDETECTOR_H_ */