#include <stdio.h>
#include "game.h"

#ifndef _GAME_C
#define _GAME_C 1

int get_possible_moves(board *b, char player, char** moves) {

    int i = MIN_SQ, j;

    for (; i <= MAX_SQ; i++) {
        for (j=MIN_SQ; j <= MAX_SQ; j++) {
            if (b->game_board[i][j] != 'E') {
                continue;
            }
            //TODO
        }
    }

    return 0;
}

#endif // _GAME_C
