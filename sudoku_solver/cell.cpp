// Elisabetta Caldesi
// Cell class interface

#include "cell.h" // call cell.h
#include <iostream> 
using namespace std;
#include <vector>

// constructor
Cell::Cell() {
	value = 0; // intialize value of cell to 0
	// set possvals vector to 0's so every value is possible 
	for (int i=0; i<9;i++){
		possvals.push_back(0);
	
	}
}

// deconstructor
Cell::~Cell() {}

// get value of cell
int Cell::getValue() {
	return value;
}

// set value of the cell to any int passed in
void Cell::setValue(int n){
	value = n;
}

// check if the cell has a value different from 0
bool Cell::isFilled() {
	if (value != 0) {
		return true;
	}else {
		return false;
	}
}

// add int passed in to vector possvals
void Cell::setVector(int n) {

	possvals.push_back(n);
	
} 

// return the possvals vector
vector <int> Cell::getVector() {

	return possvals;	

}
