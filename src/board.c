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

int get_piece(char* square_name, char* piece) {
    
    return 0;
}

int put_piece(char* square_name, char* piece) {
    
    return 0;
}

int init_board(board* b) {
    
    return 0;
}












#endif // _BOARD_C
