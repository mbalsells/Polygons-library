#ifndef Point_hh
#define Point_hh
#include <iostream>

using namespace std;

const double epsilon = 1e-12;
const double INF = 1.0/0.0;

class Point{
	private:
		double x, y;

	public:
		Point(double a, double b) {x = a; y = b;}
		Point() {x = 0; y = 0;}

		//Returns the x component of the point
		double getx() const {return x;}

		//Returns the y component of the point
		double gety() const {return y;}

		//Return true if the point has xcoord smaller than a, in case of
		//a tie it compares the ycoord
		bool operator < (const Point& a) const;

		//Returns true if the coordinates of the two points differ by at most epsilon
		bool operator == (const Point& a) const;

		//Rerturns not ==
		bool operator != (const Point& a) const;
		
		//Returns the slope of the line that connects both points
		//if the line is vertical returns INF
		// Pre: a must be different than *this
		double slope(const Point a) const;

		//Returns the distance between the two points
		double distance(const Point a) const;

		//Returns true if the points are clockwise and false otherwise
		bool clockwise(const Point b, const Point c) const;

		//Returns true if *this is in the segments that goes from a to b
		bool between(const Point a, const Point b) const;

		//Returns true if *this is in the segments that goes from a to b
		//knowing that the point is in that line (not necessarily in the segment)
		//is much more precise than between, but not so general
		bool between_line(const Point a, const Point b) const;

		//Returns the point of the intersection of the line from *this to a 
		//and the line from b to c
		Point cross(const Point a, const Point b, const Point c) const;
};

#endif