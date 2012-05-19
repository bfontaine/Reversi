#ifndef _GAME_C
#define _GAME_C 1

#include <stdio.h>
#include "game.h"

int can_play(board *b, int col, int row, char player, int* directions) {
    
    if (!is_empty_by_colrow(b, col, row)) {
        return 0;
    }

    int i, j,
        set_directions=0;
    
    if (directions != NULL) {
        set_directions = 1;
        *directions = 0;
    }
    
    /*
     1 2 3
     4 X 5
     6 7 8
     */

    if (col > 1+MIN_SQ) {

        if ((row < MAX_SQ-1) && (is_other_player_by_colrow(b, col-1, row+1, player))) {
            /* 1 */
            for (i=col-2, j=row+2; i >= MIN_SQ && j <= MAX_SQ; i--, j++) {
                if (is_player_by_colrow(b, i, j, player)) {
                    if (!set_directions) {return 1;}
                    *directions |= CAN_PLAY_UPLEFT;
                } else if (is_empty_by_colrow(b, i, j)) {
                    break;
                }

            }
        }

        if (is_other_player_by_colrow(b, col-1, row, player)) {
            /*  4 */
            for (i=col-2; i >= MIN_SQ; i--) {
                if (is_player_by_colrow(b, i, row, player)) {
                    if (!set_directions) {return 1;}
                    *directions |= CAN_PLAY_LEFT;
                } else if (is_empty_by_colrow(b, i, row)) {
                    break;
                }
            }
        }

        if ((row > 1+MIN_SQ) && (is_other_player_by_colrow(b, col-1, row-1, player))) {
            /*  6 */
            for (i=col-2, j=row-2; i >= MIN_SQ && j >= MIN_SQ; i--, j--) {
                if (is_player_by_colrow(b, i, j, player)) {
                    if (!set_directions) {return 1;}
                    *directions |= CAN_PLAY_DOWNLEFT;
                } else if (is_empty_by_colrow(b, i, j)) {
                    break;
                }

            }
        }
    }

    if (col < MAX_SQ-1) {

        if ((row <= MAX_SQ-1) && (is_other_player_by_colrow(b, col+1, row+1, player))) {
            /*  3 */
            for (i=col+2, j=row+2; i <= MAX_SQ && j <= MAX_SQ; i++, j++) {
                if (is_player_by_colrow(b, i, j, player)) {
                    if (!set_directions) {return 1;}
                    *directions |= CAN_PLAY_UPRIGHT;
                } else if (is_empty_by_colrow(b, i, j)) {
                    break;
                }

            }
        }

        if (is_other_player_by_colrow(b, col+1, row, player)) {
            /*  5 */
            for (i=col+2; i <= MAX_SQ; i++) {
                if (is_player_by_colrow(b, i, row, player)) {
                    if (!set_directions) {return 1;}
                    *directions |= CAN_PLAY_RIGHT;
                } else if (is_empty_by_colrow(b, i, row)) {
                    break;
                }

            }
        }

        if ((row > MIN_SQ+1) && (is_other_player_by_colrow(b, col+1, row-1, player))) {
            /*  8 */
            for (i=col+2, j=row-2; i <= MAX_SQ && j >= MIN_SQ; i++, j--) {
                if (is_player_by_colrow(b, i, j, player)) {
                    if (!set_directions) {return 1;}
                    *directions |= CAN_PLAY_DOWNRIGHT;
                } else if (is_empty_by_colrow(b, i, j)) {
                    break;
                }
            }
        }
    }

    if ((row > 1+MIN_SQ) && (is_other_player_by_colrow(b, col, row-1, player))) {
        /*  7 */

        for (i=row-2; i >= MIN_SQ; i--) {
            if (is_player_by_colrow(b, col, i, player)) {
                if (!set_directions) {return 1;}
                *directions |= CAN_PLAY_DOWN;
            } else if (is_empty_by_colrow(b, col, i)) {
                break;
            }

        }
    }

    if ((row < MAX_SQ-1) && (is_other_player_by_colrow(b, col, row+1, player))) {
        /*  2 */
        for (i=row+2; i <= MAX_SQ; i++) {
            if (is_player_by_colrow(b, col, i, player)) {
                if (!set_directions) {return 1;}
                *directions |= CAN_PLAY_UP;
            } else if (is_empty_by_colrow(b, col, i)) {
                break;
            }

        }
    }

    return (set_directions && (*directions != 0));
}

int get_possible_moves(board *b, char player, char*** moves) {

    int i = MAX_SQ, j, moves_nb=0;

    for (; i >= MIN_SQ; i--) {
        for (j=MIN_SQ; j <= MAX_SQ; j++) {
            if (can_play(b, j, i, player, NULL)) {
                if ((*moves)[moves_nb] == NULL) {
                    (*moves)[moves_nb] = (char*)malloc(sizeof(char)*3);
                }
                (*moves)[moves_nb][0] = FIRST_LETTER+i; /* FIXME 
                                                           segfault ici
                avec l'intelligence artificielle, compute_moves avec deep=1
                                                        */
                (*moves)[moves_nb][1] = FIRST_DIGIT+j;
                (*moves)[moves_nb][2] = '\0';
                moves_nb++;
            }
        }
    }
    return moves_nb;
}

int get_score(board *b, char player) {

    if (player == '\0') {
        return get_score(b, WHITE_C) - get_score(b, BLACK_C);
    }
    
    int i=MIN_SQ, j, score=0;

    for (; i<=MAX_SQ; i++) {
        for (j=MIN_SQ; j<=MAX_SQ; j++) {
            if (b->game_board[i][j] == player) {
                score++;
            }
        }
    }

    return score;
}

int play(board *b, char player, char* square_name) {

    int i, j, col, row, err, pts=0, directions=0;

    err = convert_square(square_name, &col, &row);

    if (err) { return err; }

    if (!is_empty_by_colrow(b, col, row)) {
        return NOT_EMPTY;
    }

    if (!can_play(b, col, row, player, &directions)) {
        return CANNOT_PLAY_HERE;
    }

    put_piece_by_colrow(b, col, row, player);
    pts = 1;

    if (directions & CAN_PLAY_UPLEFT) {
       for (i=col-1, j=row+1;
                   i>= MIN_SQ
                && j<= MAX_SQ
                && is_other_player_by_colrow(b, i, j, player);
            i--, j++) {

           put_piece_by_colrow(b, i, j, player);
           pts++;
       } 
    }

    if (directions & CAN_PLAY_UP) {
       for (i=row+1;
                  i<= MAX_SQ
               && is_other_player_by_colrow(b, col, i, player);
            i++) {

           put_piece_by_colrow(b, col, i, player);
           pts++;
       } 
    }

    if (directions & CAN_PLAY_UPRIGHT) {
       for (i=col+1, j=row+1;
                   i<= MAX_SQ
                && j<= MAX_SQ
                && is_other_player_by_colrow(b, i, j, player);
            i++, j++) {

           put_piece_by_colrow(b, i, j, player);
           pts++;
       } 
    }

    if (directions & CAN_PLAY_LEFT) {
       for (i=col-1;
                   i>= MIN_SQ
                && is_other_player_by_colrow(b, i, row, player);
            i--) {

           put_piece_by_colrow(b, i, row, player);
           pts++;
       } 
    }

    if (directions & CAN_PLAY_RIGHT) {
       for (i=col+1;
                   i<= MAX_SQ
                && is_other_player_by_colrow(b, i, row, player);
            i++) {

           put_piece_by_colrow(b, i, row, player);
           pts++;
       } 
    }

    if (directions & CAN_PLAY_DOWNLEFT) {
       for (i=col-1, j=row-1;
                   i>= MIN_SQ
                && j>= MIN_SQ
                && is_other_player_by_colrow(b, i, j, player);
            i--, j--) {

           put_piece_by_colrow(b, i, j, player);
           pts++;
       } 
    }

    if (directions & CAN_PLAY_DOWN) {
       for (i=row-1;
                   i>= MIN_SQ
                && is_other_player_by_colrow(b, col, i, player);
            i--) {

           put_piece_by_colrow(b, col, i, player);
           pts++;
       } 
    }

    if (directions & CAN_PLAY_DOWNRIGHT) {
       for (i=col+1, j=row-1;
                   i<= MAX_SQ
                && j>= MIN_SQ
                && is_other_player_by_colrow(b, i, j, player);
            i++, j--) {

           put_piece_by_colrow(b, i, j, player);
           pts++;
       } 
    }
    
    return pts;
}

/* _GAME_C */
#endif
