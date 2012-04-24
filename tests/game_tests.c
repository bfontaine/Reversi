#include "tests_base.h"
#include "../src/game/game.c"

// compare two moves arrays. Return 1 if they are equal (same moves, the order
// does not matter), else 0.
int compare_moves_arrays(char** a, char** b, int len) {

    int i=0, j;

    for (; i < len; i++) {
        for (j = 0; j < len; j++) {
            if (strcmp(a[i], b[i]))
                return 0;
            else
                continue;
        }
    }
    return 1;

}

int main(void) {

    board* b = (board*)malloc(sizeof(board));
    char** moves = NULL;
    int moves_nb = 0;

    char* initial_moves[] = {"E6", "F5", "C4", "D3"};

    assert(init_board(b) == 0);

    // first move (black)
    moves_nb = get_possible_moves(b, BLACK_C, moves);
    assert(moves_nb == 4);
    assert(moves != NULL);
    assert(compare_moves_arrays(moves, initial_moves, moves_nb));


    return 0;
}
