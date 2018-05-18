// Elisabetta Caldesi
// sudoku class implementation

#include "sudoku.h" // call sudoku.h
#include <iostream>
#include "cell.h" // call cell.h
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// constructor
Sudoku::Sudoku(string filename) {
	
	// initiate vector of Cell
	for (int i=0; i< 9; i++){
		vector <Cell> temp;
		for (int j=0; j< 9; j++){
			Cell c;
			c.setValue(0);
			temp.push_back(c);
		}
		cells.push_back(temp);
	}

	// read in from file
	ifstream ifs;
	ifs.open(filename.c_str());
	int num;
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			ifs >> num;
			cells[i][j].setValue(num);
		}
	}
}

// deconstructor
Sudoku::~Sudoku() {}

// function that determines possible values in each cell
void Sudoku::possibleValues(int r, int c){

	// set possible values to all 0's
	for (int i=0; i<9; i++) {
		cells[r][c].possvals[i] = 0;
	}

	// set the value of possible values to 1 if the current value of cell is 0 and if there is a possible value that checkInput
	// checked (so there isn't the same value in the row, column and minigrid)
	for(int k=0; k <9; k++){
		if (checkInput(r,c,k+1) && cells[r][c].getValue() == 0){
			cells[r][c].possvals[k] = 1;
		}
	}
	
}

// function that checks the values in the cell for row, column and minigrid
bool Sudoku::checkInput(int r, int c, int k){

	// initiate variable
	int cellval=0;

	// check for row
	for (int i=0; i<9; i++) {
		cellval= cells[r][i].getValue(); // get value of cell
		if (cellval == k) { // if cell value is not equal to zero (k is the variable used to iterate
					// through a loop in possibleValues()), return 0
			return 0;
		}
	}

	// check for column
	for (int i=0; i<9; i++) {
		cellval= cells[i][c].getValue();
		if (cellval == k) {
			return 0;
		}
	}

	// check for minigrid
	
	// boundaries for for loop
	int rbegin = r - (r%3); // row
	int rend = rbegin +3;
	int cbegin = c - (c%3); // column
	int cend = cbegin +3;
	
	for (int i = rbegin; i<rend ; i++) {
		for (int j= cbegin; j< cend; j++) {
			cellval = cells[i][j].getValue();
			if (cellval == k) {
				return 0;
			}
		}
	}
	
	return 1;				
}

// check if the board is filled 
bool Sudoku::checkWin() {
	int counter = 0; // counter for cells
	for (int i =0; i< 9; i++) {
		for (int j =0; j< 9; j++) {
			if (cells[i][j].isFilled() == true){
				counter ++;
			}
		}
	}
	// board 9x9
	if (counter==81) {
		return true;
	}else {
		return false;
	}
}

// algorithm for single possibility
void Sudoku::SinglePossibility(int r, int c) {

	// initiate variables
	int counter = 0;
	int cellval = 0;

	// set a counter that counts the number of ones in the vector
	for (int i =0; i< 9; i++ ) {
		if (cells[r][c].possvals[i] == 1) {
			counter+=1;
		}
	}

	// if only one value in the vector is a 1	
	if (counter == 1) {
		for (int i=0; i< 9; i++) {
			if (cells[r][c].possvals[i] == 1) {
				cellval=i+1; // assign the index of the vector + 1 to the value of the cell
				cells[r][c].setValue(cellval);
				cells[r][c].possvals[i] = 0; // set the possvals vector of the cell to all 0's
			}
		}
	}

	// Set the vector of possvals to 0's to update it
	for (int i=0; i<9; i++) {
		cells[r][c].possvals[i] = 0;
	}
}

// algorith for singleton
void Sudoku::Singleton() {
	
	// initiate a vector that works as a counter
	vector <int> possCount;


	// set vector for count of possible numbers to 0
	for (int i=0; i<9; i++) {
		possCount.push_back(0);
	}

	// CHECK FOR COLUMN
	for (int i=0;i<9; i++){ //row		
		for (int j=0; j< 9; j++) { //columns
			possibleValues(i,j); // update value of possible values
			for (int k=0; k<9; k++) { 
				possCount[k] += cells[i][j].possvals[k]; // add to counter
			}
		}

		// check if there is a 1 in the counter vector
		for (int z=0; z<9; z++) {
			if (possCount[z] == 1){
				// go through the column again
				for (int x=0; x<9; x++) {
					// find the 1 in the possvals vector
					if (cells[i][x].possvals[z] == 1) {
						cells[i][x].setValue(z+1); // assign value of cell to index +1 
						cells[i][x].possvals[z] = 0; // reset possvals vector
						break;
					}
				}	
			}
		}

		// reset counter
		for (int i=0; i<9; i++) {
			possCount[i] =0;
		}	
	}

	// reset counter
	for (int i=0; i<9; i++) {
		possCount[i] =0;
	}


	// CHECK FOR ROW
	for (int i=0;i<9; i++){ //row		
		for (int j=0; j< 9; j++) { //columns
			possibleValues(j,i); // update value of possible values
			for (int k=0; k<9; k++) {
				possCount[k] += cells[j][i].possvals[k]; // add to counter
			}
		}

		// check if there is a 1 in the counter vector
		for (int z=0; z<9; z++) {
			if (possCount[z] == 1){
				// go through row again
				for (int x=0; x<9; x++) {
					if (cells[x][i].possvals[z] == 1) {
						cells[x][i].setValue(z+1); // assign value of cell to index +1
						cells[x][i].possvals[z] = 0; // reset possvals vector
						break;
					}
				}	
			}
		}

		// reset counter
		for (int i=0; i<9; i++) {
			possCount[i] =0;
		}

	}

	// reset counter
	for (int i=0; i<9; i++) {
		possCount[i] = 0;
	}

	// update possible values vector
	for (int i=0; i<9; i++) {
		for(int j=0; j<9; j++){
			possibleValues(i,j);
		}
	}
	
	// CHECK FOR MINI GRID
	for (int r=0; r<9; r+=3) { // row 
		for (int c=0; c<9; c+=3){ // column
			// minigrid boundaries
			for (int m=r; m<r+3; m++){ 
				for (int n=c; n<c+3; n++) {
					for (int k=0; k<9; k++) {
						possCount[k] += cells[m][n].possvals[k]; // add to counter vector
					}
				}
			}
			// find the one 1
			for (int z=0; z<9; z++) {
				if (possCount[z] == 1){
					// go through minigrid again
					for (int m=r; m< r+3; m++) {
						for (int n=c; n<c+3; n++) {
							if (cells[m][n].possvals[z] == 1) {
								cells[m][n].setValue(z+1); // assign value of cell to index +1
								cells[m][n].possvals[z] = 0; // reset possvals vector
								break;
							}
						}
					}
				}	
			}
		}

		// reset counter
		for (int i=0; i<9; i++) {
			possCount[i] = 0;
		}
		
	}
	
}
// play Sudoku function
void Sudoku::playSudoku() {
	print(); // print board initially
	cout << endl;
	while (checkWin() == false){ // if the board in not filled
		// go through each row
		for (int i=0; i<9; i++){
			// go through each column 
			for (int j=0; j<9; j++) {
				possibleValues(i,j); // update possvals
				SinglePossibility(i, j); // single possibility algorithm
				possibleValues(i,j); // update possvals
			}
		}
		Singleton(); // singleton alogrithm
		print(); // print board everytime
		cout << endl;
	}
}

// print function
void Sudoku::print() {
	
	int counter=0;
	for (int i=0; i< 9; i++){
		for (int j=0; j<9; j++) {
			cout << cells[i][j].getValue()<< " ";
			counter+=1;
			}
			// start a new line every 9 cells
			if (counter == 9) {
				cout << endl;
				counter = 0;
			}	
		}
}

