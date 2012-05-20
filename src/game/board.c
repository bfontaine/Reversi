#ifndef _BOARD_C
#define _BOARD_C 1

#include "board.h"

int convert_square(char* square_name, int* col, int* row) {

    if (strlen(square_name) < 2) {
        return NOT_A_SQUARE;
    }
    
    if (   (square_name[0] < (MIN_SQ+FIRST_LETTER))
        || (square_name[0] > (MAX_SQ+FIRST_LETTER))
        || (square_name[1] < (MIN_SQ+FIRST_DIGIT) )
        || (square_name[1] > (MAX_SQ+FIRST_DIGIT) )) {

        return OUTSIDE;
    }

    *col = square_name[0] - FIRST_LETTER;
    *row = square_name[1] - FIRST_DIGIT;

    return 0;
}

/*  By row/column */

int get_piece_by_colrow(board *b, int col, int row, char* piece) {

    if (is_outside_by_colrow(col, row))
        return OUTSIDE;

    *piece = b->game_board[col][row];
    return 0;
}

int put_piece_by_colrow(board *b, int col, int row, char piece) {

    if (is_outside_by_colrow(col, row))
        return OUTSIDE;

    b->game_board[col][row] = piece;
    
    return 0;
}

int is_outside_by_colrow(int col, int row) {
    return (   (row < MIN_SQ) || (row > MAX_SQ)
            || (col < MIN_SQ) || (col > MAX_SQ));
}

int is_empty_by_colrow(board* b, int col, int row) {
    if (is_outside_by_colrow(col, row))
        return OUTSIDE;

    return (b->game_board[col][row] == EMPTY_C);
}

int is_player_by_colrow(board* b, int col, int row, char player) {
    if (is_outside_by_colrow(col, row))
        return OUTSIDE;
    
    return (b->game_board[col][row] == player);
}

int is_other_player_by_colrow(board* b, int col, int row, char player) {
    if (is_outside_by_colrow(col, row))
        return OUTSIDE;
    
    char other_p = (player == BLACK_C) ? WHITE_C : BLACK_C;

    return (b->game_board[col][row] == other_p);
}

int is_alone_by_colrow(board* b, int col, int row) {
    if (is_outside_by_colrow(col, row))
        return OUTSIDE;
    
    return (   (is_empty_by_colrow(b, row-1, col-1))
            && (is_empty_by_colrow(b, row,   col-1))
            && (is_empty_by_colrow(b, row+1, col-1))
            && (is_empty_by_colrow(b, row-1, col))
            && (is_empty_by_colrow(b, row+1, col))
            && (is_empty_by_colrow(b, row-1, col+1))
            && (is_empty_by_colrow(b, row,   col+1))
            && (is_empty_by_colrow(b, row+1, col+1)));

}

/*  By square name */

int get_piece(board* b, char* square_name, char* piece) {

    int col, row, err;

    err = convert_square(square_name, &col, &row);

    if (err != 0) { return err; }

    return get_piece_by_colrow(b, col, row, piece);
}

int put_piece(board* b, char* square_name, char piece) {

    int col, row, err;
    err = convert_square(square_name, &col, &row);
    if (err != 0) { return err; }

    return put_piece_by_colrow(b, col, row, piece);    
}


int is_empty(board* b, char* square_name) {
    int col, row, err;
    err = convert_square(square_name, &col, &row);
    if (err != 0) { return err; }

    return is_empty_by_colrow(b, col, row);
}

int is_player(board* b, char* square_name, char player) {
    int col, row, err;
    err = convert_square(square_name, &col, &row);
    if (err != 0) { return err; }

    return is_player_by_colrow(b, col, row, player);    
}

int is_other_player(board* b, char* square_name, char player) {
    int col, row, err;
    err = convert_square(square_name, &col, &row);
    if (err != 0) { return err; }

    return is_other_player_by_colrow(b, col, row, player);    
}

int is_alone(board* b, char* square_name) {
    int col, row, err;
    err = convert_square(square_name, &col, &row);
    if (err != 0) { return err; }

    return is_alone_by_colrow(b, col, row);
}


int init_board(board* b) {

    if (b == NULL) {return BAD_POINTER;}

    int i = MIN_SQ, j;

    for (;i <= MAX_SQ; i++) {
        for (j = MIN_SQ;j <= MAX_SQ; j++) {
            b->game_board[i][j] = EMPTY_C;
        }
    }

    put_piece(b, "D5", BLACK_C);
    put_piece(b, "E4", BLACK_C);
    put_piece(b, "D4", WHITE_C);
    put_piece(b, "E5", WHITE_C);
    
    return 0;
}

board* board_cp(board* b) {

    if (b == NULL) {
        return NULL;
    }

    board *b2 = (board*)malloc(sizeof(board));

    if (b2 == NULL) {
        /* malloc failed */
        return NULL;
    }

    int i,j;

    for (i=0; i<MAX_SQ; i++) {
        for (j=0; j<MAX_SQ; j++) {
            b2->game_board[i][j] = b->game_board[i][j];
        }
    }
    return b2;
}

/* _BOARD_C */
#endif
