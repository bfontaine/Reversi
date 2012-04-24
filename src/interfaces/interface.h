#include "utils.h"

#ifndef _INTERFACE_H
#define _INTERFACE_H 1

// initialize the interface
int init_interface();

// print game board
int print_board(board *b);

// get a move
int get_move(char* move);

#endif // _INTERFACE_H
