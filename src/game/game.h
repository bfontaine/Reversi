#include "../utils.h"
#include "board.c"

#ifndef _GAME_H
#define _GAME_H 1

// test if `player` can play here.
int can_play(board *b, int col, int row, char player);

// returns all possible moves for the given player. Moves are put in `moves`,
// and the array length is given by the returned int value.
int get_possible_moves(board *b, char player, char*** moves);

// return the current score for the given player
int get_score(board *b, char player);

// the player `player` put a token on `square_name` square.
//
// Ex:        .<- W plays here          W
//   before: WB                 after: WW
//           BW                        BW
//
// returns the score made with this move (new score - old score).
int play(board *b, char player, char* square_name);

#endif // _GAME_H
