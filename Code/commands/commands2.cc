#include "commands.hh"

using namespace std;

void list (string_Polgyon& listing){
	bool first = false;

	//we print each name in the map (listing)
	for (auto x: listing) {
		if (first) cout << " ";
		else first = true;

		cout << x.first;
	}
	cout << endl;
}

void bound (istringstream& ss, string_Polgyon& listing, string_Color& colors){
	string name1, name;
	// If they dont give us anything print error
	if (not (ss >> name1)) {error_missing(); return;}

	double xmin = INF, ymin = INF, xmax = -INF, ymax = -INF;

    while (ss >> name){
    	// All polygons must exist
    	if (not check(name, listing)) return;
    		// We only consider those who are not empty
	    	if (listing[name].vertices() > 0){
	    	Polygon A = listing[name].bbox();

	    	xmin = min(xmin, A[0].getx());
	    	ymin = min(ymin, A[0].gety());

	    	xmax = max(xmax, A[1].getx());
	    	ymax = max(ymax, A[1].gety());
	    }
    }

    // If there was no non empty polygon print error
    if (xmin == INF) {error_invalid(); return;}

    // If the polygon does not exist set color to black
    if (listing.find(name1) == listing.end()) colors[name1] = {0,0,0};

    // We create the resulting polygon
    vector <Point> Q = {Point(xmin, ymin), Point(xmin, ymax), Point(xmax, ymax), Point(xmax, ymin)};
    listing[name1] = Polygon(Q);

	cout << "ok" << endl;
}

void setcol (istringstream& ss, string_Polgyon& listing, string_Color& colors){
	string name, test, R1, G1, B1;

	// Check if we read something
	if (not (ss >> name)) {error_missing(); return;}

	// Check if the polygon exists
	if (not check(name, listing)) return;

	double R, G, B;

	// Check if we read three things
	if (not (ss >> R1 >> G1 >> B1)){error_missing(); return;}

	// Check that they are doubles
	if (is_not_double(R1)) return;
	if (is_not_double(B1)) return;
	if (is_not_double(G1)) return;

	istringstream iss(R1 + " " + G1 + " " + B1);
	iss >> R >> G >> B;

	// Check that we read nothing else
	if (ss >> test){error_invalid(); return;}

	// Check that all colors are between 0 and 1
	if (R < 0 or R > 1 or G < 0 or G > 1 or B < 0 or B > 1) {error_invalid(); return;}

	// Change color
	colors[name] = {R, G, B};
	cout << "ok" << endl;
}

void print (istringstream& ss, string_Polgyon& listing){
	string name;
	vector <string> Names;

	// Read everything and make sure all exist
	while (ss >> name) {
		if (not check(name, listing)) return;
		Names.push_back(name);
	}

	// We should have only read one thing
	if ((int) Names.size() < 1) {error_missing(); return;}
	if ((int) Names.size() > 1) {error_invalid(); return;}

	// We print the name and the vertices of the polygon
	cout << name;
	Polygon P = listing[name];

	for (int i = 0; i < P.vertices(); ++i){
		cout << " " << P[i].getx() << " " << P[i].gety();
	}

	cout << endl;
}