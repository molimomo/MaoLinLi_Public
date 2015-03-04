#ifndef _H_POKER_
#define _H_POKER_


#define NUM_OF_CARD_POKER 52
#define NUM_OF_SUIT_POKER 4
#define NUM_OF_SHUFFLE_POKER 30

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <ctime>
#include <iomanip>

#include "cardGame.h"

using namespace std;

/* Comparator for Poker:
	if two cards have the same suit, then compare their faces.
	else Club < Dimond < Heart < Spader 
*/
struct pokerCompare
{
	bool operator() (const card& lhs, const card& rhs) const{
		bool result;
		if(lhs.getSuit() == rhs.getSuit()){
			result = (lhs.getFace() < rhs.getFace());
		}
		else{
			if(lhs.getSuit()=="Spader")
				result = false;
			if(lhs.getSuit()=="Club")
				result = true;
			if(lhs.getSuit()=="Diamond")
				result = (rhs.getSuit()!="Club");
			if(lhs.getSuit()=="Heart")
				result = (rhs.getSuit()=="Spader");
		}
		return result;
	}
};

// The map to record the sequence of each card.
// key: card
// value: list<card>
// comparator: pokerCompare
typedef map< card, list<card>, pokerCompare> pokerSeqRec;

class poker: public cardGame{
	public:
		poker(int num_seq, int type_shuffle);
		void shuffle();
		bool checkSeq() const;
		void printDeck() const;
		void printRec(bool old) const;

	private:
		pokerSeqRec newRec;
		vector<pokerSeqRec> allRec;
};

// The constructor to initialize the configuration of UNO cards.
poker::poker(int num_seq, int type_shuffle)
{
	string suites[] = {"Heart", "Diamond","Club","Spader"};
	string faces[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	deck = new card[NUM_OF_CARD_POKER];											
	numOfSeq = num_seq;
	numOfCard = NUM_OF_CARD_POKER;
	numOfSuit = NUM_OF_SUIT_POKER;
	numOfShuffle = NUM_OF_SHUFFLE_POKER;
	typeOfShuffle = type_shuffle;
	for(int count = 0;count<numOfCard;count++)
		deck[count] = card(faces[count%(NUM_OF_CARD_POKER/NUM_OF_SUIT_POKER)], suites[count/(NUM_OF_CARD_POKER/NUM_OF_SUIT_POKER)]);
}

// Shuffle cards.
// Type 1: Record the most recent shuffle 
// Type 2: Record all the previous shuffle
void poker::shuffle()
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

bool poker::checkSeq() const
{
	// If the number of previous shuffles is 30, stop checking sequence and return the latest shuffle result; 
	if(allRec.size()==numOfShuffle){
		cout<<"Already tried "<<numOfShuffle<<" shuffles, return the latest shuffle."<<endl;
		return false;
	}
	
	// Check all previous shuffles.
	for(int i=0; i<=(numOfCard - numOfSeq); i++){
		for(vector<pokerSeqRec>::const_iterator it = allRec.begin();it!=allRec.end();it++){
			pokerSeqRec tmpRec = *it;
			pokerSeqRec::const_iterator old = tmpRec.find(deck[i]);
			//Get corresponsing card's sequence record.
			if(old!=tmpRec.end()){
				list<card> oldSeq = old->second;
				list<card> newSeq = (newRec.find(deck[i]))->second;
				list<card>::const_iterator oi = oldSeq.begin();
				list<card>::const_iterator ni = newSeq.begin();
				// Check sequence
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
void poker::printDeck() const
{
	cout<<left;
	for(int i = 0;i <numOfCard;i++){
		cout<<setw(19)<<deck[i].print();
		if((i+1)%numOfSuit==0)
			cout<<endl;
	}
}

// Print out all the records fo card sequence and write them into a text file.
void poker::printRec(bool old) const
{
	ofstream recFile;
	pokerSeqRec rec;
	if(old){
		rec = allRec[0];
		recFile.open("old_poker_deck.txt");
	}
	else{
		rec = newRec;
		recFile.open("new_poker_deck.txt");
	}
	for(pokerSeqRec::const_iterator it = rec.begin();it!=rec.end();it++){
		cout<<"Card: "<<(it->first).print();
		recFile<<"Card: "<<(it->first).print();
		cout<<" Seq: ";
		recFile<<" Seq: ";
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