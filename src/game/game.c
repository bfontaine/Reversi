#include <stdio.h>
#include "game.h"

#ifndef _GAME_C
#define _GAME_C 1

int can_play(board *b, int col, int row, char player) {
    
    if (is_empty_by_rowcol(b, col, row) != 1)
        return 0;

    int i, j;
    
    /*
     1 2 3
     4 X 5
     6 7 8
     */

    if (col > 1+MIN_SQ) {

        if ((row < MAX_SQ-1) && (is_other_player_by_rowcol(b, col-1, row+1, player))) {
            // 1
            for (i=col-2, j=row+2; i >= MIN_SQ && j <= MAX_SQ; i--, j++) {
                if (is_player_by_rowcol(b, i, j, player)) {
                    return 1;
                }
            }
        }

        if (is_other_player_by_rowcol(b, col-1, row, player)) {
            // 4
            for (i=col-2; i >= MIN_SQ; i--) {
                if (is_player_by_rowcol(b, i, row, player)) {
                    return 1;
                }
            }
        }

        if ((row > 1+MIN_SQ) && (is_other_player_by_rowcol(b, col-1, row-1, player))) {
            // 6
            for (i=col-2, j=row-2; i >= MIN_SQ && j >= MIN_SQ; i--, j--) {
                if (is_player_by_rowcol(b, i, j, player)) {
                    return 1;
                }
            }
        }

    }

    if (col < MAX_SQ-1) {

        if ((row > 1+MIN_SQ) && (is_other_player_by_rowcol(b, col+1, row+1, player))) {
            // 3
            for (i=col+2, j=row+2; i <= MAX_SQ && j <= MAX_SQ; i++, j++) {
                if (is_player_by_rowcol(b, i, j, player)) {
                    return 1;
                }
            }
        }

        if (is_other_player_by_rowcol(b, col+1, row, player)) {
            // 5
            for (i=col+2; i <= MAX_SQ; i++) {
                if (is_player_by_rowcol(b, i, row, player)) {
                    return 1;
                }
            }
        }

        if ((row < MAX_SQ-1) && (is_other_player_by_rowcol(b, col+1, row-1, player))) {
            // 8
            for (i=col+2, j=row-2; i <= MAX_SQ && j >= MIN_SQ; i++, j--) {
                if (is_player_by_rowcol(b, i, j, player)) {
                    return 1;
                }
            }
        }
    }

    if ((row > 1+MIN_SQ) && (is_other_player_by_rowcol(b, col, row-1, player))) {
        // 7
        for (i=row-2; i >= MIN_SQ; i--) {
            if (is_player_by_rowcol(b, col, i, player)) {
                return 1;
            }
        }
    }

    if ((row < MAX_SQ-1) && (is_other_player_by_rowcol(b, col, row+1, player))) {
        // 2
        for (i=row+2; i <= MAX_SQ; i++) {
            if (is_player_by_rowcol(b, col, i, player)) {
                return 1;
            }
        }
    }

    return 0;
}

int get_possible_moves(board *b, char player, char*** moves) {

    int i = MIN_SQ, j, moves_nb=0;

    for (; i <= MAX_SQ; i++) {
        for (j=MIN_SQ; j <= MAX_SQ; j++) {
            if (!is_empty_by_rowcol(b, i, j)) {
                continue;
            }
            if (can_play(b, i, j, player)) {
                (*moves)[moves_nb] = (char*)malloc(sizeof(char)*3);
                (*moves)[moves_nb][0] = FIRST_LETTER+i;
                (*moves)[moves_nb][1] = FIRST_DIGIT+j;
                (*moves)[moves_nb][2] = '\0';
                moves_nb++;
            }
        }
    }
    return moves_nb;
}

int get_score(board *b, char player) {
    //TODO
    return 0;
}

int play(board *b, char player, char* square_name) {

    //TODO
    
    return 0;
}

#endif // _GAME_C
