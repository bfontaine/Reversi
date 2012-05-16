#ifndef _MAIN_H
#define _MAIN_H 1

#include "utils.h"
#include "game/board.c"
#include "game/game.c"

#ifndef INTERFACE
#define INTERFACE "interfaces/text.c"
#endif

#define PLAY_AGAIN 2
#define SHOW_MOVES 4

#include INTERFACE

/*  start a new game */
int launch_game();

/*  read a command */
char* read_cmd();

/*  parse the given 'command'
    'player' should be the name of the current player (WHITE_C or BLACK_C). it
    will be set to WHITE_C or BLACK_C if it's a pass/move
    set 'sq_name' to the square name if it's a move
    set 'pass' to 1 if it's a pass
    set 'executed' to 1 if the command has already been executed
    the returned value may be 0 or PLAY_AGAIN */
int parse_cmd(board *b, char *command, char *player,
                char **sq_name, int *pass, int *executed);

#endif /* _MAIN_H */
