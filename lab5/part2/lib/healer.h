#ifndef HEALER_H
#define HEALER_H

#include "player.h"

class Healer : public Player {
public:
	Healer(std::string);

	void doAction(Player *);
};

#endif