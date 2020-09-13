#include "gtest/gtest.h"

#include "player.h"
#include "healer.h"
#include "tank.h"
#include "fighter.h"
#include "inventory.h"

#include <iostream>
#include <sstream>

class RPGTest : public testing::Test {
protected:
	RPGTest() {
	}

	virtual ~RPGTest() {
	}

	virtual void SetUp() {
		tank = new Tank("Mark");
		healer = new Healer("Aaron");
		fighter = new Fighter("David");
	}

	virtual void TearDown() {
		delete tank;
		delete healer;
		delete fighter;
	}

	Player* tank;
	Player* healer;
	Player* fighter;
};

TEST_F(RPGTest, FighterTest) {
	tank->setHP(500);
	fighter->doAction(tank);
	EXPECT_EQ(425, tank->getHP());

	tank->setHP(75);
	fighter->doAction(tank);
	EXPECT_TRUE(tank->isDead());
}

TEST_F(RPGTest, HealerTest) {
	tank->setHP(400);
	healer->doAction(tank);
	EXPECT_EQ(475, tank->getHP());

	tank->setHP(450);
	healer->doAction(tank);
	EXPECT_EQ(500, tank->getHP());
}

TEST_F(RPGTest, InventoryTest) {

	// redirect cout statements to our stringstream
	std::stringstream buffer;
	std::streambuf *sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	Inventory* inv = tank->getInv();

	inv->addItem("HP Potion", 4);
	inv->addItem("Sword", 1);
	inv->addItem("Tunic", 1);
	inv->addItem("Boots", 2);
	inv->addItem("Flower", 5);
	inv->removeItem("Flower");
	inv->addItem("Tunic", 2);
	EXPECT_EQ(3, inv->getNumItems("Tunic"));

	inv->printAllItems();

	std::string compare = "HP Potion 4\nSword 1\nTunic 3\nBoots 2\n";

	EXPECT_EQ(compare, buffer.str());

	std::cout.rdbuf(sbuf);
}