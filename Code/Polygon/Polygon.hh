#ifndef Polygon_hh
#define Polygon_hh
#include <vector>
#include <fstream>
#include "Point.hh"

using namespace std;
typedef pair <int,int> ii;

class Polygon{
	private:
		vector <Point> P;
		
		//This method updates P so that it becomes a clockwise sorted convex Polygon
		//which constist of the convexhull of P
		void ConvexHull();

		//If the segment P[a.first] P[a.second] and the segment Q[b.first] Q[b.second]
		//intersect, it adds the point of intersection to R.
		void attempt(ii a, ii b, const Polygon& Q, vector <Point>& R) const;

	public:

		//Constructors
		Polygon ();
		Polygon (vector <Point>& V);

		//Returns the ith element of P
		const Point& operator[](int i) const {return P[i];}

		//Returns true if the polygons have the same vertices and false otherwise
		bool operator == (const Polygon& Q) const;
		
		//Returns the area of the Polygon
		double area() const;

		//Returns the perimeter of the polygon
		double perimeter() const;

		//Returns the number of vertices of the polygon
		int vertices() const {return (int) P.size();}

		//Returns the centroid of the polygon
		Point centroid() const;

		//Returns a polygon which is the union of *this and Q 
		Polygon merge (const Polygon& Q) const;

		//Returns the leftmost lower corner and rightmost upper corner of the smallest
		//rectangle that contains the polygon
		Polygon bbox () const ;
		
		//Returns true if the polygon is regular and false otherwise
		bool regular () const;

		//Returns true if the polygon *this is inside Q
		bool inside (const Polygon& Q) const;

		//Returns true if the point a is inside the polygon *this
		bool in (const Point a) const;

		//Returns a Polygon, the intesection of the polygons Q and *this
		Polygon intersection (const Polygon& Q) const;
};

#endif