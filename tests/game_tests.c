#include "tests_base.h"
#include "../src/game/game.c"

#include "../src/interfaces/text.c"

/* compare two moves arrays. Return 1 if they are equal (same moves, the order*/
/* does not matter), else 0.*/
int compare_moves_arrays(char** a, char** b, int len) {

    int i=0, j, ok;

    /* we assume that each array have exactly `len` different values*/

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
    int i, moves_nb = 0, directions=0;

    char* initial_moves_b[] = {"E6", "F5", "C4", "D3"};
    char* initial_moves_w[] = {"E3", "F4", "C5", "D6"};
    char piece = '\0';

    assert(init_board(b) == 0);

    /* initial scores*/
    assert(get_score(b, WHITE_C) == 2);
    assert(get_score(b, BLACK_C) == 2);

    /* possible first moves with white (this is a test, not a normal game)*/
    moves_nb = get_possible_moves(b, WHITE_C, &moves);
    assert(moves_nb == 4);
    assert(moves != NULL);
    assert(compare_moves_arrays(moves, initial_moves_w, moves_nb));
    for (i=0; i<moves_nb; i++) {
        free(moves[i]);
    }

    /* possible first moves with black*/
    moves_nb = get_possible_moves(b, BLACK_C, &moves);
    assert(moves_nb == 4);
    assert(moves != NULL);
    assert(compare_moves_arrays(moves, initial_moves_b, moves_nb));
    for (i=0; i<moves_nb; i++) {
        free(moves[i]);
    }
    /* check if black can play in E6*/
    assert(can_play(b, 4, 5, BLACK_C, &directions) == 1);
    assert(can_play(b, 4, 5, BLACK_C, NULL) == 1);
    assert(directions == CAN_PLAY_DOWN);
    
    /* black plays in E6*/
    assert(play(b, BLACK_C, "E6") == 2);
    assert(get_score(b, WHITE_C) == 1);
    assert(get_score(b, BLACK_C) == 4);
    assert(get_piece(b, "E6", &piece) == 0);
    assert(piece == BLACK_C);

    /* white plays in F4*/
    assert(play(b, WHITE_C, "F4") == 2);
    assert(get_score(b, WHITE_C) == 3);
    assert(get_score(b, BLACK_C) == 3);
    assert(get_piece(b, "F4", &piece) == 0);
    assert(piece == WHITE_C);

    /* black plays in E3*/
    assert(play(b, BLACK_C, "E3") == 2);
    assert(get_score(b, WHITE_C) == 2);
    assert(get_score(b, BLACK_C) == 5);
    assert(get_piece(b, "E3", &piece) == 0);
    assert(piece == BLACK_C);

    /* white plays in F6*/
    assert(play(b, WHITE_C, "F6") == 2);
    assert(get_score(b, WHITE_C) == 4);
    assert(get_score(b, BLACK_C) == 4);
    assert(get_piece(b, "F6", &piece) == 0);
    assert(piece == WHITE_C);

    /* black plays in F5*/
    assert(play(b, BLACK_C, "F5") == 2);
    assert(get_score(b, WHITE_C) == 3);
    assert(get_score(b, BLACK_C) == 6);
    assert(get_piece(b, "F5", &piece) == 0);
    assert(piece == BLACK_C);

    /* white plays in D6*/
    assert(play(b, WHITE_C, "D6") == 4);
    assert(get_score(b, WHITE_C) == 7);
    assert(get_score(b, BLACK_C) == 3);
    assert(get_piece(b, "D6", &piece) == 0);
    assert(piece == WHITE_C);

    /* TODO continue game until one player can pass his turn
     * TODO continue game until one player won */

    free(moves);
    free(b);

    return 0;
}
