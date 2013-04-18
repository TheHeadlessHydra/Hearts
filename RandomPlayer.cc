// std includes
#include <algorithm>
#include <iostream>
// local includes
#include "RandomPlayer.h"
#include "Card.h"
#include "CardPile.h"

using namespace std;

RandomPlayer::RandomPlayer(int iPlayerNumber, string sName, int iSeed)
{
	Player::m_iPlayerNumber = iPlayerNumber;
	Player::m_sName = sName;
	Player::m_hand = new CardPile;
	Player::m_discardPile = new CardPile;
	m_totalScore = 0;
	m_randomGenerator.seed(iSeed);
}

RandomPlayer::~RandomPlayer(){}

Card* RandomPlayer::lead()
{
	// Implementation:
	// Lead with a random card

	int iRandomNumber = m_randomGenerator(0, (this->sizeOfHand()-1) );
	assert (iRandomNumber < this->sizeOfHand()); // Or else we would be out of bounds

	cout << "  " << this->getName() << " led " << *(this->getFromHand(iRandomNumber)) << endl;
	return this->getFromHand(iRandomNumber);
}

Card* RandomPlayer::throwOff()
{
	// Implementation:
	// Throw off with a random card

	int iRandomNumber = m_randomGenerator(0, (this->sizeOfHand()-1) );
	assert (iRandomNumber < this->sizeOfHand()); // Or else we would be out of bounds

	cout << "  " << this->getName() << " threw off " << *(this->getFromHand(iRandomNumber)) << endl;
	return this->getFromHand(iRandomNumber);
}

Card* RandomPlayer::followSuit(trick *currentTrick)
{
	enum Card::Suit trumpSuit = (currentTrick->getTrumpCard()).getSuit();

	// Create a CardPile for the suits that are the same as the trump card
	CardPile *listOfTrumpSuitCards = new CardPile;

	// Iterate through the hand and add the cards that are the same suit as the trump card
	for (int i = 0; i < this->sizeOfHand(); i++)
	{
		Card *currentCard = this->getFromHand(i);
		if ( currentCard->getSuit() == trumpSuit )
			listOfTrumpSuitCards->addCard(currentCard);
	}


	// Choose a random card from the pile of cards that are the same suit
	Card* cardToPlay = listOfTrumpSuitCards->getCard( ( m_randomGenerator(0, (listOfTrumpSuitCards->getSize()-1)) ) );
	// Display the value
	cout << "  " << this->getName() << " followed suit with " << *(cardToPlay) << endl;

	// EVERY CARD IN THE CARDPILE MUST BE REMOVED!!!
	// If this does not happen, the destructor of CardPile will
	// DELETE and free the memory of every card in the CardPile
	// causing many many hard to find seg faults!
	listOfTrumpSuitCards->clearPile();
	delete listOfTrumpSuitCards;

	return cardToPlay;
}
