#include <string>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include "Card.h"

using namespace std;

const string Card::RankName = "23456789TJQKA";
const string Card::SuitName = "SDCH";
const int Card::numRanks = RankName.length();
const int Card::numSuits = SuitName.length();
const int Card::numCards = Card::numRanks * Card::numSuits;
const Card Card::TwoOfClubs (Card::Two, Card::Clubs);
const Card Card::QueenOfSpades (Card::Queen, Card::Spades);

// Default Constructor
Card::Card() : rank(Ace), suit(Spades) {}

// Constructor: takes a Rank r and Suit s
Card::Card (Rank r, Suit s) : rank(r), suit(s) {}	

// Constructor: takes a string of length 2, and creates a card
Card::Card (string sCard)
{
	// Check if the string is a legal card before setting. 
	if (!stringIsALegalCard(sCard))
		exit(1);
	rank = static_cast<Rank>(Card::RankName.find(sCard.substr(1,1)));
	suit = static_cast<Suit>(Card::SuitName.find(sCard.substr(0,1)));
}

// Destructor
Card::~Card () {}

// Gets value of a card (1 for heart, 13 for Q spades, 0 for other)
int Card::getHeartsValue () const
{
	if (suit==3) 
		return 1;
	else if ((suit==0) && (rank==10))
		return 13;
	else
		return 0;
}

// Gets the rank of a card
Card::Rank Card::getRank() const { return rank; }

// Gets the suit of a card
Card::Suit Card::getSuit() const { return suit; }

// returns TRUE if the card is legal (actuall in a standard 52 deck)
bool Card::stringIsALegalCard(string tempCard)
{
	// Holds int for '.find' statement, the returned int the substr is found
	// If the substring is not found, it returns a string::npos (large integer)
	size_t foundRank,foundSuit;

	if (tempCard.length()!=2) 
		return false;
	else 
	{
		foundRank=Card::RankName.find(tempCard.substr(0,1));
		foundSuit=Card::SuitName.find(tempCard.substr(1,1));
		return ( (foundRank!=string::npos) && (foundSuit!=string::npos) );
	}
}

// < Overload Operator to check if a cardA is less than cardB based on rank and suit
bool operator< (const Card& c1, const Card& c2)
{
	if (c1.getRank()<c2.getRank())
		return true;
	return ( (c1.getRank()==c2.getRank()) && (c1.getSuit()<c2.getSuit()) );
}

// == Overload Operator to check if cardA equal to cardB on rank and suit
bool operator== (const Card& c1, const Card& c2)
{
	return ( (c1.getRank()==c2.getRank()) && (c1.getSuit()==c2.getSuit()) );
}

// << Overload Operator to print out a Card
ostream& operator<< (ostream &out, const Card &c)
{
	out << Card::RankName.at(static_cast<int>(c.getRank()));
	out << Card::SuitName.at(static_cast<int>(c.getSuit()));
	return out;
}

// >> Overload Operator to take in a Card
istream& operator>> (istream& in, Card& c)
{
	// Take in a string and see if it is a valid card
	string newString;
	in >> newString;
	if( !Card::stringIsALegalCard(newString) )
	{
		cerr << "Error, " << newString << " is not a legal card. Aborting." << endl;
		exit(1);
	}
	
	// If it is, take its values and make a new card with it
	char newRank = newString[0];
	char newSuit = newString[1];
	Card newCard( 
		static_cast<Card::Rank>(Card::RankName.find(newRank)), 
		static_cast<Card::Suit>(Card::SuitName.find(newSuit)) );
	
	// Set the given card to be the newly created card
	c = newCard;
	return in;
}
