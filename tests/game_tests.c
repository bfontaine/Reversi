#include "tests_base.h"
#include "../src/game/game.c"

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

    /* test a move:
     *	P: player (WHITE_C or BLACK_C)
     *	S: square (e.g. "E6")
     *	SC: score made with this move
     *	SCW: score for white player
     *	SCB: score for black player
     */
#define T_PLAY(P,S,SC,SCW,SCB) assert(play(b,P,S) == SC); \
    assert(get_score(b, WHITE_C) == SCW); \
    assert(get_score(b, BLACK_C) == SCB); \
    assert(get_piece(b, S, &piece) == 0); \
    assert(piece == P); \
                               
    
    /* black plays in E6*/
    T_PLAY(BLACK_C,"E6",2,1,4)

    /* white plays in F4*/
    T_PLAY(WHITE_C,"F4",2,3,3)

    /* black plays in E3*/
    T_PLAY(BLACK_C,"E3",2,2,5)

    /* white plays in F6*/
    T_PLAY(WHITE_C,"F6",2,4,4)

    /* black plays in F5*/
    T_PLAY(BLACK_C,"F5",2,3,6)

    /* white plays in D6*/
    T_PLAY(WHITE_C,"D6",4,7,3)

    /* black plays in C6*/
    T_PLAY(BLACK_C,"C6",2,6,5)

    /* white plays in G5*/
    T_PLAY(WHITE_C,"G5",2,8,4)

    /* black plays in G6*/
    T_PLAY(BLACK_C,"G6",5,4,9)

    /* white plays in C5*/
    T_PLAY(WHITE_C,"C5",2,6,8)

    // the board is not full
    assert(is_full(b) == 0);

    /* black plays in C4*/
    T_PLAY(BLACK_C,"C4",4,3,12)

    /* white plays in G7*/
    T_PLAY(WHITE_C,"G7",3,6,10)

    /* TODO continue game until one player can pass his turn
     * TODO continue game until one player won */

    free(moves);
    free(b);

    return 0;
}
