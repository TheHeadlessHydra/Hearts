#ifndef _RANDOMPLAYER_H_
#define _RANDOMPLAYER_H_

#include "Player.h"
#include "trick.h"
#include "PRNG.h"
#include <string>

using namespace std;

class RandomPlayer : public Player
{
private:
	PRNG m_randomGenerator;
public:
	RandomPlayer(int iPlayerNumber, string sName, int iSeed);
	virtual ~RandomPlayer();

	Card* lead();
	Card* throwOff();
	Card* followSuit(trick *currentTrick);
};

#endif
