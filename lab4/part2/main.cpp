#include "attackMove.h"
#include "battle.h"
#include "pokemon.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>

Battle* b;
Pokemon *pA, *pB;
AttackMove *am1, *am2, *am3, *am4, *am5, *am6, *am7, *am8;

void setUp() {
    std::srand(time(0));

    am1 = new AttackMove("Quick Attack", 55);
    am2 = new AttackMove("Slam", 90);
    am3 = new AttackMove("Thunder Shock", 60);
    am4 = new AttackMove("Thunder", 110);

    am5 = new AttackMove("Tackle", 40);
    am6 = new AttackMove("Quick Attack", 40);
    am7 = new AttackMove("Psychic", 90);
    am8 = new AttackMove("Last Resort", 140);

    pA = new Pokemon("Pikachu", 274);
    pA->setMoves(am1, am2, am3, am4);
    pB = new Pokemon("Espeon", 334);
    pB->setMoves(am5, am6, am7, am8);
    b = new Battle(pA, pB);
}

void tearDown() {
    delete am1;
    delete am2;
    delete am3;
    delete am4;
    delete am5;
    delete am6;
    delete am7;
    delete am8;
    delete pA;
    delete pB;
    delete b;
}

int main() {
    setUp();
    b->run();
    tearDown();

    return 0;
}