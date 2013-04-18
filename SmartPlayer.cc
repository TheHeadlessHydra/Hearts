// std includes
#include <algorithm>
#include <iostream>
// local includes
#include "SmartPlayer.h"
#include "CardPile.h"
#include "Card.h"

using namespace std;

SmartPlayer::SmartPlayer(int iPlayerNumber, string sName)
{
	Player::m_iPlayerNumber = iPlayerNumber; 
	Player::m_sName = sName;
	Player::m_hand = new CardPile;
	Player::m_discardPile = new CardPile;
	m_totalScore = 0;
}

SmartPlayer::~SmartPlayer(){}
Card* SmartPlayer::lead()
{
	// Implementation:
	// Smart player should pick the lowest card out of his hand to lead

	assert (this->sizeOfHand() > 0); // The size of the hand cannot be zero!

	// Take the first card in his hand
	Card* currentSmallest = this->getFromHand(0);

	// Iterate through and find the smallest card
	for(int i = 0; i < this->sizeOfHand(); i++)
	{
		if( *(this->getFromHand(i)) < *(currentSmallest) )
			currentSmallest = this->getFromHand(i);
	}

	cout << "  " << this->getName() << " led " << *(currentSmallest) << endl;
	return currentSmallest;
} 

Card* SmartPlayer::throwOff()
{
	// Implementation:
	// If you have queen of spades, play it
	// If not, play the heart with the highest rank
	// If not, play the highest card. 

	assert (this->sizeOfHand() > 0); // The size of the hand cannot be zero!

	Card *queenOfSpades = NULL;
	Card *largestHeart = NULL;
	Card *largestNonHeart = NULL;

	for(int i = 0; i < this->sizeOfHand(); i++)
	{
		enum Card::Suit hearts = Card::Hearts;
		Card* currentCard = this->getFromHand(i);

		// If its the queen of hearts
		if( (*currentCard) == Card::QueenOfSpades )  
			queenOfSpades = currentCard;
		// If its a heart and we have no hearts tracked yet
		else if( currentCard->getSuit() == hearts && largestHeart == NULL )
			largestHeart = currentCard;
		// If its a hearts and its larger than our current hearts
		else if( currentCard->getSuit() == hearts && currentCard->getRank() > largestHeart->getRank() )
			largestHeart = currentCard;
		// If its not a heart/queenOfSpades and we have no tracked card yet
		else if ( currentCard->getSuit() != hearts && largestNonHeart == NULL)
			largestNonHeart = currentCard;
		// If its not a heart/queenOfSpades and its larger than our current non-heartcard
		else if ( currentCard->getSuit() != hearts && *largestNonHeart < *currentCard )
			largestNonHeart = currentCard;
	}

	if(queenOfSpades != NULL)
	{
		cout << "  " << this->getName() << " threw off " << (*queenOfSpades) << endl;
		return queenOfSpades;
	}
	if(largestHeart != NULL)
	{
		cout << "  " << this->getName() << " threw off " << (*largestHeart) << endl;
		return largestHeart;
	}
	if(largestNonHeart != NULL)
	{
		cout << "  " << this->getName() << " threw off " << (*largestNonHeart) << endl;
		return largestNonHeart;
	}

	assert(false); // throwOff could not find a card!
	return NULL;
}

Card* SmartPlayer::followSuit(trick *currentTrick)
{
	// Implementation:
	// Select the highest ranking card that is less than the current trump card.
	// If you can't do the above, play the lowest ranking card. 

	Card trumpCard = currentTrick->getTrumpCard();
	Card *highestCard = NULL;
	Card *lowestRankedCard = NULL;

	for(int i = 0; i < this->sizeOfHand(); i++)
	{
		Card *currentCard = this->getFromHand(i);
		// If the card is the same suit, lower rank than the trump, and the current highest is empty...
		if( currentCard->getSuit() == trumpCard.getSuit() && 
			currentCard->getRank() < trumpCard.getRank() &&
			highestCard == NULL)
			highestCard = currentCard;
		// If the card is the same suit, lower rank than the trump, and higher rank than the current...
		else if( currentCard->getSuit() == trumpCard.getSuit() && 
			     currentCard->getRank() < trumpCard.getRank() &&
				 currentCard->getRank() > highestCard->getRank() )
			highestCard = currentCard;
		// If the card is the same suit, and the lowestRankedCard is empty...
		else if (currentCard->getSuit() == trumpCard.getSuit() &&  lowestRankedCard == NULL)
			lowestRankedCard = currentCard;
		// If the card is the same suit, and the Rank is lower than the lowestRankedCard...
		else if(currentCard->getSuit() == trumpCard.getSuit() &&  
			    currentCard->getRank() < lowestRankedCard->getRank())
			lowestRankedCard = currentCard;
	}

	if(highestCard != NULL)
	{
		cout << "  " << this->getName() << " followed suit with " << *(highestCard) << endl;
		return highestCard;
	}
	if(lowestRankedCard != NULL)
	{
		cout << "  " << this->getName() << " followed suit with " << *(lowestRankedCard) << endl;
		return lowestRankedCard;
	}

	assert(false); // If it reached here, it could not find a card of the same suit - that should not happen in follow suit!
	return NULL;
}
