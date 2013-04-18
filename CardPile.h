#ifndef _CARDPILE_H_
#define _CARDPILE_H_

using namespace std;

#include <vector>
#include "Card.h"
#include "PRNG.h"


class CardPile : private vector<Card*> {
    public:
	// Constructors and destructor
	CardPile ();
	virtual ~CardPile (); // Deletes ALL cards in the CardPile! YOU CANNOT REFERENCE THEM ANYMORE AFTER THE CardPile DIES ****

	void setRandomSeed(uint32_t randomSeed);
	virtual void print();
	int heartsValue();
	void shuffle(); 

	// Accessor functions
	int getSize() const;					     	 // Get size of the CardPile
	vector<Card*>::const_iterator getBegin() const;	 // Gives you the beginning iterator
	vector<Card*>::const_iterator getEnd() const;	 // Gives you the ending iterator
	void addCard(Card *card);						 // Add given card
	bool removeCard(int iPos);			 			 // Remove card at position iPos - Does not delete! Owner responsible for deleting values
	bool removeCard(Card *card);		 			 // Remove given card - Does not delete! Owner responsible for deleting values
	Card* getCard(int iPos) const;		 		     // Get card at position iPos
	void clearPile();
 
    private:
	PRNG prng;
	static const uint32_t DefaultRandomSeed;
};

#endif
