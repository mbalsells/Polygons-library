#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include "Polygon.hh"

using namespace std;

void Polygon::attempt (ii a, ii b, const Polygon& Q, vector <Point>& R) const{
	Point p1 = P[a.first];
	Point p2 = P[a.second];
	Point q1 = Q[b.first];
	Point q2 = Q[b.second];

	// we consider the point of the intersection of the lines p1 p2, and q1 q2
	Point candidate = p1.cross(p2, q1, q2);

	// we have to check that the intersection occurs in the segment p1 p2 and q1 q2
	if (candidate.between_line(p1, p2) and candidate.between_line(q1, q2)){
		R.push_back(candidate);
	}
}


bool Polygon::regular() const{
	int n = (int) P.size();

	double dist = P[n-1].distance(P[0]);

	// we allow higher relaxation for precision issues. We also normalize the distance
	// to avoid precision issued: i.e. that polygons whose points are
	// close are not considered regular if they arent really
	for (int i = 0; i < n-1; ++i) {
		if (abs((dist - P[i].distance(P[i+1]))/dist) > 0.001) return false;
	}

	return true;
}


bool Polygon::in (const Point a) const{
	/*
	* We consider the leftmost point and set left = 1 and right = n-1. We now perform a binary search:
    * Lets consider the line made up by P[0] and P[middle] where middle = (right+left)/2
    * If P[middle], P[0] and the given point are clockwise then the point is above the line, 
      so we set right = middle. If not then the point is below the line, so we set left = middle
    * At the end, we will end up with a triangle made up by P[0], P[left] and P[right].
    * We check if Point a lies in the sides of the triangle or if the point is inside the triangle
	*/

	//check degenerates cases
	if ((int) P.size() == 0) return false;
	if ((int) P.size() == 1) return P[0] == a;
	if ((int) P.size() == 2) return a.between(P[0], P[1]);

	int left = 1, right = (int) P.size()-1;

	//binary search: keep dividing the plane till we have a cone
	while (left + 1 < right){
		int middle = (left + right)/2;

		if (P[middle].clockwise(P[0], a)) right = middle;
		else left = middle;
	}

	// now P[0] P[left] P[right] form a triangle, if the point is in the polygon
	// it must be inside this triangle (or on the sides of it)

	// is on the sides?
	if (a.between(P[0], P[left])) return true;
	if (a.between(P[right], P[left])) return true;
	if (a.between(P[0], P[right])) return true;

	// is outside ?
	if (not P[0].clockwise(P[left], a)) return false;
	if (not P[left].clockwise(P[right], a)) return false;
	if (not P[right].clockwise(P[0], a)) return false;

	return true;
}