#ifndef _MAIN_C
#define _MAIN_C 1

#include "main.h"

int main(int argc, char** argv) {
    
    if (argc <= 1) {
        puts("Use --play to play.");
        return 0;
    }

    if (!strcmp(argv[1], "--play")) {
        while (launch_game() == PLAY_AGAIN);
    }

    return 0;
}

int launch_game() {

    int i = 0,
        white_score = 0,
        pass = 0,
        executed = 0,
        parsing_result = 0,
        move_result = 0,
        moves_nb = 0,
        other_p_moves_nb = 0,
        return_value = 0;

    board* b = (board*)malloc(sizeof(board));
    char *cmd = malloc(sizeof(char)*(CMD_MAX_SIZE+1)),
         *sq_name = malloc(sizeof(char)*3),
         **moves = malloc(sizeof(char*)*SQS_NB);

    char current_player = FIRST_PLAYER,
         player = '\0';
    
    init_board(b);

    init_interface();

    while (1) {
        pass = 0;
        executed = 0;
        moves_nb = -1;
        read_command(&cmd);

        parsing_result = parse_cmd(b, cmd, &player, &sq_name, &pass, &executed);

        if (parsing_result < 0) {
            
            print_error("Commande non reconnue.");
            continue;

        }

        /* compute possible moves */
        moves_nb = get_possible_moves(b, current_player, &moves);

        if (moves_nb == 0) {
            other_p_moves_nb
                = get_possible_moves(b, OTHER_PLAYER(current_player), NULL);

            if (other_p_moves_nb == 0) {
                /* nobody can play */

                white_score = get_score(b, WHITE_C);

                if (white_score > SQS_NB/2) {
                    print_winner(WHITE_C);
                } else if (white_score == SQS_NB/2) {
                    print_winner(TIE_C);
                } else {
                    print_winner(BLACK_C);
                }
                break;
            }
        }

        if (pass) {
            if (moves_nb > 0) {
                printf("ERREUR il est possible de jouer en %s\n", moves[i]);
                continue;
            } else {
                puts("OK");
                SWITCH_PLAYER(current_player);
                continue;
            }
        }
        
        if (parsing_result == PLAY_AGAIN) {
            
            puts("OK");
            return_value = PLAY_AGAIN;
            break;
        
        } else if (parsing_result == SHOW_MOVES) {

            print_moves(moves, moves_nb);
            continue;
        }

        if (executed) {
            /* command already executed -> do nothing */
            continue;
        }

        move_result = play(b, current_player, sq_name);

        if (move_result == CANNOT_PLAY_HERE) {
            print_error("Impossible de jouer ici.");
            continue;
        }
        if (move_result == NOT_EMPTY) {
            print_error("Impossible de jouer ici, la case est déjà  occupée.");
            continue;
        }
        if (move_result == OUTSIDE) {
            print_error("La case est en dehors du plateau.");
            continue;
        }
        if (move_result == NOT_A_SQUARE) {
            print_error("Nom de case non reconnu.");
            continue;
        }

        SWITCH_PLAYER(current_player);
        puts("OK");
    }

    close_interface();
    free(cmd);
    free(sq_name);
    free(b);

    for (i=0; i<SQS_NB; i++) {
        free(moves[i]);
    }
    free(moves);

    return return_value;
}

int parse_cmd(board* b, char *command, char *player,
                char **sq_name, int *pass, int *executed) {

    if (!strcmp(command, "score")) {
        /*  print score */
        *executed = 1;
        return print_score(get_score(b, '\0'));
    }

    if (!strcmp(command, "newgame")) {
        /*  new game */
        *executed = 1;
        return PLAY_AGAIN;
    }

    if (!strcmp(command, "coups")) {
        /*  print possible moves */
        *executed = 1;
        return SHOW_MOVES;
    }

    if (!strcmp(command, "affiche")) {
        /*  print board */
        *executed = 1;
        return print_board(b);
    }

    if (
               (strlen(command) != 3)
         /*  || ((command[0] != WHITE_C) && (command[0] != BLACK_C)) */
            || ((command[0] != 'B') && (command[0] != 'N'))
            || ((command[1] == 'P') && (command[2] != 'A'))
            || ((command[1] < FIRST_LETTER) && (command[1] > FIRST_LETTER+MAX_SQ))
            || ((command[2] < FIRST_DIGIT) && (command[2] > FIRST_DIGIT+MAX_SQ))
        ){
        /*  bad command */
        *executed = 1;
        return print_error("Commande invalide.");
    }

    *executed = 0;
    /* *player = command[0]; */
    *player = (command[0] == 'B') ? WHITE_C : BLACK_C;

    if (command[1] == 'P') {
        /*  pass turn */
        *pass = 1;
        return 0;
    }

    (*sq_name)[0] = command[1];
    (*sq_name)[1] = command[2];
    (*sq_name)[2] = '\0';

    return 0;
}

#endif /* _MAIN_C */
