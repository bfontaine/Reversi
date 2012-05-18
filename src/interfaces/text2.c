#ifndef _TEXT_2_C
#define _TEXT_2_C 1

#include <stdio.h>
#include "interface.h"

#define COMMAND_PROMPT "reversi> "

int init_interface() {
    return 0;
}


int close_interface() {
    return 0;
}


int print_board(board *b) {

    int r=MAX_SQ, c, pretty_c = 8;
    char sq;

    if (BOARD_PRETTY_PRINT) {
        fputs("   A B C D E F G H\n", stderr);
    }

    for (; r>=MIN_SQ; r--) {
        if (BOARD_PRETTY_PRINT) {
            fprintf(stderr, "%d ", pretty_c--);
        }
        for (c=MIN_SQ; c<=MAX_SQ; c++) {
            sq = b->game_board[c][r];
            if (BOARD_COLORS == 0) {

                if (sq == BLACK_C) {
                    sq = FRENCH_BLACK_C;
                }
                else if (sq == WHITE_C) {
                    sq = FRENCH_WHITE_C;
                }

                fprintf(stderr, " %c", sq);
            } else {
                /* colors */
                if (sq == BLACK_C) {
                    fprintf(stderr, BOARD_COLOR_B, FRENCH_BLACK_C);
                }
                else if (sq == WHITE_C) {
                    fprintf(stderr, BOARD_COLOR_W, FRENCH_WHITE_C);
                }
                else if ((r+c)%2 == 1) {
                    sq = (BOARD_PRINT_EMPTY) ? sq : ' ';
                    fprintf(stderr, BOARD_COLOR_1, sq);
                }
                else if ((r+c)%2 == 0) {
                    sq = (BOARD_PRINT_EMPTY) ? sq : ' ';
                    fprintf(stderr, BOARD_COLOR_2, sq);
                }
            }
        }
        fprintf(stderr, "\n");
    }

    return 0;
}


int print_score(int score) {
    printf("SCORE %02d\n", score);
    return 0;
}


int print_moves(char** moves, int moves_number) {
    
    if (!moves_number) {
        puts("COUPS");
        return 0;
    }

    printf("COUPS");

    int i=0;

    for (; i<moves_number; i++) {
        printf(" %2s", moves[i]);
    }
    puts("");

    return 0;
}


int print_winner(char winner) {

    if (winner == WHITE_C) {
        puts("BLANC gagne.");
        
    } else if (winner == BLACK_C) {
        puts("NOIR gagne.");

    } else if (winner == TIE_C) {
        puts("Egalite.");
    
    }

    return 0;
}


int print_error(char* error_str) {

    printf("ERREUR %s\n", error_str);
    return 0;
}


int print_notice(char* notice_str) {

    printf("%s\n", notice_str);
    return 0;
}


int read_command(char** command) {

    if (*command == NULL) {
        return -21;
    }
    /* we assume that strlen(*command) >= CMD_MAX_SIZE */

    char c = fgetc(stdin);
    int len = 0;

    while ((c != EOF) && (c != '\n') && (len+1 < CMD_MAX_SIZE)) {
        if (len+1 < CMD_MAX_SIZE) {
            *((*command)+(len++)) = c;
        }

        c = fgetc(stdin);
    }
    *((*command)+len) = '\0';

    return 0;
}


#endif /* _TEXT_2_C */
