#include "commands.hh"

using namespace std;

void save (istringstream& ss , string_Polgyon& listing){
	string doc, name;
	// if they dont give us the name of the document print error
	if (not (ss >> doc)) {error_missing(); return;}

	vector <string> Names;

	while (ss >> name){
		//check if it exists
		if (not check(name, listing)) return;
		Names.push_back(name);
	}

	// create document and open it
	ofstream document;
	document.open("Files/" + doc);
	document.setf(ios::fixed);
	document.precision(3);

	// output the polygons in the document
	for (int i = 0; i < (int) Names.size(); ++i){
		Polygon P = listing[Names[i]];
		document << Names[i];

		for (int i = 0; i < P.vertices(); ++i){
			document << " " << P[i].getx() << " " << P[i].gety();
		}

		document << endl;
	}

	document.close();
	cout << "ok" << endl;
}

void load (istringstream& ss , string_Polgyon& listing,  string_Color& colors){
	string doc, name, line2;
	// if they dont give us the file print error
	if (not (ss >> doc)) {error_missing(); return;}

	ifstream document;
	document.open("Files/" + doc);

	//if the file does not exist or cant be opened print error
	if (not document) {error_document(); return;}

	while (getline(document, line2)){
		istringstream ss2(line2);
		//if the polygon declaration is invalid detect it
		if (not newpolygon(ss2, listing, colors, false)) {document.close(); return;}
	}

	document.close();
	cout << "ok" << endl;
}