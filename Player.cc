#include <iostream>
#include "Player.h"

using namespace std;

Player::~Player()
{
	delete m_hand;
	delete m_discardPile;
}

Card* Player::PlayCard(trick *currentTrick)
{
	if(currentTrick->getCurrentSize() == 0)
		return lead();

	enum Card::Suit leadSuit = (currentTrick->getTrumpCard()).getSuit();

	// Find out if the player has a card of the
	// same type as the lead card.
	bool bHasSuitOfType = false;
	for(int i = 0; i < this->sizeOfHand(); i++)
	{
		if( (this->getFromHand(i))->getSuit() == leadSuit )
		{
			bHasSuitOfType = true;
			break;
		}
	}

	if(!bHasSuitOfType)
		return throwOff();
	else
		return followSuit(currentTrick);
}

// Hand functions
int Player::sizeOfHand(){ return m_hand->getSize(); }
CardPile* Player::getHand(){ return m_hand; }
void Player::addToHand(Card *card){ m_hand->addCard(card); }
void Player::removeFromHand(int iPos){ m_hand->removeCard(iPos); }

bool Player::removeFromHand(Card *card)
{
	for(int i = 0; i < this->sizeOfHand(); i++)
	{
		if (this->getFromHand(i) == card)
		{
			this->removeFromHand(i);
			return true;
		}
	}
	return false;
}

Card* Player::getFromHand(int iPos){ return m_hand->getCard(iPos); }

void Player::emptyHand()
{ 
	delete this->m_hand; // Destructor of CardPile deletes all cards in m_hand
	this->m_hand = new CardPile;
}

void Player::printHand(){ m_hand->print(); }

// Discard functions
int Player::sizeOfDiscard() { return m_discardPile->getSize(); }
CardPile* Player::getDiscard(){ return m_discardPile; }

void Player::addToDiscard(Card* card)
{
	m_totalScore = m_totalScore + card->getHeartsValue();
	m_discardPile->addCard(card); 
}

void Player::removeFromDiscard(int iPos){ m_discardPile->removeCard(iPos); }
Card* Player::getFromDiscard(int iPos){ return m_discardPile->getCard(iPos); }

void Player::emptyDiscard()
{ 
	delete this->m_discardPile; // Destructor of CardPile deletes all cards in m_hand
	this->m_discardPile = new CardPile;
}

void Player::printDiscardPile(){ m_discardPile->print(); }

// Other functions
int Player::heartsValue(){ return m_totalScore; }
int Player::getPlayerNumber() { return m_iPlayerNumber; }
string Player::getName() { return m_sName; }
