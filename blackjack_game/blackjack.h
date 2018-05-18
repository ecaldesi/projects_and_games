// Elisabetta Caldesi
// BlackJack class interface

#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <iostream>
using namespace std;

class BlackJack {
	
	public:
		BlackJack(int = 52); // constructor
		~BlackJack(); // deconstructor

		// additional functions
		void shuffle();
		bool checkWin();
		int Deal();
		void playBlackJack();
		void exit();

	private:
		// private data members
		int size;	
		int PlayerCardsVal;
		int ComputerCardsVal;
		int cardIndex;
		int *deck;
		int playerscore;
		int computerscore;
};

#endif
