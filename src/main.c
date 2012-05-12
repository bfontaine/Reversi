#include "main.h"

int main(int argc, char** argv) {
    
    if (argc == 0) {
        puts("Use --play to play.");
        return 0;
    }

    if (!strcmp(argv[0], "--play")) {
        while (launch_game() == PLAY_AGAIN);
    }

    return 0;
}

int launch_game() {

    board* b = (board*)malloc(sizeof(board));
    init_board(b);

    init_interface();


    close_interface();
    free(b);

    return 0;
}

int read_cmd(char **command) {

    return 0;
}

int parse_cmd(board* b, char *command, char *player,
                char **sq_name, int *pass, int *executed) {

    if (!strcmp(command, "score")) {
        *executed = 1;
        return print_score(get_score(b, '\0'));
    }

    if (!strcmp(command, "newgame")) {
        *executed = 1;
        return PLAY_AGAIN;
    }

    if (!strcmp(command, "coups")) {
        *executed = 1;
        //print_moves( … ) TODO
        return 0;
    }

    if (!strcmp(command, "affiche")) {
        *executed = 1;
        return print_board(b);
    }

    if (
               (strlen(command) != 3)
         // || ((command[0] != WHITE_C) && (command[0] != BLACK_C))
            || ((command[0] != 'B') && (command[0] != 'N'))
            || ((command[1] == 'P') && (command[2] != 'A'))
            || ((command[1] < FIRST_LETTER) && (command[1] > FIRST_LETTER+MAX_SQ))
            || ((command[2] < FIRST_DIGIT) && (command[2] > FIRST_DIGIT+MAX_SQ))
        ){
        *executed = 1;
        return print_error("Commande invalide.");
    }

    *executed = 0;
    //*player = command[0];
    *player = (command[0] == 'B') ? WHITE_C : BLACK_C;

    if (command[1] == 'P') {
        *pass = 1;
        return 0;
    }

    (*sq_name)[0] = command[1];
    (*sq_name)[1] = command[2];
    (*sq_name)[2] = '\0';

    return 0;
}