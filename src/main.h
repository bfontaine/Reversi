#ifndef _MAIN_H
#define _MAIN_H 1

#include "utils.h"
#include "game/board.h"
#include "game/game.h"
#include "ai/ai.h"

#include "interfaces/interface.h"

#define PLAY_AGAIN 2
#define SHOW_MOVES 4

#define HELP_STR "Use --play to play."

/*  start a new game
     ia_player should be '\0' without AI, BLACK_C if the AI is black, or
     WHITE_C if the AI is white.
 */
int launch_game(char ai_player);

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
