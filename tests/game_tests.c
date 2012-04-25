#include "tests_base.h"
#include "../src/game/game.c"

// compare two moves arrays. Return 1 if they are equal (same moves, the order
// does not matter), else 0.
int compare_moves_arrays(char** a, char** b, int len) {

    int i=0, j, ok;

    // we assume that each array have exactly `len` different values

    for (i=0; i < len; i++) {
        ok = 0;
        for (j = 0; j < len; j++) {
            if (!strcmp(a[i], b[j])) {
                ok = 1;
            }
        }
        if (!ok)
            return 0;
    }
    return 1;
}

int main(void) {

    board* b = (board*)malloc(sizeof(board));
    char** moves = (char**)malloc(30*sizeof(char*));
    int i, moves_nb = 0;

    char* initial_moves[] = {"E6", "F5", "C4", "D3"};

    assert(init_board(b) == 0);

    // first move (black)
    moves_nb = get_possible_moves(b, BLACK_C, &moves);
    assert(moves_nb == 4);
    assert(moves != NULL);
    assert(compare_moves_arrays(moves, initial_moves, moves_nb));


    for (i=0; i<moves_nb; i++) {
        free(moves[i]);
    }
    free(moves);
    free(b);

    return 0;
}
