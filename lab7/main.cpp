#include <iostream>
#include "llist.h"

struct Pokemon {
  int id;
  std::string name;

  Pokemon()
    : id(0), name("") { }

  Pokemon(int i, std::string n)
    : id(i), name(n) { }
};

int main() {
  LList<Pokemon> pokedex;

  pokedex.push_back(Pokemon(1, "Bulbasaur"));
  pokedex.push_back(Pokemon(4, "Charmander"));
  pokedex.push_back(Pokemon(7, "Squirtle"));

  for (int i = 0; i < pokedex.size(); i++) {
    std::cout << pokedex.get(i).id << " " << pokedex.get(i).name << std::endl;
  }

  pokedex.clear();

  pokedex.push_back(Pokemon(144, "Articuno"));
  pokedex.push_back(Pokemon(145, "Zapdos"));
  pokedex.push_back(Pokemon(146, "Moltres"));

  for (int i = 0; i < pokedex.size(); i++) {
    std::cout << pokedex.get(i).id << " " << pokedex.get(i).name << std::endl;
  }
  
  return 0;
}
