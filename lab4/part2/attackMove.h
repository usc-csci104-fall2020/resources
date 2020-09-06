#ifndef ATTACKMOVE_H
#define ATTACKMOVE_H

#include <string>

class AttackMove {
  public:
    AttackMove(std::string, int);
    std::string getName();
    int getPotency();

  private:
    std::string name;
    int potency;
};

#endif