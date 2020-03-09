#include "commands.hh"

using namespace std;

void instruct (string& line, string_Polgyon& listing, string_Color& colors){

	if ((int) line.size() == 0) return;

	if (line[0] == '#') {
		cout << "#" << endl;
		return;
	}

	istringstream ss(line);
	string command;
	ss >> command;
	
		 if (command == "polygon") newpolygon (ss, listing, colors, true);
	else if (command == "print") print (ss, listing);
	else if (command == "area") area (ss, listing);
	else if (command == "perimeter") perimeter (ss, listing);
	else if (command == "vertices") vertices (ss, listing);
	else if (command == "centroid") centroid (ss, listing);
	else if (command == "list") list (listing);
	else if (command == "save") save (ss, listing);
	else if (command == "load") load (ss, listing, colors);
	else if (command == "inside") interior (ss, listing);
	else if (command == "bbox") bound (ss, listing, colors);
	else if (command == "setcol") setcol (ss, listing, colors);
	else if (command == "intersection") intersect_union(ss, listing, colors, true);
	else if (command == "union") intersect_union (ss, listing, colors, false);
	else if (command == "draw") draw(ss, listing, colors, true);
	else if (command == "fulldraw") draw(ss, listing, colors, false);
	else if (command == "regular") regular(ss, listing);
	else if (command == "in") in(ss, listing);

	else cout << "Error: unrecognized command" << endl;
}


int main(){
	cout.setf(ios::fixed);
	cout.precision(3);

	string_Polgyon listing;
	string_Color colors;

	string line;
	while (getline(cin, line)) instruct (line, listing, colors);
}