#ifndef _AI_C
#define _AI_C 1

#include "ai.h"

future_move* create_future_move(int col, int row) {

    future_move *fm = (future_move*)malloc(sizeof(future_move)); /* FIXME */

    fm->col = col;
    fm->row = row;
    fm->points = 0;
    fm->weight = 0;
    fm->moves = (future_move**)malloc(sizeof(future_move*)*MAX_POSSIBLE_MOVES);
    fm->moves_len = 0;

    return fm;
}

int compute_moves(future_move* self, board* b, char player, int deep) {
    if (deep < 1) {
        return 0;
    }

    if (self->points != 0) {
        /* if AI does not pass the turn */
        put_piece_by_colrow(b, self->col, self->row, player);
    }

    char **moves_c = (char**)malloc(sizeof(char*)*MAX_POSSIBLE_MOVES);
    
    int i, moves_c_len = 0,
        col = -1,
        row = -1;
    
    board* b2 = NULL;
    future_move* fm = NULL;

    moves_c_len = get_possible_moves(b, player, &moves_c);

    if (moves_c_len == 0) {
            fm = create_future_move(-1,-1);
            ADD_FUTURE_MOVE(self, fm);
    } else {
        for (i=0; i<moves_c_len; i++) {
            convert_square(moves_c[i], &col, &row);

            /* create a future move with good points/weight and col/row */
            fm = create_future_move(col, row);
            fm->points = play(b, player, moves_c[i]);
            put_piece(b, moves_c[i], EMPTY_C); 
            fm->weight = M_WEIGHT(*fm);

            ADD_FUTURE_MOVE(self, fm);
        }
    }

    for (i=0; i<(self->moves_len); i++) {
        b2 = board_cp(b);

        /* TODO if it's other player's turn, replace '+=' with '-=' */
        self->weight
            += compute_moves((self->moves)[i],
                             b2,
                             OTHER_PLAYER(player),
                             deep-1);
        /* FIXME segfault après l'appel à la ligne précédente */

        free(b2);
        b2 = NULL;
    }

    for (i=0; i<moves_c_len; i++) {
        if (moves_c[i] != NULL) {
            free(moves_c[i]);
        }
    }
    free(moves_c);
    
    return self->weight;
}

ai* create_ai(board* b, char player_c) {
    
    board* b2 = board_cp(b);
    ai* a = (ai*)malloc(sizeof(ai));

    future_move *fm = create_future_move(-1,-1);

    a->moves = (future_move**)malloc(sizeof(future_move*)*MAX_POSSIBLE_MOVES);
    a->moves_len = 0;
    a->b = b2;
    a->player_c = player_c;
    a->current_player_c = FIRST_PLAYER;

    compute_moves(fm, b, player_c, MAX_DEEP);

    a->moves = fm->moves;
    a->moves_len = fm->moves_len;

    free(fm);

    return a;
}

int ai_play_best_move(ai* self, char** sq) {

    if (self->moves_len == 0) {
        *sq = "PA";
        return ai_play(self, -1, -1);
    }

    int i,
        max_weight = (self->moves)[0]->weight;

    future_move* best_move = NULL;

    for (i=1; i<(self->moves_len); i++) {
        if ((self->moves)[i]->weight > max_weight) {
            max_weight = (self->moves)[i]->weight;
            best_move = (self->moves)[i];
        }
    }

    (*sq)[0] = FIRST_LETTER + best_move->col;
    (*sq)[1] = FIRST_DIGIT + best_move->row;
    (*sq)[2] = '\n';

    return ai_play(self, best_move->col, best_move->row);
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

    SWITCH_PLAYER(self->current_player_c);

    return put_piece_by_colrow(self->b, col, row, self->current_player_c);
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

    char *sq = (char*)malloc(sizeof(char)*3),
         name = (self->player_c == BLACK_C) ? 'N' : 'B';

    ai_play_best_move(self, &sq);

    (*cmd)[0] = name;
    (*cmd)[1] = sq[0];
    (*cmd)[2] = sq[1];
    (*cmd)[3] = '\0';

#if VERBOSE_AI
    printf("AI: My command is \"%s\".\n", *cmd);
#endif

    return 0;
}

#endif /* _AI_C */
