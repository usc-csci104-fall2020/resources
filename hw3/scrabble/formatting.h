#ifndef FORMATTING_H
#define FORMATTING_H

#include "rang.h"
#include <ostream>
#include <string>


std::string repeat(const char* str, size_t times);
void print_horizontal(size_t columns, const char* left, const char* joint, const char* right, std::ostream& out);

// Set colors used in the drawing.
// Hey, it's like prehistoric CSS!

#define FG_COLOR_LINE rang::fgB::green << rang::style::reset
#define FG_COLOR_LABEL rang::fg::reset
#define FG_COLOR_SCORE rang::fg::gray
#define FG_COLOR_LETTER rang::fg::reset << rang::style::bold
#define FG_COLOR_MULTIPLIER rang::fg::gray
#define FG_COLOR_HEADING rang::fgB::blue << rang::style::bold

#define BG_COLOR_NORMAL_SQUARE rang::bgB::black
#define BG_COLOR_START_SQUARE rang::bg::cyan
#define BG_COLOR_OUTSIDE_BOARD rang::bg::reset
#define BG_COLOR_WORD_MULTIPLIER_2X rang::bg::red
#define BG_COLOR_WORD_MULTIPLIER_3X rang::bgB::red
#define BG_COLOR_LETTER_MULTIPLIER_2X rang::bg::blue
#define BG_COLOR_LETTER_MULTIPLIER_3X rang::bgB::blue
#define BG_COLOR_PLAYER_HAND rang::bg::green

#define MOVE_PROMPT_COLOR rang::fgB::blue << rang::style::bold
#define PLAYER_NAME_COLOR rang::fgB::red << rang::style::bold
#define TILE_NAME_COLOR rang::fg::green << rang::style::bold
#define SCORE_COLOR rang::fgB::magenta << rang::style::bold

// Unicode line-drawing character constants
// from https://en.wikipedia.org/wiki/Box-drawing_character

#define I_HORIZONTAL "\u2500"
#define I_VERTICAL "\u2502"
#define L_TOP_LEFT "\u250c"
#define L_TOP_RIGHT "\u2510"
#define L_BOTTOM_LEFT "\u2514"
#define L_BOTTOM_RIGHT "\u2518"
#define T_DOWN "\u252c"
#define T_UP "\u2534"
#define T_RIGHT "\u251c"
#define T_LEFT "\u2524"
#define PLUS "\u253c"
#define SPACE " "

#define SQUARE_INNER_WIDTH 5
#define SQUARE_INNER_HEIGHT 3
#define SQUARE_OUTER_WIDTH (SQUARE_INNER_WIDTH + 2)
#define SQUARE_OUTER_HEIGHT (SQUARE_INNER_WIDTH + 2)
#define BOARD_LEFT_MARGIN 3
#define BOARD_TOP_MARGIN 3
#define HAND_TOP_MARGIN 3
#define HAND_LEFT_MARGIN 24

#endif
