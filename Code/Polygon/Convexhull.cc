#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include "Polygon.hh"

using namespace std;

struct Comp {
	Point a;

	bool operator ()(const Point b, const Point c){
		if (b != c){
			// since 0/0 is nan doing the slope of a point with itself may
			// produce errors, so we consider it as a separate case
			if (b == a) return true;
			if (c == a) return false;
		}

		// we sort it by increasing slope, in case of a tie by which is closer to a
		if (a.slope(b) == b.slope(c)) return b < c;
		return a.slope(b) > a.slope(c);
	}
};


void Polygon::ConvexHull() {
	/*
	* We take the leftmost point (in case of a tie the lower one), this is our start point
    * We sort P using the operator () of the struct Comp, taking the start point as the point a
    * We go through the sorted vector adding the points that we visit to another vector (CHull).
    * If at some point we visit a point such that is counterclockwise with respect to the two previous 
      taken points we start eliminating the taken points till the point is clockwise
      with last two points of CHull
    * In CHull we have the convex hull of the initial set of points
	*/

	int n = (int) P.size();

	// check degenerate case
	if (n < 2) return; 
	if (n == 2) {
		if (P[0] == P[1]) P.pop_back();
		return;
	}

	// find leftmost (lower) point
	Point first = P[0];
	for (int i = 1; i < n; ++i) first = min(first, P[i]);


	// this is the final vector of points, the convex hull
	vector <Point> CHull = {first};

	// we sort the points of P;
	sort(P.begin(), P.end(), Comp{first});
	
	// valid is the position of the first point which is different than the start one
	int valid = 1;

	// we put the point with highest slope different than start(not necesarily in the convex hull 
	// since there can be points with the same slope but further)
	while (valid < n and (int) CHull.size() == 1){
		if (P[valid] == first) ++valid;
		else CHull.push_back(P[valid]);
	}

	// if all points were equal we stop here
	if ((int) CHull.size() == 1) {
		P = CHull;
		return;
	}

	// m is the size of the CHull
	int m = 2;
	
	//for each point
	for (int i = valid + 1; i < (int) P.size(); ++i) {
		//while the points are counterclockwise we pop points
		while ((int) CHull.size() > 1 and not CHull[m-2].clockwise(CHull[m-1], P[i])){
			--m;
			CHull.pop_back();
		}
		
		//we add the point
		++m;
		CHull.push_back(P[i]);
	}

	//we take into account the last point 
	while ((int) CHull.size() > 2 and not CHull[m-2].clockwise(CHull[m-1], CHull[0])) {
		CHull.pop_back();
		--m;
	}

	P = CHull;
}
