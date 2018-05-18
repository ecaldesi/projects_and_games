// Elisabetta Caldesi
// main Driver

#include "blackjack.h" // class definition

#include <iostream>
using namespace std;
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	
	// make the seed random
	srand (time(NULL));
	
	// play Black Jack	
	BlackJack b;
	
	b.shuffle();
	b.exit();

return 0;
}
