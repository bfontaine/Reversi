#ifndef _AI_C
#define _AI_C 1

#include "ai.h"

future_move* create_future_move(int col, int row) {

    future_move *fm = (future_move*)malloc(sizeof(future_move));

    fm->col = col;
    fm->row = row;
    fm->points = 0;
    fm->moves = (future_move**)malloc(sizeof(future_move*)*MAX_POSSIBLE_MOVES);
    fm->moves_len = 0;

    return fm;
}

position* create_position(board* b) {

    position* p = (position*)malloc(sizeof(position));

    p->b = b;
    p->moves = (future_move**)malloc(sizeof(future_move*)*MAX_POSSIBLE_MOVES);
    p->moves_len = 0;

    /* TODO compute future moves */

    return p;
}

ai* create_ai(board* b, char player_c) {
    
    board* b2 = board_cp(b);

    ai* a = (ai*)malloc(sizeof(ai));

    a->pos = create_position(b2);
    a->player_c = player_c;

    return a;
}

int play(ai*, int col, int row);

int free_future_move(future_move* fm) {

    int i=0;

    for (; i<(fm->moves_len); i++) {
        free_future_move((fm->moves)[i]);
    }
    free(fm);
    fm = NULL;

    return 0;
}

int free_position(position* p) {

    int i=0;

    for (; i<(p->moves_len); i++) {
        free_future_move((p->moves)[i]);
    }
    free(p->b);
    free(p);
    p = NULL;

    return 0;
}

int free_ai(ai* a) {
    free_position(a->pos);
    free(a);
    a = NULL;

    return 0;
}

int read_ai_command(ai* self, char** cmd) {

    puts("Not implemented.");

    /* TODO read_ai_command */
    return 0;
}

#endif /* _AI_C */
