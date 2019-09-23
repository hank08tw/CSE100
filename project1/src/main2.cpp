
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "KDT.hpp"
using namespace std;

/**
 *  IMPORTANT!! YOU MUST USE THE FOLLOWING LINES OF CODE FOR PROMPTS AND
 * OUTPUTS: To output size of tree: cout << "Size of tree: " << size << "\n"; To
 * output height of tree: cout << "Height of tree: " << height << "\n"; To
 * prompt the user to enter a coordinate: cout << "Enter coordinate (x y): " <<
 * "\n";
 *
 *  To show the result of the nearest neighbor search: cout << "Nearest point in
 * tree: " << nearestNeighbor << "\n"; To prompt the user to try again: cout <<
 * "Search again? (y/n)" << "\n";
 *
 *  Use cin to process user input.
 *
 *  You MUST output size, then height, then prompt the user to search, as above.
 *
 *  You MUST have the prompt for entering the name appear if and only if
 *  the user input for trying again is "y" followed by the return key
 *  You MUST have the program exit (exiting the prompt loop) if and only if
 *  the user input for trying again is "n" followed by the return key
 *  You should handle other inputs for the retry prompt,
 *  but we will not be testing them.
 *
 *  Note that size, height, and nearestNeighbor are local variables in main that
 *  you should update accordingly.
 */

using namespace std;

int main(int argc, char *argv[]) {
    // Size of tree should be stored in local variable size.
    // Height of tree should be stored in local variable height.
    // Input name will be stored in a string name
    unsigned int size = 0;
    unsigned int height = 0;
    Point nearestNeighbor;

    // Check for Arguments
    if (argc != 2) {
        cout << "Invalid number of arguments.\n"
             << "Usage: ./main <input filename>.\n";
        return -1;
    }

    // Open file
    ifstream in;
    in.open(argv[1], ios::binary);

    // Check if input file was actually opened
    if (!in.is_open()) {
        cout << "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }

    // Check for empty file
    in.seekg(0, ios_base::end);
    unsigned int len = in.tellg();
    if (len == 0) {
        cout << "The file is empty. \n";
        return -1;
    }

    // Resets the stream to beginning of file
    in.seekg(0, ios_base::beg);

    // TODO
    // main function implementation should go here
    vector<Point> point;
    double xvalue;
    double yvalue;
    while (!in.eof()) {
        in >> xvalue;
        in >> yvalue;
        point.push_back(Point(xvalue, yvalue));
	in.get();
	if(in.peek()=='\n'){
		break;
	}
    }
    KDT kdt;
    kdt.build(point);
    height=kdt.height();
    size = kdt.size();
    cout << "Size of tree: " << size << "\n";
    cout << "Height of tree: " << height << "\n";
    char charin = 'y';
    while (charin == 'y') {
        cout << "Enter coordinate (x, y): " << "\n";
        cin >> xvalue; 
        cin >> yvalue; 
        Point nearestNeighbor = *kdt.findNearestNeighbor(Point(xvalue, yvalue));
        cout << "Nearest point in tree: " << nearestNeighbor << "\n";
        cout << "Search again? (y/n)" << "\n";
        cin >> charin;
    }
    if (in.is_open()) {
        in.close();
    }

    return 0;
}
