#include <stdio.h>
#include "game.h"

#ifndef _GAME_C
#define _GAME_C 1

int can_play(board *b, int col, int row, char player) { // FIXME (IS_NOT_ME)

#define IS_ME(i,j) (b->game_board[i][j]==player)
#define IS_NOT_ME(i,j) (b->game_board[i][j]==(OTHER_C(player)))
    
    if (b->game_board[col][row] != 'E')
        return 0;

    int i, j;
    
    /*
     1 2 3
     4 X 5
     6 7 8
     */

    if (col > 1+MIN_SQ) {

        if ((row < MAX_SQ-1) && (IS_NOT_ME(col-1,row+1))) {
            // 1
            for (i=col-2, j=row+2; i >= MIN_SQ && j <= MAX_SQ; i--, j++) {
                if (IS_ME(i,j)) {
                    return 1;
                }
            }
        }

        if (IS_NOT_ME(col-1,row)) {
            // 4
            for (i=col-2; i >= MIN_SQ; i--) {
                if (IS_ME(i,j)) {
                    return 1;
                }
            }
        }

        if ((row > 1+MIN_SQ) && (IS_NOT_ME(col-1,row-1))) {
            // 6
            for (i=col-2, j=row-2; i >= MIN_SQ && j >= MIN_SQ; i--, j--) {
                if (IS_ME(i,j)) {
                    return 1;
                }
            }
        }

    }

    if (col < MAX_SQ-1) {

        if ((row > 1+MIN_SQ) && (IS_NOT_ME(col+1,row+1))) {
            // 3
            for (i=col+2, j=row+2; i <= MAX_SQ && j <= MAX_SQ; i++, j++) {
                if (IS_ME(i,j)) {
                    return 1;
                }
            }
        }

        if (IS_NOT_ME(col+1,row)) {
            // 5
            for (i=col+2; i <= MAX_SQ; i++) {
                if (IS_ME(i,j)) {
                    return 1;
                }
            }
        }

        if ((row < MAX_SQ-1) && (IS_NOT_ME(col+1,row-1))) {
            // 8
            for (i=col+2, j=row-2; i <= MAX_SQ && j >= MIN_SQ; i++, j--) {
                if (IS_ME(i,j)) {
                    return 1;
                }
            }
        }
    }

    if ((row > 1+MIN_SQ) && (IS_NOT_ME(col,row-1))) {
        // 7
        for (i=row-2; i >= MIN_SQ; i--) {
            if (IS_ME(i,j)) {
                return 1;
            }
        }
    }

    if ((row < MAX_SQ-1) && (IS_NOT_ME(col,row+1))) {
        // 2
        for (i=row+2; i <= MAX_SQ; i++) {
            if (IS_ME(i,j)) {
                return 1;
            }
        }
    }

    return 0;
}

int get_possible_moves(board *b, char player, char** moves) {

    int i = MIN_SQ, j, moves_nb=0;

    moves = (char**)malloc(30*sizeof(char*));

    for (; i <= MAX_SQ; i++) {
        for (j=MIN_SQ; j <= MAX_SQ; j++) {
            if (b->game_board[i][j] != 'E') {
                continue;
            }
            if (can_play(b, i, j, player)) {
                moves[moves_nb] = (char*)malloc(sizeof(char)*3);
                moves[moves_nb][0] = FIRST_LETTER+i;
                moves[moves_nb][1] = FIRST_LETTER+MAX_SQ+j;
                moves_nb++;
            }
        }
    }

    return moves_nb;
}

#endif // _GAME_C
