main: main.o cell.o sudoku.o
		g++ main.o cell.o sudoku.o -o main

main.o: main.cpp
		g++ -g -c main.cpp

cell.o: cell.cpp
		g++ -g -c cell.cpp


sudoku.o: sudoku.cpp
		g++ -g -c sudoku.cpp

clean:
		rm -f *.o main
