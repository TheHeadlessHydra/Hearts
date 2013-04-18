#ifndef _DECK_H_
#define _DECK_H_

#include <iostream>
#include "CardPile.h"

using namespace std;

// A deck of cards is a kind of card pile.  It should start out with the
// normal 52 cards; one of each (suit,rank) pair.
// A deck might be read in via operator>> or just generated (like buying a
// brand new deck of cards); if generated, it is not shuffled by default 
// but it is sorted.
class Deck : public CardPile {
    public:
    // Stores the amount of cards in a deck
    const int m_iDeckSize;
	// Constructor creates an empty deck.
	Deck ();
	virtual ~Deck();
	// Take an existing (ideally, empty) deck and fill it with the
	// usual suspects of 52 cards by iterating through the elements of
	// Card::Rank and Card::Suit.
	void generate();
	// Check that the deck of cards does indeed contain the usual 
	// 52 suspects; this isn't hard if you know your STL containers.
	bool playingWithAFullDeck () const;
};

// Take an existing (ideally, empty) deck and read in 52 cards from the
// indicated input stream, making use of operator>>(istream&, Card&).
// Make sure that you are playingWithAFullDeck at the end.
// The ordering should be so that the last card read in will be on the top
// of the deck.
extern istream& operator>> (istream& in, Deck& deck);

#endif
