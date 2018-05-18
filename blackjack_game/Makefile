main: main.o blackjack.o
		g++ -o main main.o blackjack.o

main.o: main.cpp
		g++ -c main.cpp

blackjack.o: blackjack.cpp blackjack.h
		g++ -c blackjack.cpp

clean: 
		rm main *.o
