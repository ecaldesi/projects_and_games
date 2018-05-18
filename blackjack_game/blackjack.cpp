// Elisabetta Caldesi
// BlackJack class implementation

#include "blackjack.h" // include class definition
#include <iostream>
#include <cstdlib>

using namespace std;

// constructor
BlackJack::BlackJack(int n) {
	
	// initialize deck of cards
	deck = new int[n]; 
	for (int i=0; i< n; i++){
		deck[i] = (i % 10) +1;
	}
	
	// set size of deck equal to int n
	size = n;

	// this will be index of the deck array
	cardIndex = 0;

	// initial cards value of the computer
	ComputerCardsVal = 0;	

	// initial cards value of the player	
	PlayerCardsVal = 0;

	// initial total score of the player
	playerscore = 0;
	
	// initial total score of the computer
	computerscore = 0;
}

// deconstructor 
BlackJack::~BlackJack() {

	delete [] deck;

}

// shuffles the deck
void BlackJack::shuffle() {

	int j, temp;

	for (int i=size-1; i>=0; i--){
		j= rand() % size;
		temp= deck[i];
		deck[i]= deck[j];
		deck[j]= temp;
	}	

}

// deals cards from the deck
int BlackJack::Deal() {
	
	// set value of aces
	if (deck[cardIndex] == 14 ) {
		deck[cardIndex] = 11;

	// set value of jacks, queens and kings to 10
	} else if (deck[cardIndex] >=11) {
		deck[cardIndex] = 10;
	}	

	// if there's only 15 cards left, make a new deck and shuffle
	if (cardIndex = 52-15) {
		for (int i=0; i< size; i++){
			deck[i] = (i % 13) +2;
		}
		shuffle();
		cardIndex = 0;
		
	}	
	return deck[cardIndex++];
	
}

// check for winner
bool BlackJack::checkWin(){
	
	bool player;

	// if the computer scores more than 21, player wins
	if (ComputerCardsVal > 21) {

		player = true;
		cout << "congratulations player, you won! " << endl;		
		playerscore += 1;
		return player;
		
	}
		
	// if the player's score is higher than the computer's
	if (ComputerCardsVal!=0){
		if (PlayerCardsVal > ComputerCardsVal) {

			player = true;
			cout << "congratulations player, you won!" << endl;
			playerscore += 1;
			return player;
		}
	}

	if (ComputerCardsVal!=0){
		// if the computer's score is higher than the player's
		if (PlayerCardsVal < ComputerCardsVal) {

			player = false;
			cout << "sorry player, you lost! " << endl;
			computerscore += 1;
			return player;
		}
	}

	if (ComputerCardsVal!=0){
		// if there is a tie, the computer automatically wins
		if (PlayerCardsVal == ComputerCardsVal) {

			player = false;
			cout << "sorry player, it was a tie so you lost!" << endl;
			computerscore += 1;	
			return player;
		}
	}		
}

// function that is used to play the game
void BlackJack::playBlackJack() {

	int dealtCard;	
	char choice = 'h';
	bool win;

	shuffle(); // shuffle deck

	// player's turn						
	while (choice == 'h') {

		dealtCard = Deal();
		cout << "Your card is : " << dealtCard << endl;

		PlayerCardsVal =  PlayerCardsVal + dealtCard;

		cout << "Your total score is: " << PlayerCardsVal << endl;


		// if the plater's score is higher than 21, the computer wins.
		if (PlayerCardsVal > 21) {
			cout << "Sorry player, you lost!" << endl;
			computerscore += 1;
			cout << "Player score: " << playerscore << ", Computer score: " << computerscore<< endl;
			
			return;
				
		}

		
		// ask for choice
		cout << "Do you want to hit(h) or stand(s)? " << endl; 
		cin >> choice;	

		// check for right input
		while (choice != 'h' && choice != 's') {
			cout << "please enter new choice " << endl;
			cin >> choice;
		}		
	}

	// computer's turn
	while (choice == 's') {

		dealtCard = Deal();
		ComputerCardsVal += dealtCard;

		cout << "Computer score: " << ComputerCardsVal << endl;

		// if computer's cards value is greater than 17, stop dealing
		if (ComputerCardsVal >=17){
			break;
		}
	}
	
	// check for winner
	checkWin();

	cout << "Player score: " << playerscore << ", Computer score: " << computerscore<< endl;

	// set choice back to h at the end of the game
	choice = 'h';


}

// function that asks if the player wants to play another hand
void BlackJack::exit() {

	char answer = 'n';
	
	while (answer == 'n') {
		
		playBlackJack();
		cout << "do you want to end the game? Yes (y) or no (n)? " << endl;
		cin >> answer;
		if (answer == 'n') {

			// set values equal to 0
			PlayerCardsVal= 0;
			ComputerCardsVal = 0;
		}	
	}
	return;
}

