#ifndef BATTLE_H
#define BATTLE_H

#include "pokemon.h"
#include <iostream>
#include <string>

class Battle {
  public:
    Battle(Pokemon*, Pokemon*);
    void run();

  private:
    Pokemon *playerA, *playerB;
    bool playerAturn;
};

#endif