#include "../utils.h"

#ifndef _GAME_H
#define _GAME_H 1

// returns all possible moves for the given player. Moves are put in `moves`,
// and the array length is given by the returned int value.
int get_possible_moves(board *b, char player, char** moves);

#endif // _GAME_H
