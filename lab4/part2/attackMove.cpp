#include "attackMove.h"

AttackMove::AttackMove(std::string n, int p) : name(n), potency(p) {
}

std::string AttackMove::getName() {
    return name;
}

int AttackMove::getPotency() {
    return potency;
}