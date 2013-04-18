#ifndef _SMARTPLAYER_H_
#define _SMARTPLAYER_H_

#include "Player.h"
#include "trick.h"
#include <string>

using namespace std;

class SmartPlayer : public Player
{
public:
	SmartPlayer(int iPlayerNumber, string sName);
	virtual ~SmartPlayer();

	Card* lead();
	Card* throwOff();
	Card* followSuit(trick *currentTrick);

};

#endif
