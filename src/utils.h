#ifndef _UTILS_H
#define _UTILS_H 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* == Configuration options ================================================ */

/* print A-H and 1-8 on the sides of the board */
#define BOARD_PRETTY_PRINT 1

/* use colors */
#define BOARD_COLORS 1

/* print a character for empty squares */
#define BOARD_PRINT_EMPTY 0

/* -- colored templates for squares ---------------------------------------- */

/* color for even squares */
#define BOARD_COLOR_1 "\e[42m %c\e[0m"
/* color for odd squares */
#define BOARD_COLOR_2 "\e[43m %c\e[0m"
/* color for black player */
#define BOARD_COLOR_B "\e[1;37m\e[40m %c\e[0m"
/* color for white player */
#define BOARD_COLOR_W "\e[1;30m\e[47m %c\e[0m"

/* == Game Constants ======================================================= */

#define MIN_SQ 0
#define MAX_SQ 7
#define FIRST_LETTER 'A'
#define FIRST_DIGIT  '1'

#define EMPTY 0
#define EMPTY_C '.'

#define WHITE 1
#define WHITE_C 'W'
#define FRENCH_WHITE_C 'B'

#define BLACK 2
#define BLACK_C 'B'
#define FRENCH_BLACK_C 'N'

#define TIE_C 'T'

#define WHITE_NAME "WHITE"
#define BLACK_NAME "BLACK"

#define FIRST_PLAYER BLACK_C

#define CAN_PLAY_UPLEFT 1
#define CAN_PLAY_UP 2
#define CAN_PLAY_UPRIGHT 4
#define CAN_PLAY_LEFT 8
#define CAN_PLAY_RIGHT 16
#define CAN_PLAY_DOWNLEFT 32
#define CAN_PLAY_DOWN 64
#define CAN_PLAY_DOWNRIGHT 128

#define CMD_MAX_SIZE 100

/* == Errors =============================================================== */

/* Board-related errors : [B]OARD -> [8] */
#define OUTSIDE -81
#define NOT_A_SQUARE -82
#define NOT_EMPTY -83

/*  Game-related errors: [G]ame -> [6] */
#define CANNOT_PLAY_HERE -61

/*  Pointer-related errors : [P]OINTER -> [2] */
#define BAD_POINTER -21

/* == Macros =============================================================== */

#define SWITCH_PLAYER(PL) PL=(((PL)==BLACK_C)?WHITE_C:BLACK_C)

#endif /* _UTILS_H */
