#include "tests_base.h"
#include "../src/board.c"

int main(void) {

    board* b = (board*)malloc(sizeof(board));
    char* sq;
    char p;

    // initialize board
    assert(init_board(b) == 0);
    
    sq = (char*)strdup("E4");
    assert(get_piece(sq, &p) == 0);
    assert(p == 'B');
    
    sq = (char*)strdup("D5");
    assert(get_piece(sq, &p) == 0);
    assert(p == 'B');
    
    sq = (char*)strdup("D4");
    assert(get_piece(sq, &p) == 0);
    assert(p == 'W');
    
    sq = (char*)strdup("E5");
    assert(get_piece(sq, &p) == 0);
    assert(p == 'W');
     

    free(b);
    free(sq);

    return 0;
}
