#include <stdio.h>
#include "interface.h"

#ifndef _TEXT_C
#define _TEXT_C 1

int init_interface() {
    return 0;
}


int close_interface() {
    return 0;
}


int print_board(board *b) {
    //TODO
    return 0;
}


int print_score(int score) {
    println("SCORE %3d\n", score);
    return 0;
}


int print_moves(char** moves, int moves_number) {
    //TODO
    return 0;
}


int print_winner(char winner) {

    if (winner == WHITE_C) {
        puts("WHITE won");
        
    } else if (winner == BLACK_C) {
        puts("BLACK won");

    } else if (winner == TIE_C) {
        puts("Tie");
    
    } else { // should not happen
        puts("Chuck Norris won");
    }

    return 0;
}


int print_error(char** error_str) {

    println("ERROR %s\n", error_str);
    return 0;
}


int print_notice(char** notice_str) {

    println("%s\n", notice_str);
    return 0;
}


int get_command(char* command) {
    //TODO
    return 0;
}



#endif // _TEXT_C
