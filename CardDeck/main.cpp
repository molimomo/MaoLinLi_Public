/*
	Apple Inc. Programming excercise - Deck of Card

	Author: Mao-Lin Li

	Date: 12/27/2014
*/

#include <iostream>
#include <string>

#include "poker.h"
#include "uno.h"

using namespace std;

int main(int argc, char* argv[]){

	int num_seq = 0;		// # of card sequence should be checked
	int type_card = 0;		// type of card game 
	int	type_shuffle = 0;	// type of shuffle

	cout<<"Hello!, Welcome to the World of Card Game!"<<endl;
	
	// Fetch type of card and the value of card sequence
	while(type_card<1 || type_card>2){
		cout<<"Please select the type of card - (1: Poker, 2:Uno)"<<endl;
		cin>>type_card;
	}
	while(num_seq<2){
		cout<<"Please input the value of card sequence you want to check - (Minimum: 2)"<<endl;
		cin>>num_seq;
	}
	
	// Fetch type of shuffle
	while(type_shuffle<1 || type_shuffle>2){
		cout<<"Please input the type of shuffle you want to do - "<<endl;
		cout<<"(1: Different from the most recent shuffle.)"<<endl;
		cout<<"(2: Different from all previous shuffles.)"<<endl;
		cin>>type_shuffle;
	}
	
	// Initialize the card game according to the type of card
	cardGame *cardGame_ptr = NULL;
	switch(type_card){
		case 1:
			cardGame_ptr = new poker(num_seq,type_shuffle);
			cout<<"You selected Poker!"<<endl;
			break;
		case 2:
			cardGame_ptr = new uno(num_seq,type_shuffle);
			cout<<"You selected Uno!"<<endl;
			break;
		default:
			cout<<"Invalid Type!"<<endl;
			break;
	}

	// Start run main program
	cout<<"Create deck of cards."<<endl<<endl;
	cardGame_ptr->printDeck();
	cout<<endl<<endl;

	cout<<"First shuffle."<<endl<<endl;
	cardGame_ptr->shuffle();
	cardGame_ptr->printDeck();
	cout<<endl<<endl;
	
	cout<<"Start new shuffle."<<endl<<endl;
	cardGame_ptr->shuffle();
	while(cardGame_ptr->checkSeq()){
		cout<<"Found duplicate sequence! Re-shuffle!"<<endl;
		cardGame_ptr->shuffle();
	}
	cout<<endl<<endl;

	cout<<"Done!"<<endl;	
	cardGame_ptr->printDeck();
	cout<<endl<<endl;

	return 0;
}
