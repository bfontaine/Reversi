#include "board.h"

#ifndef _BOARD_C
#define _BOARD_C 1

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

int get_piece(board* b, char* square_name, char* piece) {

    int col, row, err;

    err = convert_square(square_name, &col, &row);

    if (err != 0) { return err; }

    *piece = b->game_board[col][row];
    
    return 0;
}

int put_piece(board* b, char* square_name, char piece) {

    int col, row, err;
    err = convert_square(square_name, &col, &row);
    if (err != 0) { return err; }

    b->game_board[col][row] = piece;
    
    return 0;
}

int init_board(board* b) {

    if (b == NULL) {
        b = (board*)malloc(sizeof(board));
    }

    int i = MIN_SQ,
        j = MIN_SQ;

    for (;i <= MAX_SQ; i++) {
        for (;j <= MAX_SQ; j++) {
            b->game_board[i][j] = EMPTY_C;
        }
    }

    put_piece(b, "D5", BLACK_C);
    put_piece(b, "E4", BLACK_C);
    put_piece(b, "D4", WHITE_C);
    put_piece(b, "E5", WHITE_C);
    
    return 0;
}

#endif // _BOARD_C
