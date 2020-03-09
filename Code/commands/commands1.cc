#include "commands.hh"

using namespace std;

bool newpolygon (istringstream& ss , string_Polgyon& listing, string_Color& colors, bool okay){
	string name, numbers;

	//if we cant read the name print error
	if (not (ss >> name)) {error_missing(); return false;}

	double x;

	// here we keep the coordinates we read, so that later we can check if the
	// number of coordinates provided was even
	vector <double> Coordinates;
	while (ss >> numbers) {
		//check that the user doesnt put words in the middle of the declaration
		if (is_not_double(numbers)) return false;
		istringstream iss(numbers);
		iss >> x;
		Coordinates.push_back(x);
	}

	// If there is an odd number of coordinates print error
	if ((int) Coordinates.size() % 2 == 1) {error_invalid(); return false;}

	int mida = (int) Coordinates.size()/2;
	vector <Point> P(mida);

	for (int i = 0; i < mida; ++i) P[i] = Point(Coordinates[2*i], Coordinates[2*i+1]);
		
	if (okay) cout << "ok" << endl; 
	
	// if is the first time we read that name, set color to black
	if (listing.find(name) == listing.end()) colors[name] = {0,0,0};
	listing[name] = Polygon(P);
	return true;
}


void intersect_union (istringstream& ss , string_Polgyon& listing, string_Color& colors, bool intersect){
	string name;
	vector <string> Names;

	int cont = 0;

	while (ss >> name) {
		// if the polygons do not exist print error (not the first one)
		if (cont > 0) if (not check(name, listing)) return;
		Names.push_back(name);
		++cont;
	}

	//if more polygons or fewer polygons were provided print error.
	if ((int) Names.size() < 2) {error_missing(); return;}
	if ((int) Names.size() > 3) {error_invalid(); return;}

	//if there were 2 polygons and the first does not exist print error
	if ((int) Names.size() == 2 and not check(Names[0], listing)) return;

	int n = (int) Names.size();

	// if the polygon we create didnt exist set color to black
	if (listing.find(Names[0]) == listing.end()) colors[Names[0]] = {0,0,0};

	// do intersection or union
	if (intersect) listing[Names[0]] = listing[Names[n-2]].intersection(listing[Names[n-1]]);
	else listing[Names[0]] = listing[Names[n-2]].merge(listing[Names[n-1]]);

	cout << "ok" << endl;
}
