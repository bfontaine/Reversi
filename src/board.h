#ifndef _BOARD_H
#define _BOARD_H 1


// -- utils --

#define EMPTY 0
#define EMPTY_C 'E'

#define WHITE 1
#define WHITE_C 'W'

#define BLACK 2
#define BLACK_C 'B'

// outside of the board
#define OUTSIDE -1

// a game board
typedef struct {

    // 0: empty square
    // 1: white piece
    // 2: black piece
    short game_board[8][8];

} board;

// convert a square name (e.g. "A7", "H2") to
// its column/row representation
int convert_square(char* square_name, int* col, int* row);


// -- piece-related functions --

// similar to `_get_piece`, but the first argument is
// a square name (e.g. "E5", "B2")
int get_piece(char* square_name, char* piece);

// reverse of `get_piece`, put `piece` into `square_name` square.
int put_piece(char* square_name, char* piece);


// -- board-related functions --

// initialize a game board
// black pieces are placed in E4 and D5 positions,
// white pieces are placed in D4 and E5 positions.
int init_board(board* b);

#endif // _BOARD_H
