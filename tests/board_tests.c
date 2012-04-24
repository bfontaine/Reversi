#include "tests_base.h"
#include "../src/board.c"

int main(void) {

    board* b = (board*)malloc(sizeof(board));
    board* b2 = NULL;
    char* sq;
    char p;

    int col = -1,
        row = -1;

    // convert squares
    sq = (char*)strdup("A1");
    assert(convert_square(sq, &col, &row) == 0);
    assert(col == 0);
    assert(row == 0);
    free(sq);

    sq = (char*)strdup("H8");
    assert(convert_square(sq, &col, &row) == 0);
    assert(col == 7);
    assert(row == 7);
    free(sq);

    sq = (char*)strdup("A8");
    assert(convert_square(sq, &col, &row) == 0);
    assert(col == 0);
    assert(row == 7);
    free(sq);

    sq = (char*)strdup("H1");
    assert(convert_square(sq, &col, &row) == 0);
    assert(col == 7);
    assert(row == 0);
    free(sq);

    sq = (char*)strdup("D7");
    assert(convert_square(sq, &col, &row) == 0);
    assert(col == 3);
    assert(row == 6);
    free(sq);

    sq = (char*)strdup("F2");
    assert(convert_square(sq, &col, &row) == 0);
    assert(col == 5);
    assert(row == 1);
    free(sq);

    sq = (char*)strdup("A9");
    assert(convert_square(sq, &col, &row) == OUTSIDE);
    free(sq);

    sq = (char*)strdup("I3");
    assert(convert_square(sq, &col, &row) == OUTSIDE);
    free(sq);

    sq = (char*)strdup("D0");
    assert(convert_square(sq, &col, &row) == OUTSIDE);
    free(sq);

    sq = (char*)strdup("0");
    assert(convert_square(sq, &col, &row) == NOT_A_SQUARE);
    free(sq);

    // initialize board
    assert(init_board(b) == 0);
    assert(init_board(b2) == BAD_POINTER);
    
    // get piece
    sq = (char*)strdup("E4");
    assert(get_piece(b, sq, &p) == 0);
    assert(p == 'B');
    free(sq);
    
    sq = (char*)strdup("D5");
    assert(get_piece(b, sq, &p) == 0);
    assert(p == 'B');
    free(sq);
    
    sq = (char*)strdup("D4");
    assert(get_piece(b, sq, &p) == 0);
    assert(p == 'W');
    free(sq);
    
    sq = (char*)strdup("E5");
    assert(get_piece(b, sq, &p) == 0);
    assert(p == 'W');
    free(sq);

    sq = (char*)strdup("E6");
    assert(get_piece(b, sq, &p) == 0);
    assert(p == 'E');
    free(sq);

    sq = (char*)strdup("E9");
    assert(get_piece(b, sq, &p) == OUTSIDE);
    free(sq);
     
    // put piece
    sq = (char*)strdup("E6");
    p = 'W';
    assert(put_piece(b, sq, p) == 0);
    p = '_';
    assert(get_piece(b, sq, &p) == 0);
    assert(p == 'W');
    free(sq);
     
    // put piece
    sq = (char*)strdup("A1");
    p = 'B';
    assert(put_piece(b, sq, p) == 0);
    p = '_';
    assert(get_piece(b, sq, &p) == 0);
    assert(p == 'B');
    free(sq);
     
    // put piece
    sq = (char*)strdup("A1");
    p = 'B';
    assert(put_piece(b, sq, p) == 0);
    p = '_';
    assert(get_piece(b, sq, &p) == 0);
    assert(p == 'B');
    free(sq);

    free(b);

    return 0;
}
