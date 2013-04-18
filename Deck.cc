#include "Deck.h"
#include <iostream>
#include <cstdlib>

// Constructor
Deck::Deck() : CardPile(), m_iDeckSize(52) {}
Deck::~Deck(){}

//************************************************
// NEED TO CHANGE ORDERING - HAS TO BE SUIT FIRST:
// 2S 3S 4S, ... QH KH
void Deck::generate()
{
	// Loop through all 52 possible combinations of a card.
	// Create each one, and add it to the Deck.
	for(int iSuit = Card::Spades; iSuit <= Card::Hearts; iSuit++)
	{
		for(int iRank = Card::Two; iRank <= Card::Ace; iRank++)
		{
			enum Card::Suit suit = static_cast<Card::Suit>(iSuit);
			enum Card::Rank rank = static_cast<Card::Rank>(iRank);
			Card *newCard = new Card(rank, suit);
			this->addCard( newCard );
		}
	}
}
//******************************************************
bool Deck::playingWithAFullDeck () const
// Ceck if every card is in the deck. First, check if the deck is 
// of size 52. If so, then loop through all 52 possible cards in a
// deck, and check if each one is in the current deck. If a single
// card is not in the deck, return false. Duplicated cards are
// taken care of vacuously.
{
	if(this->getSize() != 52)
		return false;

	for(int iRank = Card::Two; iRank <= Card::Ace; iRank++)
	{
		for(int iSuit = Card::Spades; iSuit <= Card::Hearts; iSuit++)
		{
			enum Card::Suit suit = static_cast<Card::Suit>(iSuit);
			enum Card::Rank rank = static_cast<Card::Rank>(iRank);
			const Card isThisIn(rank, suit);

			// Checks every spot in the vector to see if the card
			// is in the vector. If it is not, it will return false. 
			bool bIsItIn = false;
			for (int i = 0; i < this->getSize(); i++)
			{
				if(*(this->getCard(i)) == isThisIn)
				{
					bIsItIn = true;
					break;
				}
			}
			if (!bIsItIn)
				return false;
		}
	}
	return true;
}

istream& operator>> (istream& in, Deck& deck)
{
	for(int i = 0; i < deck.m_iDeckSize; i++)
	{
		Card *inputCard = new Card;
		in >> *inputCard;
		deck.addCard(inputCard);
	}

	if(!deck.playingWithAFullDeck())
	{
		cerr << "Error, incomplete deck.  Aborting." << endl << "    ";
		deck.print();
		cout << endl;
		exit(1);
	}

	return in;
}