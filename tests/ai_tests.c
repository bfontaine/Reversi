#include <stdio.h>
#include "tests_base.h"
#include "../src/game/board.c"
#include "../src/game/game.c"
#include "../src/ai/ai.c"

int main(int argc, char **argv) {

    board* b = (board*)malloc(sizeof(board));
    assert(init_board(b) == 0);

    ai* AI = create_ai(b, BLACK_C);

    assert(AI != NULL);

    free_ai(AI); 
    free(b);
    
    return 0;
}
