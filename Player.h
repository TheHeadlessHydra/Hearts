#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "CardPile.h"
#include "Card.h"
#include "trick.h"

class Player
{
protected:
	int m_iPlayerNumber;
	string m_sName;
	CardPile *m_hand;
	CardPile *m_discardPile;
	int m_totalScore;
public:
	// There are no constructors or destructors for the Player class!
	// Never try to directly create a Player class! This class
	// must always be an instance of one of its children. There MUST be a destructor.
	// The destructor will delete m_hand and m_discardPile. Calling delete
	// on these two will free memory of all cards within it (through destructor
	// of CardPile class in CardPile.{h,cc}).
	virtual ~Player();
	// Play card takes in a trick and figures out
	// what card it should play based on the information
	// in the trick. This function will also output
	// the information of what it is currently playing
	// to the console. 
	Card* PlayCard(trick *currentTrick);
	// Virtual functions that are the inner workings
	// of the PlayCard function. 
	virtual Card* lead() = 0;
	virtual Card* throwOff() = 0;
	virtual Card* followSuit(trick *currentTrick) = 0;

	// Accessor functions ----------
	// Hand functions
	int sizeOfHand();
	CardPile* getHand();
	void addToHand(Card *card);
	void removeFromHand(int iPos);
	bool removeFromHand(Card *card);
	Card* getFromHand(int iPos);
	void emptyHand();
	void printHand();

	// Discard functions
	int sizeOfDiscard();
	CardPile* getDiscard();
	void addToDiscard(Card *card); // Will increment m_totalScore with the proper hearts values as you add to the pile.
	void removeFromDiscard(int iPos);
	Card* getFromDiscard(int iPos);
	void emptyDiscard();
	void printDiscardPile();

	// Other function
	int heartsValue();
	int getPlayerNumber();
	string getName();
};

#endif
