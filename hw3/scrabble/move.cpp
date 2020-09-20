#include "move.h"


Direction operator!(Direction direction) {
    return direction == Direction::ACROSS ? Direction::DOWN : Direction::ACROSS;
}
