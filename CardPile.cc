// std includes
#include <vector>
#include <iostream>
#include <algorithm>
// local includes
#include "CardPile.h"
#include "Card.h"

const uint32_t CardPile::DefaultRandomSeed = 37;

// Constructor / destructor
CardPile::CardPile() : prng(DefaultRandomSeed) {}

CardPile::~CardPile() 
{
	for(int i = 0; i < this->getSize(); i++)
		delete this->getCard(i);
}

// Extra Functions
void CardPile::setRandomSeed(uint32_t randomSeed) 
{
	prng.seed(randomSeed);
}

void CardPile::print()
{
	for ( int i = 0; i < getSize(); i++ )
		cout << *(getCard(i)) << " ";
}

int CardPile::heartsValue()
{
	int iTotalSum = 0;
	for ( int i = 0; i < getSize(); i++ )
		int iTotalSum = iTotalSum + this->at(i)->getHeartsValue();
	return iTotalSum;
}

void CardPile::shuffle() 
{
	for (int i = size() - 1; i > 0; i--) {
		const int j = prng(i);
		Card* tmp = at(j);
		at(j) = at(i);
		at(i) = tmp;
	}
}

// Accessor functions 
int CardPile::getSize( void ) const { return this->size(); } 
vector<Card*>::const_iterator CardPile::getBegin( void ) const { return this->begin(); } 
vector<Card*>::const_iterator CardPile::getEnd( void ) const { return this->end(); } 
void CardPile::addCard(Card *card){	this->push_back(card);	}

bool CardPile::removeCard(int iPos)
{
	assert( iPos >= 0 || iPos < this->getSize() );
	if( iPos < 0 || iPos >= this->getSize() )
		return false;
	this->erase(this->begin() + iPos);
	return true;
}

bool CardPile::removeCard(Card *card)
{
	for(int i = 0; i < this->getSize(); i++)
	{
		if(card ==  this->at(i))
		{
			this->erase(this->begin() + i);
			return true;
		}
	}	
	// Made it past the for loop; was not in the deck
	return false;
}

Card* CardPile::getCard(int iPos) const
{
	assert( iPos >= 0 || iPos < this->getSize() );
	return this->at(iPos);
}

void CardPile::clearPile(){ this->clear(); }
