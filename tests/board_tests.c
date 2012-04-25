#include "tests_base.h"
#include "../src/game/board.c"

int main(void) {

    board* b = (board*)malloc(sizeof(board));
    board* b2 = NULL;
    char p;

    int col = -1,
        row = -1;

    // convert squares
    assert(convert_square("A1", &col, &row) == 0);
    assert(col == 0);
    assert(row == 0);

    assert(convert_square("H8", &col, &row) == 0);
    assert(col == 7);
    assert(row == 7);

    assert(convert_square("A8", &col, &row) == 0);
    assert(col == 0);
    assert(row == 7);

    assert(convert_square("H1", &col, &row) == 0);
    assert(col == 7);
    assert(row == 0);

    assert(convert_square("D7", &col, &row) == 0);
    assert(col == 3);
    assert(row == 6);

    assert(convert_square("F2", &col, &row) == 0);
    assert(col == 5);
    assert(row == 1);

    assert(convert_square("A9", &col, &row) == OUTSIDE);
    assert(convert_square("I3", &col, &row) == OUTSIDE);
    assert(convert_square("D0", &col, &row) == OUTSIDE);

    assert(convert_square("0", &col, &row) == NOT_A_SQUARE);

    // initialize board
    assert(init_board(b) == 0);
    assert(init_board(b2) == BAD_POINTER);
    
    // get piece

    assert(get_piece(b, "E4", &p) == 0);
    assert(p == BLACK_C);
    
    assert(get_piece(b, "D5", &p) == 0);
    assert(p == BLACK_C);
    
    assert(get_piece(b, "D4", &p) == 0);
    assert(p == WHITE_C);
    
    assert(get_piece(b, "E5", &p) == 0);
    assert(p == WHITE_C);

    assert(get_piece(b, "E6", &p) == 0);
    assert(p == EMPTY_C);

    assert(get_piece(b, "E9", &p) == OUTSIDE);
     
    // put piece
    p = WHITE_C;
    assert(put_piece(b, "E6", p) == 0);
    p = '_';
    assert(get_piece(b, "E6", &p) == 0);
    assert(p == WHITE_C);
     
    p = BLACK_C;
    assert(put_piece(b, "A1", p) == 0);
    p = '_';
    assert(get_piece(b, "A1", &p) == 0);
    assert(p == BLACK_C);
     
    p = BLACK_C;
    assert(put_piece(b, "A1", p) == 0);
    p = '_';
    assert(get_piece(b, "A1", &p) == 0);
    assert(p == BLACK_C);

    // is empty
    assert(is_empty(b, "A1") == 0);
    assert(is_empty(b, "A2") == 1);
    assert(is_empty(b, "A0") == OUTSIDE);
    assert(is_empty(b, "w") == NOT_A_SQUARE);

    // is player
    assert(is_player(b, "D4", BLACK_C) == 0);
    assert(is_player(b, "D4", WHITE_C) == 1);
    assert(is_player(b, "E4", BLACK_C) == 1);
    assert(is_player(b, "E4", WHITE_C) == 0);
    assert(is_player(b, "A2", BLACK_C) == 0);
    assert(is_player(b, "A2", WHITE_C) == 0);
    assert(is_player(b, "A0", WHITE_C) == OUTSIDE);
    assert(is_player(b, "w", WHITE_C) == NOT_A_SQUARE);
    
    // is other player
    assert(is_other_player(b, "D4", BLACK_C) == 1);
    assert(is_other_player(b, "D4", WHITE_C) == 0);
    assert(is_other_player(b, "E4", BLACK_C) == 0);
    assert(is_other_player(b, "E4", WHITE_C) == 1);
    assert(is_other_player(b, "A2", BLACK_C) == 0);
    assert(is_other_player(b, "A2", WHITE_C) == 0);
    assert(is_other_player(b, "A0", WHITE_C) == OUTSIDE);
    assert(is_other_player(b, "w", WHITE_C) == NOT_A_SQUARE);


    free(b);

    return 0;
}
