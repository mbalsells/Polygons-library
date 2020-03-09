#include "commands.hh"

using namespace std;

//errors messages
void error_missing (){
	cout << "Error: missing parameters" << endl;
}

void error_invalid (){
	cout << "Error: invalid declaration" << endl;
}

void error_undefined () {
	cout << "Error: undefined identifier" << endl;
}

void error_vertices () {
	cout << "Error: lacking vertices" << endl;
}

void error_document () {
	cout << "Error: document not found" << endl;
}


//check if a string is a double
bool is_not_double (string s){
	int n = (int) s.size();

	if (n == 0) {error_invalid(); return true;}

	if (s[0] == '-'){
		if (n == 1) {error_invalid(); return true;}
		if (s[1] < '0' or s[1] > '9') {error_invalid(); return true;}
	}

	else if (s[0] < '0' or s[0] > '9') {error_invalid(); return true;}
	if (s[n-1] < '0' or s[n-1] > '9') {error_invalid(); return true;}

	bool dot = false;

	for (int i = 1; i < n-1; ++i){
		if (s[i] == '.'){
			if (dot) {error_invalid(); return true;}
			else dot = true; 
		}
		else if (s[i] < '0' or s[i] > '9') {error_invalid(); return true;}
	}

	return false;
}

//check if polygon exists, if it doesnt print error and return false
bool check (string& name, string_Polgyon& listing){
	if (listing.find(name) == listing.end()) {
		error_undefined();
		return false;
	}
	return true;
}

//check if a polygons has at least a give nnumber of vertices
bool points (string& name, string_Polgyon& listing, int least){
	if (listing[name].vertices() < least) {
		error_vertices(); 
		return false;
	}
	return true;
}