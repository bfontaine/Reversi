#ifndef _BOARD_H
#define _BOARD_H 1

#include <stdio.h>
#include <string.h>
#include "../utils.h"

// -- utils --

// a game board
typedef struct {

    // 0: empty square
    // 1: white piece
    // 2: black piece
    short game_board[MAX_SQ+1][MAX_SQ+1];

} board;

// convert a square name (e.g. "A7", "H2") to
// its column/row representation
int convert_square(char* square_name, int* col, int* row);


// -- piece-related functions --

// get the piece in `square_name` square, and put it in `piece`.
int get_piece(board* b, char* square_name, char* piece);
int get_piece_by_colrow(board *b, int col, int row, char* piece);

// reverse of `get_piece`, put `piece` into `square_name` square.
int put_piece(board* b, char* square_name, char piece);
int put_piece_by_colrow(board *b, int col, int row, char piece);

// test if the square is empty
int is_empty(board* b, char* square_name);
int is_empty_by_colrow(board* b, int col, int row);

// test if the square contains a token of the given player
int is_player(board* b, char* square_name, char player);
int is_player_by_colrow(board* b, int col, int row, char player);

// test if the square contains a token of the other player
int is_other_player(board* b, char* square_name, char player);
int is_other_player_by_colrow(board* b, int col, int row, char player);

// test if the square is alone, i.e. all its neighbour are empty
int is_alone(board* b, char* square_name);
int is_alone_by_colrow(board* b, int col, int row);

// test if the square is outside of the board
int is_outside_by_colrow(int col, int row);

// -- board-related functions --

// initialize a game board
// black pieces are placed in E4 and D5 positions,
// white pieces are placed in D4 and E5 positions.
int init_board(board* b);

#endif // _BOARD_H
