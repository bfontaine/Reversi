#include <stdio.h>
#include "game.h"

#ifndef _GAME_C
#define _GAME_C 1

int can_play(board *b, int col, int row, char player) {

#define IS_ME(i,j) (b->game_board[i][j]==player)
    
    if (b->game_board[col][row] != 'E')
        return 0;

    int i, j;
    
    /*
     1 2 3
     4 X 5
     6 7 8
     */

    if (b->game_board[col-1][row+1] != player) {
        // 1
        for (i=col-2, j=row+2; i >= MIN_SQ && j <= MAX_SQ; i--, j++) {
            if IS_ME(i,j) {
                return 1;
            }
        }
    }

    if (b->game_board[col+1][row+1] != player) {
        // 3
        for (i=col+2, j=row+2; i <= MAX_SQ && j <= MAX_SQ; i++, j++) {
            if IS_ME(i,j) {
                return 1;
            }
        }
    }

    if (b->game_board[col+1][row-1] != player) {
        // 8
        for (i=col+2, j=row-2; i <= MAX_SQ && j >= MIN_SQ; i++, j--) {
            if IS_ME(i,j) {
                return 1;
            }
        }
    }

    if (b->game_board[col-1][row-1] != player) {
        // 6
        for (i=col-2, j=row-2; i >= MIN_SQ && j >= MIN_SQ; i--, j--) {
            if IS_ME(i,j) {
                return 1;
            }
        }
    }

    return 0;
}

int get_possible_moves(board *b, char player, char** moves) {

    int i = MIN_SQ, j, moves_nb;

    for (; i <= MAX_SQ; i++) {
        for (j=MIN_SQ; j <= MAX_SQ; j++) {
            if (b->game_board[i][j] != 'E') {
                continue;
            }
            if (can_play(b, i, j, player)) {
                moves_nb++;
                //TODO
            }
        }
    }

    return 0;
}

#endif // _GAME_C
