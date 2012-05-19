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

ai* create_ai(board* b, char player_c) {
    
    board* b2 = board_cp(b);

    ai* a = (ai*)malloc(sizeof(ai));

    a->moves = (future_move**)malloc(sizeof(future_move*)*MAX_POSSIBLE_MOVES);
    a->moves_len = 0;
    a->b = b2;
    a->player_c = player_c;

    /* TODO compute possible moves */

    return a;
}

int ai_play(ai* self, int col, int row) {

    int i,
        move_id = -1,
        moves_len = self->moves_len;
    future_move *move;

    for (i=0; i<moves_len; i++) {
        move = (self->moves)[i];

        if ((move->col == col) && (move->row == row)) {
            move_id = i;
            break;
        }
    }
    if (move_id < 0) {
        return CANNOT_PLAY_HERE;
    }

    /* delete all others possible moves */
    for (i=0; i<moves_len; i++) {
        if (move_id != i) {
            free_future_move((self->moves)[i]);
        }
    }

    /* put this move's future moves into current position */
    self->moves = move->moves;
    self->moves_len = move->moves_len;

    /* delete this move */
    move->moves = NULL;
    free_future_move(move);
    
    /* TODO */
    return 0;
}

int free_future_move(future_move* fm) {

    int i=0;

    for (; i<(fm->moves_len); i++) {
        free_future_move((fm->moves)[i]);
    }
    free(fm);
    fm = NULL;

    return 0;
}

int free_ai(ai* a) {

    int i=0;

    for (; i<(a->moves_len); i++) {
        free_future_move((a->moves)[i]);
    }
    free(a->b);
    free(a);
    a = NULL;

    return 0;
}

int read_ai_command(ai* self, char** cmd) {

#if VERBOSE_AI
    printf("AI: My command is \"%s\".\n", *cmd);
#endif

    puts("Not implemented.");

    /* TODO read_ai_command */
    return 0;
}

#endif /* _AI_C */
