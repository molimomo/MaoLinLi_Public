#include <iostream>
#include <string>
#include "card.h"
#include "deckOfCards.h"

using namespace std;

int main(){

	//card currentCard;
	cout<<"Create deck of cards."<<endl<<endl;
	deckOfCards deck;
	deck.printDeck();
	cout<<endl<<endl;


	cout<<"First shuffle."<<endl<<endl;
	deck.shuffle();
	deck.printDeck();
	cout<<endl<<endl;
	//cout<<"Old Rec: "<<endl;
	//deck.printRec(true);
	
	cout<<"Start new shuffle."<<endl<<endl;
	deck.shuffle();
	while(deck.checkSeq()){
		cout<<"Found duplicate sequence! Re-shuffle!"<<endl;
		deck.shuffle();
	}
	cout<<endl<<endl;

	cout<<"Done!"<<endl;	
	deck.printDeck();
	cout<<endl<<endl;
	//cout<<"New Rec: "<<endl;
	//deck.printRec(false);
	return 0;
}
