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
 * A position
 *  b : actual game board
 *
 *  moves : possible moves with this position
 *  moves_len : number of possible moves
 */
typedef struct position {

    board* b;

    struct future_move **moves;
    short moves_len;

} position;

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

/*
 * Create and return a new future_move given its column and row.
 * Set its points to 0 and its moves_len to 0.
 */
future_move* create_future_move(int col, int row);

/*
 * Create and return a new position given the current board. It create
 * also every future move.
 */
position* create_position(board* b);

/*
 * Add a future_move to an existing future_move
 */
int m_add_future_move(future_move* self, future_move* fm);

/*
 * Add a future_move to an existing position
 */
int p_add_future_move(position* self, future_move* fm);

/*
 * Free the memory allocated for the given future_move and all its
 * children.
 */
int free_future_move(future_move* fm);

/*
 * Free the memory allocated for the given position and all its future moves.
 */
int free_position(position* p);

#endif /* _AI_H */
