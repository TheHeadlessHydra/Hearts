#ifndef _TRICK_H_
#define _TRICK_H_

#include "Card.h"
#include "CardPile.h"

// Forward decleration
class Player;

class trick : public CardPile
{
private:
	Card *m_trumpCard;
	Player *m_trumpPlayer;
	int m_totalSize;
public:
	trick();
	trick(Card *ledCard, Player *playerWhoPlayed);
	~trick();

	// Accessor functions
	int getCurrentSize();
	Card getTrumpCard();
	void addToTrick(Card *cardToAdd, Player *playerWhoPlayed);
    Player* getWinner( void ); 

};

#endif
