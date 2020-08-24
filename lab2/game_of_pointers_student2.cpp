#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

// note: enums would be better, but the field was provided in the assignment as a string
const std::string AXE = "axe";
const std::string SWORD = "sword";

struct Warrior
{
  std::string weapon;
  int power;
  Warrior(const std::string &_weapon, int _power) : weapon(_weapon), power(_power) {}
};

// returns true if successful and false otherwise
bool ReadInitialInput(std::ifstream &inputFile, int &n, int &m, int &numReserves, int &numSkirmishes)
{
  inputFile >> n >> m >> numReserves >> numSkirmishes;
  return !inputFile.fail();
}

Warrior ***AllocateWarriors(int num_rows, int num_columns, bool axes_on_even)
{
  Warrior ***warriors = new Warrior **[num_rows];
  for (int i = 0; i < num_rows; ++i)
  {
    warriors[i] = new Warrior *[num_columns];
  }

  for (int i = 0; i < num_rows; ++i)
  {
    for (int j = 0; j < num_columns; ++j)
    {
      int power = i * 10 + (j + 1) * 10;
      if ((axes_on_even && i % 2 == 0) || (!axes_on_even && i % 2 == 1))
      {
        warriors[i][j] = new Warrior(AXE, power);
      }
      else
      {
        warriors[i][j] = new Warrior(SWORD, power);
      }
    }
  }

  return warriors;
}

void DeallocateWarriors(Warrior ***warriors, int num_rows, int num_columns)
{
  for (int i = 0; i < num_rows; ++i)
  {
    for (int j = 0; j < num_columns; ++j)
    {
      if (warriors[i][j])
        delete warriors[i][j];
    }
  }

  for (int i = 0; i < num_rows; ++i)
  {
    delete[] warriors[i];
  }

  delete[] warriors;
}

bool DefectProtector(Warrior *protector, Warrior ***invaders, int n, int m)
{
  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      if (!invaders[i][j])
      {
        invaders[i][j] = protector;
        return true;
      }
    }
  }

  return false;
}

bool Skirmish(Warrior ***protectors, Warrior ***invaders, int n, int m, int skirmishLine, int &numReserves, std::ofstream &outputFile)
{
  if (skirmishLine < 0 || skirmishLine >= m)
  {
    return false;
  }

  for (int k = 0; k < n; ++k)
  {
    Warrior *invader = invaders[skirmishLine][k];
    Warrior *protector = protectors[k][skirmishLine];

    if (!invader)
    {
      outputFile << "No assault" << std::endl;
      continue;
    }

    if (!protector)
    {
      return true;
    }

    bool protectorLost = false;
    if (invader->weapon == protector->weapon)
    {
      if (invader->power < protector->power)
      {
        protectorLost = true;
      }
      else if (protector->power < invader->power)
      {
        delete invader;
        invaders[skirmishLine][k] = nullptr;
        outputFile << "Invader killed" << std::endl;
      }
      else
      {
        outputFile << "Duel ends in draw" << std::endl;
      }
    }
    else
    { // different weapons -- the warrior with the axe wins
      if (invader->weapon == AXE)
      {
        protectorLost = true;
      }
      else
      {
        delete invader;
        invaders[skirmishLine][k] = nullptr;
        outputFile << "Invader killed" << std::endl;
      }
    }

    if (protectorLost)
    {
      // protector leaves the protector side
      protectors[k][skirmishLine] = nullptr;

      // see if the protector can defect
      if (DefectProtector(protector, invaders, n, m))
      {
        outputFile << "Protector defected" << std::endl;
      }
      else
      {
        outputFile << "Protector killed" << std::endl;
        delete protector;
      }

      // add reserve if there is one
      if (numReserves-- > 0)
      {
        protectors[k][skirmishLine] = new Warrior(AXE, 100);
      }
    }
  }

  return false;
}

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    std::cout << "usage: ./game_of_pointers input_file output_file" << std::endl;
    return 1;
  }

  int n;             // number of rows of protectors and columns of invaders
  int m;             // number of columns of protectors and rows of invaders
  int numReserves;   // number of reserve forces for protectors
  int numSkirmishes; // number of skirmishes

  std::ifstream inputFile(argv[1]);
  std::ofstream outputFile(argv[2]);

  if (inputFile.fail())
  {
    std::cout << "the provided input file does not exist" << std::endl;
    return 1;
  }

  ReadInitialInput(inputFile, n, m, numReserves, numSkirmishes);

  Warrior ***protectors = AllocateWarriors(n, m, true);
  Warrior ***invaders = AllocateWarriors(m, n, false);

  bool invadersWon = false;
  for (int i = 0; i < numSkirmishes; ++i)
  {
    int skirmishLine;
    inputFile >> skirmishLine;
    if (Skirmish(protectors, invaders, n, m, skirmishLine, numReserves, outputFile))
    {
      invadersWon = true;
      break;
    }
  }

  if (invadersWon)
  {
    outputFile << "Winner: invaders" << std::endl;
  }
  else
  {
    outputFile << "Winner: protectors" << std::endl;
  }

  DeallocateWarriors(protectors, n, m);
  DeallocateWarriors(invaders, n, m);
}