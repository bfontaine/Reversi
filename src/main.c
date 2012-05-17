#include "main.h"

#ifndef _MAIN_C
#define _MAIN_C 1

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
        pass = 0,
        executed = 0,
        parsing_result = 0,
        move_result = 0,
        moves_nb = 0;
    const int sqs_nb = (MAX_SQ-MIN_SQ+1)*(MAX_SQ-MIN_SQ+1);

    board* b = (board*)malloc(sizeof(board));
    char *cmd = malloc(sizeof(char)*(CMD_MAX_SIZE+1)),
         *sq_name = malloc(sizeof(char)*3),
         **moves = malloc(sizeof(char*)*sqs_nb);

    char current_player = FIRST_PLAYER,
         player = '\0';
    
    init_board(b);

    init_interface();

    while (1) {
        pass = 0;
        executed = 0;
        read_command(&cmd);

        parsing_result = parse_cmd(b, cmd, &player, &sq_name, &pass, &executed);

        if (parsing_result < 0) {
            
            print_error("Commande non reconnue.");
            continue;

        } else if (parsing_result == PLAY_AGAIN) {
            
            puts("OK");
            return PLAY_AGAIN;
        
        } else if (parsing_result == SHOW_MOVES) {

            printf("COUPS");
            for (i=0; i<moves_nb; i++) {
                printf(" %s", moves[i]);
            }
            puts("");
            continue;
        }

        if ((parsing_result == SHOW_MOVES) || pass) {
            /* compute possible moves */
            moves_nb = get_possible_moves(b, player, &moves);
        }

        if (executed) {
            /* command already executed -> do nothing */
            continue;

        } else {

            if (current_player != player) {
                if (current_player == BLACK_C) {
                    print_error("C'est à Noir de jouer.");
                } else {
                    print_error("C'est à Blanc de jouer.");
                }
                continue;
            }
            
            if (pass) {
                pass = 0;
                if (moves_nb) {
                    printf("ERREUR Le joueur peut jouer en %s\n", moves[0]);
                } else {
                    SWITCH_PLAYER(current_player);
                    puts("OK");
                }
                continue;
            }

            move_result = play(b, current_player, sq_name);

            if (move_result == CANNOT_PLAY_HERE) {
                print_error("Impossible de jouer ici.");
                continue;
            }
            if (move_result == NOT_EMPTY) {
                print_error("Impossible de jouer ici, la case est déjà occupée.");
                continue;
            }
        }

        SWITCH_PLAYER(current_player);
        puts("OK");
    }

    close_interface();
    free(cmd);
    free(sq_name);
    free(b);

    for (i=0; i<sqs_nb; i++) {
        free(moves[i]);
    }
    free(moves);

    return 0;
}

char* read_cmd() {

    char *cmd = (char*)malloc(sizeof(char)*(CMD_MAX_SIZE+1));
    char c = fgetc(stdin);    

    int len = CMD_MAX_SIZE;

    while ((c != EOF) && (len-- != 0) && (c != '\n')) {
        *cmd++ = c;
        c = fgetc(stdin);
    }
    
    while (fgetc(stdin) != EOF); /* flush buffer */

    return cmd;
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
