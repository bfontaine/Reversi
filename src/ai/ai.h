#ifndef _AI_H
#define _AI_H 1

#include <stdio.h>
#include <stdlib.h>

#include "../utils.h"
#include "../game/board.h"
#include "../game/game.h"

#define CORNER_WEIGHT 10
#define SIDE_WEIGHT 3
#define DEFAULT_WEIGHT 1

#define MAX_DEEP 8

#define VERBOSE_AI 1


/* TODO lower this number using tests */
#define MAX_POSSIBLE_MOVES 40

/*
 * A future move
 *  col : column
 *  row : row
 *
 *  points : points earned by making this move
 *
 *  If there is no possible move, "points"'s value should be equal to 0.
 *  If there is no possible move after the current move, moves_len should be 1
 *  and the only one move's points should be equal to 0.
 *  
 *  moves : future moves made possible with this move
 *  moves_len : number of possible future moves
 */
typedef struct future_move {

    unsigned short col;
    unsigned short row;

    short points;

    struct future_move **moves;
    short moves_len;

} future_move;

/*
 * An AI
 *  b : actual game board
 *
 *  moves : possible moves with this position
 *  moves_len : number of possible moves
 *
 *  player_c : char of the player (BLACK_C or WHITE_C)
 */
typedef struct ai {

    board* b;

    struct future_move **moves;
    short moves_len;

    short player_c;

} ai;

/* compute a position's weight using its column and row */
#define P_WEIGHT(C,R) ((C==MIN_SQ || C==MAX_SQ) \
                           ? (R==MIN_SQ || R==MAX_SQ) \
                                ? CORNER_WEIGHT \
                                : SIDE_WEIGHT \
                           : (R==MIN_SQ || R==MAX_SQ) \
                                ? SIDE_WEIGHT \
                                : DEFAULT_WEIGHT)

/* compute a move's weight */
#define M_WEIGHT(M) (P_WEIGHT((M).col,(M).row)*(M).points)

/* add a future_move* to a future_move* or a position* */
#define ADD_FUTURE_MOVE(SELF,F) ((SELF)->moves)[((SELF)->moves_len)++]=(F)

/*
 * Create and return a new future_move given its column and row.
 * Set its points to 0 and its moves_len to 0.
 */
future_move* create_future_move(int col, int row);

/*
 * Create and return a new AI given the current board. It create
 * also all its future move. Note that the board is copied.
 */
ai* create_ai(board* b, char player_c);

/*
 * Make the AI plays in col/row. All the tree of future moves will be
 * adapted to the new position.
 */
int ai_play(ai* self, int col, int row);

/*
 * Free the memory allocated for the given future_move and all its
 * children.
 */
int free_future_move(future_move* fm);

/*
 * Free the memory allocated for the given AI and all its future moves.
 */
int free_ai(ai* a);

/* == AI methods =========================================================== */

/*
 * Read a command from the AI.
 *  self: current AI
 *  cmd: 3-chars string which will be filled by the AI
 */
int read_ai_command(ai* self, char** cmd);

#endif /* _AI_H */
