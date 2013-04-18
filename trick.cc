// STD includes
#include <assert.h>
#include <iostream>
// Local includes
#include "trick.h"
#include "Player.h"

using namespace std;

trick::trick() : m_totalSize(0) {}

trick::trick(Card *ledCard, Player *playerWhoPlayed) : m_trumpCard(ledCard), m_trumpPlayer(playerWhoPlayed), m_totalSize(0) {}

trick::~trick()
{
	assert (this->getSize() == 0); // WARNING! Trying to delete a trick with cards still inside!
}

int trick::getCurrentSize() { return m_totalSize; }
Card trick::getTrumpCard() { return *(m_trumpCard); }

void trick::addToTrick(Card *cardToAdd, Player *playerWhoPlayed)
{	
	assert (this->getSize() < 5); // Cannot add more than 4 cards to the trick

	this->addCard(cardToAdd);
	if (m_totalSize == 0)
	{
		m_trumpCard = cardToAdd;
		m_trumpPlayer = playerWhoPlayed;
	}
	else
	{
		if( cardToAdd->getSuit() == m_trumpCard->getSuit() && cardToAdd->getRank() > m_trumpCard->getRank() )
		{
			m_trumpCard = cardToAdd;
			m_trumpPlayer = playerWhoPlayed;
		}
	}
	m_totalSize++;


}

Player* trick::getWinner( void )
{
	assert (this->getSize() == 4); // Trying to take the trick when all four cards have not been played

	cout << "  " << m_trumpPlayer->getName() << " won the trick and added the following cards:" << endl;
	cout << "    ";

	// Remove the cards in the current trick.
	for(int i = 0; i < this->getSize(); i++)
	{	
		cout << *(this->getCard(i)) << " ";
		m_trumpPlayer->addToDiscard( this->getCard(i) );
		m_totalSize--;
	}
	this->clearPile();
	cout << endl << endl;
	return m_trumpPlayer;
}




