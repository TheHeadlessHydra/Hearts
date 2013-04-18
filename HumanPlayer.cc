// std includes
#include <iostream>
#include <string>
// local includes
#include "HumanPlayer.h"
#include "Card.h"

using namespace std;

HumanPlayer::HumanPlayer(int iPlayerNumber, string sName)
{
	Player::m_iPlayerNumber = iPlayerNumber;
	Player::m_sName = sName;
	Player::m_hand = new CardPile;
	Player::m_discardPile = new CardPile;
	m_totalScore = 0;
}

HumanPlayer::~HumanPlayer(){}

Card* HumanPlayer::lead()
{
	cout << "Human player " << this->getName() << " has these cards:" << endl << "    ";
	this->printHand();
	cout << endl;

	while(true)
	{
		cout << "What card would you like to play, " << this->getName() << "? ";

		// Take in the string
		string playThis;
		cin >> playThis;

		// If the string is not a valid string, send an error
		// and ask again
		if ( !Card::stringIsALegalCard(playThis) )
		{
			cout << playThis << " is not a card" << endl;
			continue;
		}

		// If it is a valid string, create the card based
		// on the string, and search the hand for the card
		Card *cardToPlay = NULL;
		char newRank = playThis[0];
		char newSuit = playThis[1];
		Card newCard( 
			static_cast<Card::Rank>(Card::RankName.find(newRank)), 
			static_cast<Card::Suit>(Card::SuitName.find(newSuit)) );
		for(int i = 0; i < this->sizeOfHand(); i++)
		{
			if( *(this->getFromHand(i)) ==  newCard )
				cardToPlay = (this->getFromHand(i));
		}

		// If the card is not in the hand, send an error 
		// and ask again.
		if (cardToPlay == NULL)
		{
			cout << playThis << " is not in your hand" << endl;
			continue;
		}

		// If it is in the hand, print to screen and return the card
		cout << "  " << this->getName() << " led " << playThis << endl;
		return cardToPlay;
	}
}

Card* HumanPlayer::throwOff()
{
	cout << "Human player " << this->getName() << " has these cards:" << endl << "    ";
	this->printHand();
	cout << endl;

	while(true)
	{
		cout << "What card would you like to play, " << this->getName() << "? ";

		// Take in the string
		string playThis;
		cin >> playThis;

		// If the string is not a valid string, send an error
		// and ask again
		if ( !Card::stringIsALegalCard(playThis) )
		{
			cout << playThis << " is not a card" << endl;
			continue;
		}

		// If it is a valid string, create the card based
		// on the string, and search the hand for the card
		Card *cardToPlay = NULL;
		char newRank = playThis[0];
		char newSuit = playThis[1];
		Card newCard( 
			static_cast<Card::Rank>(Card::RankName.find(newRank)), 
			static_cast<Card::Suit>(Card::SuitName.find(newSuit)) );
		for(int i = 0; i < this->sizeOfHand(); i++)
		{
			if( *(this->getFromHand(i)) ==  newCard)
				cardToPlay = (this->getFromHand(i));
		}

		// If the card is not in the hand, send an error 
		// and ask again.
		if (cardToPlay == NULL)
		{
			cout << playThis << " is not in your hand" << endl;
			continue;
		}

		// If it is in the hand, print to screen and return the card
		cout << "  " << this->getName() << " threw off " << playThis << endl;
		return cardToPlay;
	}
}

Card* HumanPlayer::followSuit(trick *currentTrick)
{
	Card trumpCard = currentTrick->getTrumpCard();
	cout << "Human player " << this->getName() << " has these cards:" << endl << "    ";
	this->printHand();
	cout << endl;

	while(true)
	{
		cout << "What card would you like to play, " << this->getName() << "? ";

		// Take in the string
		string playThis;
		cin >> playThis;

		// If the string is not a valid string, send an error
		// and ask again
		if ( !Card::stringIsALegalCard(playThis) )
		{
			cout << playThis << " is not a card" << endl;
			continue;
		}

		// If it is a valid string, create the card based
		// on the string, and search the hand for the card
		Card *cardToPlay = NULL;
		char newRank = playThis[0];
		char newSuit = playThis[1];
		Card newCard( 
			static_cast<Card::Rank>(Card::RankName.find(newRank)), 
			static_cast<Card::Suit>(Card::SuitName.find(newSuit)) );
		for(int i = 0; i < this->sizeOfHand(); i++)
		{
			if( *(this->getFromHand(i)) ==  newCard)
				cardToPlay = (this->getFromHand(i));
		}

		// If the card is not in the hand, send an error 
		// and ask again.
		if (cardToPlay == NULL)
		{
			cout << playThis << " is not in your hand" << endl;
			continue;
		}

		// If it is in the hand, check to see if it is the same suit as the trump
		if(cardToPlay->getSuit() != trumpCard.getSuit())
		{
			cout << "You have at least one " << Card::SuitName.at(static_cast<int>(trumpCard.getSuit())) << "; you must follow suit!" << endl;
			continue;
		}

		// If it is in the hand, and of the same suit as the trump, print to screen and return the card
		cout << "  " << this->getName() << " followed suit with " << playThis << endl;
		return cardToPlay;
	}
}
