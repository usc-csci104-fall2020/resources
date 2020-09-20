#include "formatting.h"
#include <cstring>

using namespace std;


string repeat(const char* str, size_t times) {
    string sum;
	for (size_t count = 0; count < times; ++count) {
		sum += str;
	}
	return sum;
}

void print_horizontal(size_t columns, const char* left, const char* joint, const char* right, ostream& out) {
    if (columns == 0) {
        return;
    }
	out << FG_COLOR_LINE << BG_COLOR_NORMAL_SQUARE << left;
	for (size_t i = 0; i < columns - 1; ++i) {
		out << repeat(I_HORIZONTAL, SQUARE_INNER_WIDTH) << joint;
	}
	out << repeat(I_HORIZONTAL, SQUARE_INNER_WIDTH) << right << BG_COLOR_OUTSIDE_BOARD;
}
