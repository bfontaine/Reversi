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
    
    int r=MAX_SQ, c;

    for (; r>=MIN_SQ; r--) {
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

    char* newline, c = '\0';

    fflush(stdin);
    if (fgets(*command, sizeof *command, stdin) == NULL) {
        return 1;
    }
        
    newline = strchr(*command, '\n');
    if (newline != NULL) {
        /* if there is a newline */
        *newline = '\0';
    } else {
        /* if there is no newline */
        puts("");
    }

    /* flush stdin */
    while (c != '\n' && c != EOF) {
        c = getchar();
    }

    return 0;
}



#endif /* _TEXT_C */
