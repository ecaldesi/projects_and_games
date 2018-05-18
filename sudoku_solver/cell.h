// Elisabetta Caldesi
// Cell class interface

#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
using namespace std;

class Cell {
	// public members
	public:
		Cell(); // constructor
		~Cell(); // decostructor
		int getValue();	// get Value of the cell
		void setValue(int); // assign value to the cell
		vector <int> getVector(); // returns the value of the vector 
		void setVector(int); // set the value of the vector
		vector <int> possvals; // vector of possible values for each cell. It is filled with 0's or 1's
					// 1 - the cell can take the value of the index (+1 because vectors start at 0)
					// 0 - the cell can't take the value of index+1
		bool isFilled(); // checks if the cell is filled
	private:
		int value; // value of the cell
		
};

#endif
