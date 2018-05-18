// Elisabetta Caldesi
// sudoku class interface

#ifndef SUDOKU_H
#define SUDOKU_H

#include "cell.h" // call cell.h because it's a composite class
#include <iostream>
using namespace std;
#include <vector>
#include <fstream>
#include <string>

class Sudoku {

	public:
		Sudoku(string); // constructor
		~Sudoku(); // deconstructor
		void possibleValues(int, int); // changes the value of Cell vector possvals
		void SinglePossibility(int, int); // function that checks for single possibility
		void Singleton(); // function that uses the singleton algorithm
		void playSudoku(); // function that is used to call the others and play the game
		bool checkWin(); // function that checks if the board is filled
		void print(); // print the board
		bool checkInput(int, int, int); // function used to check for values in row column and minigrid. 
						

	private:
		vector <vector <Cell> > cells; // 2D vector the represents the board

};


#endif
