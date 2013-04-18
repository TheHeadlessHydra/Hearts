#ifndef __CARD_H__
#define __CARD_H__

using namespace std;

#include <string>

class Card {
    public:
	// Some (static) constants and types for rank and suit.
	enum Rank {Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
		    Jack, Queen, King, Ace};
	static const string RankName;
	static const int numRanks;
	enum Suit {Spades, Diamonds, Clubs, Hearts};
	static const string SuitName;
	static const int numSuits;
	static const int numCards;
	// Two special cards, which are compared by value in various places
	static const Card TwoOfClubs;
	static const Card QueenOfSpades;

	// Constructors and destructor.
	// Cxr of no args creates the Ace of Spades, cos sometimes you
	// just gotta have a card, which you can then overwrite.
	Card ();
	// Preferred cxr
	Card (Rank r, Suit s);	
	// Takes a char string of length 2, which better be legal
	Card (string sCard);
	// Destructor
	~Card ();

	// Accessor fcns
	Rank getRank () const;
	Suit getSuit () const;
	int getHeartsValue () const;
 	
	// Static utility function to check if a two char string 
	// represents a legal card value
	static bool stringIsALegalCard (string s);

    private:
	Rank rank;
	Suit suit;
};

// Overloaded operators: We will define them in Card.cc so we need to
// make their prototypes visible here for clients.
extern bool operator== (const Card& c1, const Card& c2);
extern bool operator< (const Card& c1, const Card& c2);
extern ostream& operator<< (ostream &out, const Card &c);
extern istream& operator>> (istream& in, Card& c);

#endif /* __CARD_H__ */
