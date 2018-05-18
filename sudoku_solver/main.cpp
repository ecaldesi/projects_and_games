// Elisabetta Caldesi
// Main driver

#include<iostream>
#include<vector>
using namespace std;
#include<fstream>
// include cell.h and sudoku.h
#include "cell.h"
#include "sudoku.h"
#include <string>

int main(int argc, char* argv[]) {

	// read in arguments
	string filename;
	if (argc == 2) {
		filename = argv[1];
	}if (argc == 1) {
		cout << "Please enter file name" << endl;
		cin >> filename;
	}

	// call sudoku play and print board
	Sudoku s(filename);
	s.playSudoku();

	return 0;
}
