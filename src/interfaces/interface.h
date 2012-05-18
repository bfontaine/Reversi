#ifndef _INTERFACE_H
#define _INTERFACE_H 1

#include "../utils.h"
#include "../game/board.h"
#include "../game/game.h"

/*  initialize the interface */
int init_interface();

/*  close the interface */
int close_interface();

/* = Game printings ======================================================== */

/*  print game board */
int print_board(board *b);

/*  print the score */
int print_score(int score);

/*  print all the possible moves */
int print_moves(char** moves, int moves_number);

/*  print the winner's name */
int print_winner(char winner);


/* = Informations printings ================================================ */

/*  print an error */
int print_error(char* error_str);

/*  print a notice */
int print_notice(char* notice_str);

/* = Inputs ================================================================ */

/*  get a command */
int read_command(char** command);

#endif /* _INTERFACE_H */
