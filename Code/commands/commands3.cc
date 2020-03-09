#include "commands.hh"

using namespace std;

void interior (istringstream& ss , string_Polgyon& listing){
	string name;
	vector <string> Names;

	while (ss >> name){
		//all polygons must exist
		if (not check(name, listing)) return;
		Names.push_back(name);
	}

	//there must be 2 polygons only
	if ((int) Names.size() < 2) {error_missing(); return;}
	if ((int) Names.size() > 2) {error_invalid(); return;}

	//check if it is inside
	if (listing[Names[0]].inside(listing[Names[1]])) cout << "yes" << endl;
	else cout << "no" << endl;
}

void area (istringstream& ss, string_Polgyon& listing){
	string name;
	vector <string> Names;

	// We read everything, check all polygons exist and have at least 3 vertices
	while (ss >> name) {
		if (not check(name, listing)) return;
		if (not points(name, listing, 3)) return;
		Names.push_back(name);
	}

	// We should have read only one thing
	if ((int) Names.size() < 1) {error_missing(); return;}
	if ((int) Names.size() > 1) {error_invalid(); return;}

	// Print the area
	cout << listing[name].area() << endl;
}

void perimeter (istringstream& ss, string_Polgyon& listing){
	string name;
	vector <string> Names;

	// Read everything and check it exists and has at least 2 vertices
	while (ss >> name) {
		if (not check(name, listing)) return;
		if (not points(name, listing, 2)) return;
		Names.push_back(name);
	}

	// We should have read only one polygon
	if ((int) Names.size() < 1) {error_missing(); return;}
	if ((int) Names.size() > 1) {error_invalid(); return;}

	// Print the perimeter
	cout << listing[name].perimeter() << endl;
}

void vertices (istringstream& ss, string_Polgyon& listing){
	string name;
	vector <string> Names;

	// Read everything and check it exists
	while (ss >> name) {
		if (not check(name, listing)) return;
		Names.push_back(name);
	}

	// We should have read only one polygon
	if ((int) Names.size() < 1) {error_missing(); return;}
	if ((int) Names.size() > 1) {error_invalid(); return;}

	// Print its vretices
	cout << listing[name].vertices() << endl;
}

void centroid (istringstream& ss, string_Polgyon& listing){
	string name;
	vector <string> Names;

	// We read everything, check it exists and has at least a vertex
	while (ss >> name) {
		if (not check(name, listing)) return;
		if (not points(name, listing, 1)) return;
		Names.push_back(name);
	}

	// Check we only read one polygon
	if ((int) Names.size() < 1) {error_missing(); return;}
	if ((int) Names.size() > 1) {error_invalid(); return;}

	// Compute the centroid and print its coordinates
	Point center = listing[name].centroid();
	cout << center.getx() << " " << center.gety() << endl;
}

void regular (istringstream& ss, string_Polgyon& listing){
	string name;
	vector <string> Names;

	// Read everything, check it exists and has at least 3 vertices
	while (ss >> name) {
		if (not check(name, listing)) return;
		if (not points(name, listing, 3)) return;
		Names.push_back(name);
	}

	// Check we only read one polygon
	if ((int) Names.size() < 1) {error_missing(); return;}
	if ((int) Names.size() > 1) {error_invalid(); return;}

	// Check if it is regular
	if (listing[name].regular()) cout << "yes" << endl;
	else cout << "no" << endl;
}

void in (istringstream& ss, string_Polgyon& listing){
	string name, a, b, test;
	// Check that we read something
	if (not (ss >> name)) {error_missing(); return;}

	double x, y;

	// Check we read two more strnigs
	if (not (ss >> a >> b)) {error_missing(); return;}

	// Check that they are indeed doubles
	if (is_not_double(a)) return;
	if (is_not_double(b)) return;
	istringstream iss(a + " " + b);
	iss >> x >> y;

	// Check that there is nothing else
	if (ss >> test) {error_invalid(); return;}

	// Check if the point belongs to the polygon
	if (listing[name].in(Point(x,y))) cout << "yes" << endl;
	else cout << "no" << endl;
}