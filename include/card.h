#ifndef _H_CARD_
#define _H_CARD_

#include <string>
#include <iostream>

using namespace std;

// The mapping between integer value and string in card
static string facesStr[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

class card{
	private:  
		int face;
		string suit;

	public:
		// default constructor
		card();	

		// initial constructor
		card(int face, string suit);

		// copy constructor
		card(const card& other);

		// assignment operator
		card& operator=(card const& other);

		// '<' operator
		bool operator<(const card& other) const;  

		// '==' operator
		bool operator==(const card& other) const;  

		// print out card information
		string print() const;

		// get face value
		int getFace() const;
		
		// get suit value
		string getSuit() const;
};

card::card(){}

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

bool card::operator< (const card& other) const{
	bool result;
	if(this->getSuit() == other.getSuit()){
			result = (this->getFace() < other.getFace());
	}
	else{
		if(this->getSuit()=="Spader")
			result = false;
		if(this->getSuit()=="Club")
			result = true;
		if(this->getSuit()=="Diamond")
			result = (other.getSuit()!="Club");
		if(this->getSuit()=="Heart")
			result = (other.getSuit()=="Spader");
	}
	return result;
}

card::card(const int cardFace, const string cardSuit){
	face = cardFace;
	suit = cardSuit;
}

string card::print() const{
	return (facesStr[face-1] + " of " + suit);
}

int card::getFace() const{
	return face;
}

string card::getSuit() const{
	return suit;
}
#endif