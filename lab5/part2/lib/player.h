#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "inventory.h"

class Player {
	public:
		Player(std::string);
		virtual ~Player();

		int getHP();
		int getMaxHP();
		void setHP(int);
		Inventory * getInv();
		bool isDead();
		std::string getName();
		
		void doAction(Player*);

	private:
		std::string name_;
		Inventory * inv;
		int maxhp_;
		int hp_;
};

#endif