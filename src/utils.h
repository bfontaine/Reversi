#ifndef _UTILS_H
#define _UTILS_H 1

/* == Game Constants ======================================================= */

#define MIN_SQ 0
#define MAX_SQ 7
#define FIRST_LETTER 'A'
#define FIRST_DIGIT  '1'

#define EMPTY 0
#define EMPTY_C 'E'

#define WHITE 1
#define WHITE_C 'W'

#define BLACK 2
#define BLACK_C 'B'

#define OTHER_C(P) ((P==WHITE_C)?BLACK_C:WHITE_C)

#define TIE_C 'T'

/* == Errors =============================================================== */

// Board-related errors : [BO]ARD -> [80] 
#define OUTSIDE -801
#define NOT_A_SQUARE -802

// Pointer-related errors : [PO]INTER -> [20]
#define BAD_POINTER -201

#endif // _UTILS_H
