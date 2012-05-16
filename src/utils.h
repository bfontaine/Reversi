#ifndef _UTILS_H
#define _UTILS_H 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* == Game Constants ======================================================= */

#define MIN_SQ 0
#define MAX_SQ 7
#define FIRST_LETTER 'A'
#define FIRST_DIGIT  '1'

#define EMPTY 0
#define EMPTY_C '.'

#define WHITE 1
#define WHITE_C 'W'

#define BLACK 2
#define BLACK_C 'B'

#define TIE_C 'T'

#define WHITE_NAME "WHITE"
#define BLACK_NAME "BLACK"

#define CAN_PLAY_UPLEFT 1
#define CAN_PLAY_UP 2
#define CAN_PLAY_UPRIGHT 4
#define CAN_PLAY_LEFT 8
#define CAN_PLAY_RIGHT 16
#define CAN_PLAY_DOWNLEFT 32
#define CAN_PLAY_DOWN 64
#define CAN_PLAY_DOWNRIGHT 128

/* == Errors =============================================================== */

/* Board-related errors : [B]OARD -> [8] */
#define OUTSIDE -81
#define NOT_A_SQUARE -82
#define NOT_EMPTY -83

/*  Game-related errors: [G]ame -> [6] */
#define CANNOT_PLAY_HERE -61

/*  Pointer-related errors : [P]OINTER -> [2] */
#define BAD_POINTER -21

#endif /* _UTILS_H */
