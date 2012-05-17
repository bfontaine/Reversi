#ifndef _TEXT_C
#define _TEXT_C 1

#include <stdio.h>
#include "interface.h"

/**
 * Basic text interface as described in the subject.
 **/

int init_interface() {
    return 0;
}


int close_interface() {
    return 0;
}


int print_board(board *b) {

    int r=MAX_SQ, c, pretty_c = 8;

    if (BOARD_PRETTY_PRINT) {
        fputs("   A B C D E F G H\n", stderr);
    }

    for (; r>=MIN_SQ; r--) {
        if (BOARD_PRETTY_PRINT) {
            fprintf(stderr, "%d ", pretty_c--);
        }
        for (c=MIN_SQ; c<=MAX_SQ; c++) {
            fprintf(stderr, " %c", b->game_board[c][r]);
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
    
    if (!moves_number) { return 0; }

    printf("COUPS %s", moves[0]);

    if (moves_number == 1) {
        puts(".");
        return 0;
    }

    int i=1;

    for (; i<moves_number; i++) {
        printf(", %s", moves[i]);
    }
    puts(".");

    return 0;
}


int print_winner(char winner) {

    if (winner == WHITE_C) {
        puts("BLANC gagne");
        
    } else if (winner == BLACK_C) {
        puts("NOIR gagne");

    } else if (winner == TIE_C) {
        puts("Egalite");
    
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

/* _TEXT_C */
#endif
