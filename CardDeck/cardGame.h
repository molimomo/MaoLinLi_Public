#ifndef _H_CARD_GAME_
#define _H_CARD_GAME_

#include <iostream>
#include "card.h"

class cardGame{
	public:
		cardGame(){};
		// shuffle function
		virtual void shuffle() = 0;
		// check card sequence
		virtual bool checkSeq() const = 0;
		// print out deck of card
		virtual void printDeck() const = 0;
		// print out card sequence record
		virtual void printRec(bool old) const = 0;
	
	protected:
		// deck of card
		card *deck;
		// number of cards
		int numOfCard;
		// number of suits
		int numOfSuit;
		// number of card sequence
		int numOfSeq;
		// number of the maximum shuffle 
		int numOfShuffle;
		// type of shuffle 
		int typeOfShuffle;
};
#endif