/*
 * Owner: Draven Schilling
 * Course: CS-3210/021
 * Date: 3/10/20
 * 
 * Program Description:
 * 	This program reads and STL file and prints the facet info and 
 * 	vertice coordinates to the console. At the end, summary statistics
 * 	are recorded for number of facet's and min/max coordinate points.
 */
#include <iostream> // input/output library
#include <fstream> // file library
#include <sstream> 
#include <string> // string library
#include <iomanip> // for setprecision()

#define BOUND 10000 // arbitrary min/max value.

using namespace std;

int main(){
	int number_of_facets = 0;
	int vertice = 1;
	double value = 0.0; // working value;
	double min[3] = {BOUND, BOUND, BOUND}; // x, y , z
	double max[3] = {-BOUND, -BOUND, -BOUND}; // x, y , z
	string filename, line, word, cord; // working strings
	
	// get and open file
	cout << "Enter STL file name: ";
	cin >> filename;
	ifstream myfile;
	myfile.open (filename.c_str());
	
	while(!myfile.eof()){ //parse file line by line
		getline(myfile, line);
		istringstream ss(line);
		ss >> word; // get the first word
		
		// you only need to check the first word to determine the line
		if(word.compare("facet") == 0){
			number_of_facets += 1;
			cout << "facet" << number_of_facets << endl;
			vertice = 1; // reset vertice number
		}else if(word.compare("vertex") == 0){
			// if the line is a vertex, read the next 3 values
			for(int i = 0; i<3; i++){
				ss >> value;
				// determine if each value is min/max?
				max[i] = (value>max[i]) ? value: max[i];
				min[i] = (value<min[i]) ? value : min[i];
				cord = i==0 ? "x" : i==1 ? "y" : "z"; // determine which x,y,z
				cout << fixed << setprecision(3) << "  " << cord << vertice << ": ";
				(value >= 0) ? cout << "+" << value : cout << value; //print + for positive
			}
			cout << endl;
			vertice += 1; // increment facet vertice number
		}
	} // end reading lines
	
	myfile.close(); // close file
	
	//print summary statistics
	cout << endl;
	cout << "|SUMMARY STATISTICS|" << endl;
	cout << endl;
	cout << "number of facet's:" << number_of_facets << endl;
	cout << fixed << setprecision(3) <<
	 "min| x:" << min[0] << " y:" << min[1] << " z:" << min[2] << endl;
	cout << fixed << setprecision(3) <<
	 "max| x:" << max[0] << " y:" << max[1] << " z:" << max[2] << endl;
	return 0;
}
