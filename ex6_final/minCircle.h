#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------
//class Point{
//public:
//	float x,y;
//	Point(float x,float y):x(x),y(y){}
//};

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle from2points(Point a,Point b);

//Point circumcenter(Point b, Point c); //??? uneeded as I return min circle immedietly

Circle from3Points(Point a, Point b, Point c);

Circle min_circle_trivial(vector<Point>& P);

Circle welzlAlgorithm(Point** P,vector<Point> R, size_t n);

Circle findMinCircle(Point** points,int size);

//Circle get_circle_center(const Point& A, const Point& B,const Point& C);

//Circle findMinCircle(Point** points, size_t size);

#endif /* MINCIRCLE_H_ */