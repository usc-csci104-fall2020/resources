#include "pokemon.h"

#include <cstdlib>

Pokemon::Pokemon(std::string n, int h) {
    name = n;
    maxhp = h;
    hp = h;

    offense = std::rand() % 4 + 6;
    defense = std::rand() % 5 + 1;
}

void Pokemon::setMoves(AttackMove* a, AttackMove* b, AttackMove* c, AttackMove* d) {
    moves.clear();
    moves.push_back(a);
    moves.push_back(b);
    moves.push_back(c);
    moves.push_back(d);
}

int Pokemon::attackPowerOf(int i) {
    return moves[i]->getPotency() * offense / 10;
}

int Pokemon::attackedBy(int power) {
    int damaged = power * (10 - defense) / 10;
    hp -= damaged;
    return damaged;
}

int Pokemon::getHP() {
    return (hp > 0) ? hp : 0;
}

std::string Pokemon::getName() {
    return name;
}

std::string Pokemon::getMove(int i) {
    return moves[i]->getName();
}