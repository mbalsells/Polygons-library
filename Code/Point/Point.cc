#include <iostream>
#include <cmath>
#include "Point.hh"

using namespace std;


bool Point::operator < (const Point& a) const{
	if (x != a.getx()) return x < a.getx();
	return y < a.gety();
}

bool Point::operator == (const Point& a) const{
	if (abs(x - a.getx()) > epsilon) return false;
	if (abs(y - a.gety()) > epsilon) return false;
	
	return true;
}

bool Point::operator != (const Point& a) const{
	if (abs(x - a.getx()) > epsilon) return true;
	if (abs(y - a.gety()) > epsilon) return true;
	
	return false;
}

double Point::slope(const Point a) const {
	//if a.getx() == x it will return infinity
	return (a.gety() - y)/(a.getx() - x);
}

bool Point::clockwise(const Point b, const Point c) const{
	//also returns false if aligned
	return (b.getx() - x)*(c.gety() - y) <  (c.getx() - x)*(b.gety() - y);
}


double Point::distance(const Point a) const{
	return sqrt((a.getx() - x)*(a.getx() - x) + (a.gety() - y)*(a.gety() - y));
}

Point Point::cross (const Point a, const Point b, const Point c) const {
	//the solpes of the two lines that the points determine
	double slope1 = slope(a);
	double slope2 = b.slope(c); 

	//if the lines are paralel they dont cross
	if (abs(slope1 - slope2) < epsilon) return Point(INF, INF);

	//get the n such that y = slope*x + n are the equations of the line
	double n1 = a.gety() - slope1*a.getx();
	double n2 = c.gety() - slope2*c.getx();

	//if one of the lines is vertical (only one since they are not paralel)
	if (abs(slope1) == INF) return Point(x, slope2*x + n2);
	if (abs(slope2) == INF) return Point(c.getx(), slope1*c.getx() + n1);

	//we solve the linear system 
	double xcord = (n2 - n1)/(slope1 - slope2);
	double ycord = slope1*xcord + n1;

	return Point(xcord, ycord);
}

bool Point::between (const Point a, const Point b) const{
	bool candidate = false;

	//we first check that the point is the rectangle delimited by the
	//start and ends of the segments
	if (a.getx() <= x+epsilon and x <= b.getx() + epsilon) candidate = true;
	if (a.getx()+epsilon >= x and x + epsilon >= b.getx()) candidate = true;

	if (not candidate) return false;
	candidate = false;

	if (a.gety() <= y+epsilon and y <= b.gety() + epsilon) candidate = true;
	if (a.gety()+epsilon >= y and y + epsilon >= b.gety()) candidate = true;

	if (not candidate) return false;


	//now we get the slope of the line
	double slope = a.slope(b);

	//if the line is vertical
	if (abs(slope) == INF) {
		if (abs(x - a.getx()) > epsilon) return false;
		if (a.gety() <= y + epsilon and y <= b.gety() + epsilon) return true;
		return (a.gety() + epsilon >= y and y + epsilon >= b.gety());
	}

	//if not we complete the equation of the line and check if the point
	//verifies it
	double n = b.gety() - slope*b.getx();
	return (abs(y - slope*x - n) < epsilon);
}

bool Point::between_line (const Point a, const Point b) const{
	bool candidate = false;

	//we only have to check that the point if on the rectangle delimited by
	//the extremes of the segments
	if (a.getx() <= x+epsilon and x <= b.getx() + epsilon) candidate = true;
	if (a.getx()+epsilon >= x and x + epsilon >= b.getx()) candidate = true;

	if (not candidate) return false;
	candidate = false;

	if (a.gety() <= y+epsilon and y <= b.gety() + epsilon) candidate = true;
	if (a.gety()+epsilon >= y and y + epsilon >= b.gety()) candidate = true;

	return candidate;
}