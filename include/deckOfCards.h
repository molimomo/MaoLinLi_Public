#ifndef _H_DECK_OF_CARDS_
#define _H_DECK_OF_CARDS_


#define NUM_OF_CARD 52
#define NUM_OF_SEQ 2
#define NUM_OF_SUIT 4

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "card.h"

using namespace std;

struct cardCompare
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

typedef map< card, list<card>, cardCompare> seqRec;

class deckOfCards{
	public:
		deckOfCards();
		void shuffle();
		bool checkSeq() const;
		void printDeck() const;
		void printSeq() const;
		void printRec(bool old) const;

	private:
		card *deck;
		int currentCard;
		static const int numOfSuit = NUM_OF_SUIT;
		static const int numOfCard = NUM_OF_CARD;
		static const int numOfSeq = NUM_OF_SEQ; 
		seqRec oldRec;
		seqRec newRec;
		bool firstRec;
};


bool deckOfCards::checkSeq() const
{
	bool result = false;
	for(int i=0; i<=(numOfCard - numOfSeq); i++){
		//cout<<"Target card: "<<deck[i].print()<<endl;
		seqRec::const_iterator old = oldRec.find(deck[i]);
		
		// Compare sequence
		if(old!=oldRec.end()){
			list<card> oldSeq = old->second;
			list<card> newSeq = (newRec.find(deck[i]))->second;
			list<card>::const_iterator oi = oldSeq.begin();
			list<card>::const_iterator ni = newSeq.begin();
			bool seqCheck = true;
			for(;oi!=oldSeq.end() && ni!=newSeq.end() ;oi++,ni++){
				//cout<<"old seq: "<<(*oi).print()<<endl;
				//cout<<"new seq: "<<(*ni).print()<<endl;
				// not the same 
				if(!((*oi)==(*ni))){
					seqCheck = false;
					break;
				}
				// same
				else{
					//cout<<"advance... # "<<i<<endl;
				}
			}
			if(seqCheck)
				return true;
		}
		else{
			//cout<<"Cannot find card sequence in old sequence."<<endl;
		}
	}
	return result;
}

void deckOfCards::printRec(bool old) const
{
	ofstream recFile;
	seqRec rec;
	if(old){
		rec = oldRec;
		recFile.open("old.txt");
	}
	else{
		rec = newRec;
		recFile.open("new.txt");
	}
	for(seqRec::const_iterator it = rec.begin();it!=rec.end();it++){
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

void deckOfCards::printDeck() const
{
	cout<<left;
	for(int i = 0;i <numOfCard;i++){
		cout<<setw(19)<<deck[i].print();
		if((i+1)%numOfSuit==0)
			cout<<endl;
	}
}

deckOfCards::deckOfCards()
{
	int faces[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
	string suites[] = {"Heart", "Diamond","Club","Spader"};
	deck = new card[numOfCard];
	currentCard = 0;
	firstRec = true;
	for(int count = 0;count<numOfCard;count++)
		deck[count] = card(faces[count%13], suites[count/13]);
}

void deckOfCards::shuffle()
{
	currentCard = 0;
	for(int first = 0 ; first < numOfCard;first++){
		int second = (rand()+time(0)) % numOfCard;
		card temp = deck[first];
		deck[first] = deck[second];
		deck[second] = temp;
	}

	if(firstRec){
		for(int i=0;i <= (numOfCard - numOfSeq) ; i++){
			for(int j=i+1;j<numOfSeq+i;j++){
				oldRec[deck[i]].push_back(deck[j]);
			}
		}
		firstRec = false;
	}
	else{
		if(newRec.size()!=0)
			newRec.clear();
		for(int i=0;i <= (numOfCard - numOfSeq) ; i++){
			for(int j=i+1;j<numOfSeq+i;j++){
				newRec[deck[i]].push_back(deck[j]);
			}
		}
	}
}
#endif