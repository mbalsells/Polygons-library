#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include "Polygon.hh"

using namespace std;

Polygon::Polygon (){
	P = {};
}

Polygon::Polygon (vector <Point>& V){
	P = V;
	ConvexHull();
}

bool Polygon::operator == (const Polygon& Q) const{
	if ((int) P.size() != Q.vertices()) return false;

	for (int i = 0; i < (int) P.size(); ++i) if (P[i] != Q[i]) return false;
	return true;
}

//Pre: Polygon has at least 3 vertices
double Polygon::area() const{
	double ans = 0;
	// We use the shoelace formula to compute the area
	for (int i = 0; i < (int) P.size() - 1; ++i) {
		ans += (P[i].getx()*P[i+1].gety() - P[i].gety()*P[i+1].getx());
	}
	ans += (P[P.size()-1].getx()*P[0].gety() - P[P.size()-1].gety()*P[0].getx());

	return abs(ans)/2;
}

//Pre: Polygon has at least 2 vertices
double Polygon::perimeter () const{
	//if it has two points we return their distance
	if ((int) P.size() == 2) return P[0].distance(P[1]);

	double ans = 0;
	for (int i = 0; i < (int) P.size()-1; ++i) {
		ans += P[i].distance(P[i+1]);
	}
	ans += P[0].distance(P[(int) P.size()-1]);
	
	return ans;
}

//Pre: Polygon has at least a vertex
Point Polygon::centroid () const{
	double xcord = 0, ycord = 0;

	for (int i = 0; i < (int) P.size(); ++i) {
		xcord += P[i].getx();
		ycord += P[i].gety();
	}

	return Point(xcord/vertices(), ycord/vertices());
}

Polygon Polygon::merge (const Polygon& Q) const{
	// We join all points and call the convexhull
	vector <Point> R = P;

	for (int i = 0; i < Q.vertices(); ++i){
		R.push_back(Q[i]);
	}

	return Polygon(R);
}

bool Polygon::inside (const Polygon& Q) const{
	return Q == merge(Q);
}

//Pre: Polygon has at least a vertex
Polygon Polygon::bbox() const{
	double xmin = P[0].getx(), ymin = P[0].gety();
	double xmax = xmin, ymax = ymin;

	// we get the minimum xcoord, ycoord an the maximum ones
	for (int i = 1; i < (int) P.size(); ++i){
		xmin = min(xmin, P[i].getx());
		xmax = max(xmax, P[i].getx());
		ymin = min(ymin, P[i].gety());
		ymax = max(ymax, P[i].gety());
	}

	vector <Point> Q = {Point(xmin, ymin), Point(xmax, ymax)};
	return Polygon(Q);
}
