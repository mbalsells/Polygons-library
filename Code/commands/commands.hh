#ifndef commands_hh
#define commands_hh

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <map>
#include <math.h>
#include <fstream>
#include <pngwriter.h>
#include "Polygon.hh"


using namespace std;
typedef map <string, Polygon> string_Polgyon;
typedef map <string, vector <double> > string_Color;


//error detectors
void error_missing ();
void error_invalid ();
void error_undefined ();
void error_vertices ();
void error_document ();

//returns false and prints an error if s is not a double
bool is_not_double (string s);

//returns true if name is a polygon
bool check (string& name, string_Polgyon& listing);

//returns true if name has at least "least" vertices
bool points (string& name, string_Polgyon& listing, int least);

//creates a polygon, in case okay is false it prints no errors even if there are.
//it returns false if there was some error and true otherwise
bool newpolygon (istringstream& ss, string_Polgyon& listing, string_Color& colors, bool okay);

//prints the name and vertices of the polygon that will be read
void print (istringstream& ss, string_Polgyon& listing);

//prints the area of the polygon that will be read
void area (istringstream& ss, string_Polgyon& listing);

//prints the perimeter of the polygon that will be read
void perimeter (istringstream& ss, string_Polgyon& listing);

//prints the number of vertices of the polygons that will be read
void vertices (istringstream& ss, string_Polgyon& listing);

//prints the coordinates of the centroid of the polygon that will be read
void centroid (istringstream& ss, string_Polgyon& listing);

//prints the polygons that have been defined so far
void list (string_Polgyon& listing);

//saves the polygons that are given to a file
void save (istringstream& ss, string_Polgyon& listing);

//loads a file with polygon definitions
void load (istringstream& ss, string_Polgyon& listing, string_Color& colors);

//checks if a polygons is inside another one
void interior (istringstream& ss, string_Polgyon& listing);

//creates a polygon with the corners of the smallest rectangle which contains all
//the given polygons
void bound (istringstream& ss, string_Polgyon& listing, string_Color& colors);

//It assigns the given colours to the given polygon
void setcol (istringstream& ss, string_Polgyon& listing, string_Color& colors);

//It computes the intersection or union of two polygons (depending on whether the
//bool intersect is true or false)
void intersect_union (istringstream& ss, string_Polgyon& listing, string_Color& colors, bool intersect);

//Draws the given polygons centered and in a white screen of 500X500 where there is a 
//pixel of margin in each side, if lines is true it only draws the edges of the polygons
//if it is false it draws the polygons filled
void draw(istringstream& ss, string_Polgyon& listing, string_Color& colors, bool lines);

//It checks if a polygon is regular or not
void regular (istringstream& ss, string_Polgyon& listing);

//It checks if a point is inside a polygon
void in (istringstream& ss, string_Polgyon& listing);

#endif