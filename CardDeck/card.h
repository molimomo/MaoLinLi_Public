#ifndef _H_CARD_
#define _H_CARD_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class card{
	private:  
		string face;
		string suit;

	public:
		// default constructor
		card(){};	

		// initial constructor
		card(string face, string suit);

		// copy constructor
		card(const card& other);

		// assignment operator
		card& operator=(card const& other);

		// '==' operator
		bool operator==(const card& other) const;  

		// print out card information
		string print() const;

		// get face value
		string getFace() const;
		
		// get suit value
		string getSuit() const;
};

card::card(const card& other){
	face = other.face;
	suit = other.suit;
}

card& card::operator=(card const& other){
	if((void*)this == (void*)&other)
		return *this;
	
	face = other.getFace();
	suit = other.getSuit();
	return *this;
}

bool card::operator==(const card& other) const {
	return (this->getSuit() == other.getSuit()) && (this->getFace() == other.getFace());
}

card::card(const string cardFace, const string cardSuit){
	face = cardFace;
	suit = cardSuit;
}

string card::print() const{
	return (face + " of " + suit);
}

string card::getFace() const{
	return face;
}

string card::getSuit() const{
	return suit;
}
#endif