#ifndef _H_UNO_
#define _H_UNO_


#define NUM_OF_CARD_UNO 108
#define NUM_OF_SUIT_UNO 5
#define NUM_OF_SHUFFLE_UNO 30

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <ctime>
#include <iomanip>

#include "cardGame.h"

using namespace std;

/* Comparator for UNO:
	if two cards have the same suit, then compare their faces.
	else Red < Green < Blue < Yellow < Black 
*/
struct unoCompare
{
	bool operator() (const card& lhs, const card& rhs) const{
		bool result;
		if(lhs.getSuit() == rhs.getSuit()){
			result = (lhs.getFace() < rhs.getFace());
		}
		else{
			if(lhs.getSuit()=="Black")
				result = false;
			else if(lhs.getSuit()=="Yellow")
				result = (rhs.getSuit()=="Black");
			else if(lhs.getSuit()=="Blue")
				result = (rhs.getSuit()=="Yellow" || rhs.getSuit()=="Black");
			else if(lhs.getSuit()=="Green")
				result = (rhs.getSuit()=="Blue" || rhs.getSuit()=="Yellow" || rhs.getSuit()=="Black");
			else
				result = (rhs.getSuit()=="Green" || rhs.getSuit()=="Blue" || rhs.getSuit()=="Yellow" || rhs.getSuit()=="Black");
		}
		return result;
	}
};

// The map to record the sequence of each card.
// key: card
// value: list<card>
// comparator: unoCompare
typedef map< card, list<card>, unoCompare> unoSeqRec;

class uno: public cardGame{
	public:
		uno(int num_seq, int type_shuffle);
		void shuffle();
		bool checkSeq() const;
		void printDeck() const;
		void printRec(bool old) const;

	private:
		unoSeqRec newRec;
		vector<unoSeqRec> allRec;
};
// The constructor to initialize the configuration of UNO cards.
uno::uno(int num_seq, int type_shuffle)
{
	string suites[] = {"Red", "Yellow","Green","Blue","Black"};
	string faces[] = {"0","1","2","3","4","5","6","7","8","9","Skip","Draw Two","Reverse","Wild","Wild Draw Four"};
	deck = new card[NUM_OF_CARD_UNO];
	numOfSeq = num_seq;
	numOfCard = NUM_OF_CARD_UNO;
	numOfSuit = NUM_OF_SUIT_UNO;
	numOfShuffle = NUM_OF_SHUFFLE_UNO;
	typeOfShuffle = type_shuffle;
	int cardCount = 0;
	int colorIdx = 0;

	//Initialize four sets of cards. (Red, Yellow, Green, Blue) [0 * 1, (1-9) * 2, (Skip, Draw Two, Reverse) * 2]
	for(int color = 0; color < 4; color++){
		colorIdx = color * 25;
		deck[colorIdx] = card(faces[0],suites[color]);
		cardCount++;
		for(int faceIdx = 1;faceIdx < 13; faceIdx++, cardCount+=2){
			deck[cardCount] = card(faces[faceIdx],suites[color]);
			deck[cardCount+1] = card(faces[faceIdx],suites[color]);
		}
	}
	//Initilaize special action cards. (Black: Wild, Wild Draw Four) * 4
	for(int faceIdx = 13;faceIdx<15;faceIdx++){
		for(int i= 0;i<4;i++, cardCount++){
			deck[cardCount] = card(faces[faceIdx],suites[4]);
		}
	}
}

// Shuffle cards.
// Type 1: Record the most recent shuffle 
// Type 2: Record all the previous shuffle
void uno::shuffle()
{
	// Shuffling
	for(int first = 0 ; first < numOfCard;first++){
		int second = (rand()+time(0)) % numOfCard;
		card temp = deck[first];
		deck[first] = deck[second];
		deck[second] = temp;
	}

	// Record all card sequences in map.
	if(newRec.size()!=0)
		newRec.clear();
	for(int i=0;i <= (numOfCard - numOfSeq) ; i++){
		for(int j=i+1;j<numOfSeq+i;j++){
			newRec[deck[i]].push_back(deck[j]);
		}
	}

	if(allRec.size() > 0){
		if(typeOfShuffle==2){
			allRec.push_back(newRec);
		}
	}
	// The first shuffle result
	else{
		allRec.push_back(newRec);
	}
}


// Check card sequence
// Return true is there is the same card sequence within two shuffles.
bool uno::checkSeq() const
{
	// If the number of previous shuffles is equal to defined limitation, stop checking sequence and return the latest shuffle result; 
	if(allRec.size()==numOfShuffle){
		cout<<"Already tried "<<numOfShuffle<<" shuffles, return the latest shuffle."<<endl;
		return false;
	}
	
	// Check all previous shuffles.
	for(int i=0; i<=(numOfCard - numOfSeq); i++){
		for(vector<unoSeqRec>::const_iterator it = allRec.begin();it!=allRec.end();it++){
			unoSeqRec tmpRec = *it;
			unoSeqRec::const_iterator old = tmpRec.find(deck[i]);
			if(old!=tmpRec.end()){
				list<card> oldSeq = old->second;
				list<card> newSeq = (newRec.find(deck[i]))->second;
				list<card>::const_iterator oi = oldSeq.begin();
				list<card>::const_iterator ni = newSeq.begin();
				bool seqCheck = true;
				for(;oi!=oldSeq.end() && ni!=newSeq.end() ;oi++,ni++){
					// not the same 
					if(!((*oi)==(*ni))){
						seqCheck = false;
						break;
					}
				}
				// The new shuffle has the same card sequence with one of previous shuffles.
				if(seqCheck){
					return true;
				}
			}
		}
	}
	return false;
}

// Print out all cards in a deck.
void uno::printDeck() const
{
	cout<<left;
	for(int i = 0;i <numOfCard;i++){
		cout<<setw(25)<<deck[i].print();
		if((i+1)%numOfSuit==0)
			cout<<endl;
	}
}

// Print out all the records fo card sequence and write them into a text file.
void uno::printRec(bool old) const
{
	ofstream recFile;
	unoSeqRec rec;
	if(old){
		rec = allRec[0];
		recFile.open("old_uno.txt");
	}
	else{
		rec = newRec;
		recFile.open("new_uno.txt");
	}
	for(unoSeqRec::const_iterator it = rec.begin();it!=rec.end();it++){
		cout<<"Card: "<<(it->first).print();
		recFile<<"Card: "<<(it->first).print();
		cout<<" Go: ";
		recFile<<" Go: ";
		for(list<card>::const_iterator si = (it->second).begin();si!=(it->second).end();si++){
			cout<<(si)->print()<<", ";
			recFile<<(si)->print()<<", ";
		}
		cout<<endl;
		recFile<<endl;
	}
	recFile.close();
}
#endif