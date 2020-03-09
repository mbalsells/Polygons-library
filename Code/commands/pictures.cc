#include "commands.hh"
#include <pngwriter.h>

using namespace std;

// Functions to draw points, lines and filled triangles.
// Note, the library pngwritter doesnt round numbers so we have to do so
// They recive the required points and the factors to escalate and center the image, as well
// as the components for the colors and the png document where they have to draw everything
void print_point (Point a, double escalate, double xk, double yk, double x, double y, double z, pngwriter& png){
    png.plot(round(a.getx()*escalate + xk), round(a.gety()*escalate + yk), x, y, z);
}

void print_line (Point a, Point b, double escalate, double xk, double yk, double x, double y, double z, pngwriter& png){
    png.line(round(a.getx()*escalate + xk), round(a.gety()*escalate + yk), 
             round(b.getx()*escalate + xk), round(b.gety()*escalate + yk), x, y, z);
}

void print_triangle (Point a, Point b, Point c, double escalate, double xk, double yk, double x, double y, double z, pngwriter& png){
    png.filledtriangle(round(a.getx()*escalate + xk), round(a.gety()*escalate + yk), round(b.getx()*escalate + xk),  
                       round(b.gety()*escalate + yk), round(c.getx()*escalate + xk), round(c.gety()*escalate + yk), x, y, z);
}


void draw (istringstream& ss, string_Polgyon& listing, string_Color& colors, bool lines){
	string file, name;

    // Check that we read something
	if (not (ss >> file)) {error_missing(); return;}

    // Put where to save the file 
    file = "Images/" + file;

    // Here we store all polygons we read, since, before drawing anything we must compute
    // the values to reescalate and center the image
    vector <string> store;

    // This boolean tells us wheter all polygons had less than two vertices
    bool all_points = true;

    //minimum and maximum cooridnates
    double xmin = INF, ymin = INF, xmax = -INF, ymax = -INF;

    while (ss >> name){
        // Check that all polygons exist
    	if (not check(name, listing)) return;

        // Check if the polygon has more than a vertex
        if (listing[name].vertices() > 1) all_points = false;

        // If the polygon isnt empty we update the max/min coordinates
        if (listing[name].vertices() > 0){
            // store the polygon
        	store.push_back(name);

            // Polygon A has the leftmost lower vertex and rightmost
            // upper vertex of the smallest rectangle that contains the polygon
        	Polygon A = listing[name].bbox();

        	xmin = min(xmin, A[0].getx());
        	ymin = min(ymin, A[0].gety());

        	xmax = max(xmax, A[1].getx());
        	ymax = max(ymax, A[1].gety());
        }
    }

    // Check that at least there is a polygon with two vertices
    if (all_points){
        error_vertices();
        return;
    }

    // Escalate is such that when multiplying each point by it, they all
    // fit in a 498x498 screen
    double escalate = min(497/(xmax-xmin), 497/(ymax-ymin));

    // We create a white screen of 500x500 white with the desired name
    pngwriter png(500, 500, 1.0, file.c_str());

    // Initially the leftmost and lower coordinates must be 2 (1 pixel of margin)
    // So if we add x0 to each xoordinate and y0 to each ycoordinate, all the points
    // will be in the 498x498 screen. However, they might not be centered
    double x0 = 2-xmin*escalate;
    double y0 = 2-ymin*escalate;

    // The maximum coordinates would then be
    double x1 = xmax*escalate +x0;
    double y1 = ymax*escalate +y0;

    // We take xk and yk such that, when we add xk to each xcoord and yk to each ycoord
    // all points are in the 498x498 desired screen, and centered
    double xk = x0 + (499 - x1)/2;
    double yk = y0 + (499 - y1)/2;

    // for each polygon
	for (int i = 0; i < (int) store.size(); ++i) {
		name = store[i]; 
        Polygon A = listing[name];
		int n = A.vertices();

        // color coordinates
    	double x = colors[name][0], y = colors[name][1], z = colors[name][2];


        // If the polygon is empty do nothing, if is is a point draw a point, if it is a line
        // draw a line. If we have to draw only lines (line = true) draw each edge, if we have to draw
        // a filled polygon (line = false) we triangulate the polygon and draw filled triangles
             if (n == 0);
        else if (n == 1) print_point(A[0], escalate, xk, yk, x, y, z, png);
        else if (n == 2) print_line(A[0], A[1], escalate, xk, yk, x, y, z, png);
        else if (lines){
            print_line(A[n-1], A[0], escalate, xk, yk, x, y, z, png);

            for (int i = 0; i < n-1; ++i) print_line(A[i], A[i+1], escalate, xk, yk, x, y, z, png);
        }
        else for (int i = 1; i < n-1; ++i){
            print_triangle(A[0], A[i], A[i+1], escalate, xk, yk, x, y, z, png);
        }
    }

    png.close();
    cout << "ok" << endl;
}