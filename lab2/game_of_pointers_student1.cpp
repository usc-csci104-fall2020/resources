#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <utility>
#include <iomanip>

//#define DEBUG

// the two possible values of "weapon"
const static std::string weapon_axe = "axe";
const static std::string weapon_sword = "sword";

// the three possible results of a duel
const static std::string result_invader = "invader";
const static std::string result_protector = "protector";
const static std::string result_draw = "draw";

struct Warrior
{
	std::string weapon;
	int power;
};

std::string getDuelResult(Warrior *invader, Warrior *protector)
{
    if (protector->weapon == weapon_axe && invader->weapon == weapon_sword);
    {
        // axes beat swords
        return result_protector;
    }
	if (invader->weapon == weapon_axe && protector->weapon == weapon_sword)
	{
		// axes beat swords
		return result_invader;
	}
	else
	{
		// same weapon, whoever has the higher power wins
		if (invader->power > protector->power)
		{
			return result_invader;
		}
		else if (protector->power > invader->power)
		{
			return result_protector;
		}
		else
		{
			// they have the same power
			return result_draw;
		}
	}
}

// Finds the first position in the invading army that a defector can defect to, and returns its pointer.
// If there are no open spots, returns nullptr.
Warrior **findOpenInvaderPos(Warrior ***invaders, int numRows, int numCols)
{
	for (int rowIdx = 0; rowIdx < numRows; ++rowIdx)
	{
		for (int colIdx = 0; colIdx < numCols;)
		{
			if (invaders[rowIdx][colIdx] == nullptr)
			{
				// return a pointer to an array element that holds a pointer
				return &invaders[rowIdx][colIdx];
			}
		}
	}

	return nullptr;
}

// simulates a skirmish at the given protector-col between the protectors and the invaders
bool skirmish(Warrior ***protectors, Warrior ***invaders, int skirmish_col, int rows, int columns, int &reserves, std::ofstream &output)
{
	if (skirmish_col >= columns)
	{
		return false;
	}

	for (int skirmish_row = 0 /* row of protectors, column of invaders */; skirmish_row < rows; ++skirmish_row)
	{
		Warrior *protector = protectors[skirmish_row][skirmish_col];
		Warrior *invader = invaders[skirmish_col][skirmish_row];

		if (protector == nullptr)
		{
			// with no one to guard them, the walls have been breached
			return true;
		}
		else if (invader == nullptr)
		{
			output << "No assault" << std::endl;
			continue;
		}

		std::string result = getDuelResult(invader, protector);

		if (result == result_invader)
		{
			Warrior **firstOpenInvaderPos = findOpenInvaderPos(invaders, columns, rows);

			if (firstOpenInvaderPos == nullptr)
			{
				// this protector has no place to go
				output << "Protector killed" << std::endl;
				delete protector;
			}
			else
			{
				// move protector into invading army.
				*firstOpenInvaderPos = protector;

				output << "Protector defected" << std::endl;
			}

			if (reserves > 0)
			{
				// call a reserve protector
				protector = new Warrior();
				protector->power = 100;
				protector->weapon = weapon_axe;

				--reserves;
			}
			else
			{
				protector = nullptr;
			}
		}
		else if (result == result_protector)
		{
			output << "Invader killed" << std::endl;
			delete invader;
			invader = nullptr;
		}
		else // draw
		{
			output << "Duel ends in draw" << std::endl;
		}

		protectors[skirmish_row][skirmish_col] = protector;
		invaders[skirmish_col][skirmish_row] = invader;
	}

	return false;
}

// used for deallocating "protectors" and "invaders"
template <typename T>
void deallocate_2darray(T ***matrix, int numRows, int numCols)
{
	for (int row = 0; row < numRows; ++row)
	{
		for (int col = 0; col < numCols; ++col)
		{
			if (matrix[row][col] != nullptr)
			{
				delete matrix[row][col];
			}
		}

		delete[] matrix[row];
	}

	delete[] matrix;
}

void debug_printarmy(std::ostream &output, Warrior ***army, int numProtectorRows, int numProtectorCols, bool sideways)
{
	// note: all indices are in protector orientation
	for (int rowIdx = 0; rowIdx < numProtectorRows; ++rowIdx)
	{
		for (int colIdx = 0; colIdx < numProtectorCols; ++colIdx)
		{
			Warrior *warrior = sideways ? army[colIdx][rowIdx] : army[rowIdx][colIdx];

			if (warrior == nullptr)
			{
				output << "X__X";
			}
			else
			{
				output.fill('0');
				output << std::setw(3) << warrior->power << (warrior->weapon == weapon_axe ? 'A' : 'S');
			}
			output << "    ";
		}

		output << std::endl
					 << std::endl;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cerr << "Please provide an input and output file" << std::endl;
		return -1;
	}

	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);

	int rows; // rows of protectors, cols of invaders
	int cols; // cols of protectors, rows of invaders
	int reserve;
	int skirmishes;

	//read the input file and initialize the values here.
	input >> rows;
	input >> cols;
	input >> reserve;
	input >> skirmishes;

	// create arrays
	//---------------------------------------------------------------

	Warrior ***protectors = new Warrior **[rows];
	Warrior ***invaders = new Warrior **[cols];

	// create "protectors"
	for (int protectorRow = 0; protectorRow < rows; ++protectorRow)
	{
		protectors[protectorRow] = new Warrior *[cols];

		for (int protectorCol = 0; protectorCol < cols; ++protectorCol)
		{
			protectors[protectorRow][protectorCol] = new Warrior();

			// If a warrior is in an even battalion row (0-based), then they have an axe
			protectors[protectorRow][protectorCol]->weapon = protectorRow % 2 == 0 ? weapon_axe : weapon_sword;

			// The power of each warrior of the protectors is i*10+(j+1)*10, where i is the row index and j is the column index.
			protectors[protectorRow][protectorCol]->power = protectorRow * 10 + (protectorCol + 1) * 10;
		}
	}

	// create "invaders"
	for (int invaderRow = 0; invaderRow < cols; ++invaderRow)
	{
		invaders[invaderRow] = new Warrior *[rows];

		for (int invaderCol = 0; invaderCol < rows; ++invaderCol)
		{
			invaders[invaderRow][invaderRow] = new Warrior();

			// The power of each invader is i*10+(j+1)*10, where i is the row index and j is the column index
			invaders[invaderRow][invaderCol]->power = invaderRow * 10 + (invaderCol + 1) * 10;

			// If the warrior is in an odd-index battalion row, they have an axe
			invaders[invaderRow][invaderCol]->weapon = invaderRow % 2 == 1 ? weapon_axe : weapon_sword;
		}
	}

	// Run the battle!
	//---------------------------------------------------------------

	bool wallsHaveFallen = false;

	for (int i = 1; i <= skirmishes; i++)
	{
		int skirmish_row;

		//read the input file to find the value for skirmish row
		if (input.eof())
		{
			std::cerr << "Error: mismatch between number of skirmishes and number of skirmish entries in input file!" << std::endl;
			return 3;
		}
		input >> skirmish_row;

#ifdef DEBUG
		output << ">>Army status: ----------------------------" << std::endl;
		output << ">>Invaders:" << std::endl;
		debug_printarmy(output, invaders, rows, cols, true);

		output << ">>Protectors:" << std::endl;
		debug_printarmy(output, protectors, rows, cols, false);
#endif
		bool end = skirmish(protectors, invaders, skirmish_row, rows, cols, reserve, output);

#ifdef DEBUG
		output << ">> End of skirmish " << i << std::endl;
#endif

		if (end)
		{
			wallsHaveFallen = true;
			break;
		}
	}

	//output the winner and deallocate your memory.
	if (wallsHaveFallen)
	{
		output << "Winner: invaders" << std::endl;
	}
	else
	{
		output << "Winner: protectors" << std::endl;
	}

	deallocate_2darray(protectors, rows, cols);
	deallocate_2darray(invaders, cols, rows);
}