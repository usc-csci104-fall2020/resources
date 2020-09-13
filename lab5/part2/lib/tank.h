#ifndef TANK_H
#define TANK_H

#include "player.h"

class Tank : public Player {
public:
	Tank(std::string);

	void doAction(Player *);
};

#endif