#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "Player.h"
#include "trick.h"
#include <string>

using namespace std;

class HumanPlayer : public Player
{
public:
	HumanPlayer(int iPlayerNumber, string sName);
	virtual ~HumanPlayer();
	
	Card* lead();
	Card* throwOff();
	Card* followSuit(trick *currentTrick);
};

#endif
