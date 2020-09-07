#ifndef POKEMON_H_
#define POKEMON_H_

#include "attackMove.h"
#include <string>
#include <vector>

class Pokemon {
  public:
    Pokemon(std::string, int);
    void setMoves(AttackMove*, AttackMove*, AttackMove*, AttackMove*);
    int getHP();
    int attackPowerOf(int);
    int attackedBy(int);
    std::string getMove(int);
    std::string getName();

  private:
    std::string name;
    int offense;
    int defense;
    int maxhp;
    int hp;

    std::vector<AttackMove*> moves;
};

#endif  // POKEMON_H_