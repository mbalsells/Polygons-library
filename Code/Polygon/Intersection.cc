#include <iostream>
#include <algorithm>
#include <fstream>
#include "Polygon.hh"

using namespace std;

Polygon Polygon::intersection (const Polygon& Q) const{
	// All point in the intersection are either points of one of the polygons or
	// intersections of edges

	/*
	* My alogirithm is based on the typical sweep line alogrithm:
    * We have four active lines: the two leftmost edges of each polygon
    * We check intersections within these segments and if the leftmost points are in the other polygon
    * Then we take the minimum end point of the active lines and we consider the segment that begins there.
    * We check if the new start point for that edge is between the lines of the other polygon (the active ones)
    * We check the intersection between this new line and the lines of the other polygons (the active ones)
    * We update the active line for this new one.
    * We repeat the process till all edges have been visited (in total the algorithm is O(n))
    */


	int n = (int) P.size(), m = Q.vertices();
	vector <Point> R;
	
	// check degenerate cases
	if (n == 0 or m == 0) return Polygon();

	if (n == 1) {
		if (Q.in(P[0])) R.push_back(P[0]);
		return Polygon(R);
	}

	if (m == 1) {
		if (in(Q[0])) R.push_back(Q[0]);
		return Polygon(R);
	}

	if (n == 2){
		if (Q.in(P[0])) R.push_back(P[0]);
		if (Q.in(P[1])) R.push_back(P[1]);

		attempt({0,1}, {m-1, 0}, Q, R);
		for (int i = 0; i < m-1; ++i){
			attempt({0,1}, {i, i+1}, Q, R);
		}

		return Polygon(R);
	}

	if (m == 2){
		if (in(Q[0])) R.push_back(P[0]);
		if (in(Q[1])) R.push_back(P[1]);

		attempt({n-1,0}, {0, 1}, Q, R);
		for (int i = 0; i < n-1; ++i){
			attempt({i,i+1}, {0, 1}, Q, R);
		}

		return Polygon(R);
	}

	
	// for each polygon we consider the 2 leftmost edges. Each line is represented
	// as a pair of integers. The line goes from P[P1.first] to P[P1.second]
	ii P1 = {0, 1};
	ii P2 = {0, n-1};	

	ii Q1 = {0, 1};
	ii Q2 = {0, m-1};

	// we see if the intersection points of these lines are points of the intersection
	// of the polygons, same with the leftmost points of each polygon
	attempt(P1, Q1, Q, R);
	attempt(P1, Q2, Q, R);
	attempt(P2, Q1, Q, R);
	attempt(P2, Q2, Q, R);

	if (in(Q[0])) R.push_back(Q[0]);
	if (Q.in(P[0])) R.push_back(P[0]);

	// bools that tell us if all edges of the first polygon have been visited (same for Q)
	bool first = true;
	bool second = true;

	//while there are edges left to visit
	while (first or second){

		//we take the minimum of the endpoints of the active lines
		Point minimum = Point(INF, INF);

		if (first){
			if (P[P1.first] < P[P1.second]) minimum = min(minimum, P[P1.second]);
			if (P[P2.first] < P[P2.second]) minimum = min(minimum, P[P2.second]);
		}
		if (second){
			if (Q[Q1.first] < Q[Q1.second]) minimum = min(minimum, Q[Q1.second]);
			if (Q[Q2.first] < Q[Q2.second]) minimum = min(minimum, Q[Q2.second]);
		}

		//we update the line and check intersections and the new point
		if (first and minimum == P[P1.second]){

			// check if the new start point for this edge is between the two
			// lines of the other polygon (and hence, is inside the other polygon)
			if (Q[Q1.first].clockwise(Q[Q1.second], minimum) and not
			    Q[Q2.first].clockwise(Q[Q2.second], minimum)) R.push_back(minimum);

			//update active line
			++P1.first; ++P1.second;

			//see intersections of the new line with the active liens of the other polgyon
			attempt(P1, Q1, Q, R);
			attempt(P1, Q2, Q, R);
		}	
		else if (first and minimum == P[P2.second]){
			if (Q[Q1.first].clockwise(Q[Q1.second], minimum) and not
				Q[Q2.first].clockwise(Q[Q2.second], minimum)) R.push_back(minimum);

			--P2.first; --P2.second;

			if (P2.first < 0) P2.first = n-1;

			attempt(P2, Q1, Q, R);
			attempt(P2, Q2, Q, R);
		}	
		else if (second and minimum == Q[Q1.second]){
			if (P[P1.first].clockwise(P[P1.second], minimum) and not
				P[P2.first].clockwise(P[P2.second], minimum)) R.push_back(minimum);

			++Q1.first; ++Q1.second;
			attempt(P1, Q1, Q, R);
			attempt(P2, Q1, Q, R);
		}
		else if (second and minimum == Q[Q2.second]){
			if (P[P1.first].clockwise(P[P1.second], minimum) and not
				P[P2.first].clockwise(P[P2.second], minimum)) R.push_back(minimum);

			--Q2.first; --Q2.second;

			if (Q2.first < 0) Q2.first = m-1;

			attempt(P1, Q2, Q, R);
			attempt(P2, Q2, Q, R);
		}

		if (P1.second == P2.second) first = false;
		if (Q1.second == Q2.second) second = false;
	}

	// we check if the rightmost points belong also to the other polygon
	if (in(Q[Q1.second])) R.push_back(Q[Q1.second]);
	if (Q.in(P[P1.second])) R.push_back(P[P1.second]);
		
	return Polygon(R);

	// Note: I have not implemented another function to update the lines because
	// it supposed having to use *this in a function, which would recieve up to 8
	// parameters, making it harder to read and understand, furthermore, this is
	// the only method that would use it.
}