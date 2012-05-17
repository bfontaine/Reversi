#include "tests_base.h"
#include "../src/interfaces/text2.c"

int main(void) {

    /* init_interface */
    assert(init_interface() == 0);

    /* print_notice */
    assert(print_notice("Test starting…") == 0);

    /* print_error */
    assert(print_error("This is a test error.") == 0);

    /* print_score */
    assert(print_notice("T: Next lines should be 'SCORE 01',") == 0);
    assert(print_notice("T: 'SCORE -12', 'SCORE 00' and 'SCORE 64'.") == 0);
    assert(print_score(1) == 0);
    assert(print_score(-12) == 0);
    assert(print_score(0) == 0);
    assert(print_score(64) == 0);

    /* print_winner */
    assert(print_notice("T: Next lines should be 'BLACK won' and 'WHITE won'.") == 0);
    assert(print_winner(BLACK_C) == 0);
    assert(print_winner(WHITE_C) == 0);

    /* print_board */
    board* b = (board*)malloc(sizeof(board));
    assert(init_board(b) == 0);

    assert(print_notice("T: Next 8 lignes should be an initialized Reversi board.") == 0);
    print_board(b);

    /* print_moves */
    char* moves[] = {"A1", "B5", "C4", "D3", "E2", "F6", "G8", "H7"};
    assert(print_notice("T: Next line should be 8 different couples letter-digit.") == 0);
    assert(print_moves(moves, 8) == 0);
    assert(print_notice("T: Next line should be only 1 couple letter-digit.") == 0);
    assert(print_moves(moves, 1) == 0);

    /* read_command */
    char *command = (char*)strdup("       ");
    assert(print_notice("T: please enter 'foo' below.") == 0);
    assert(read_command(&command) == 0);
    assert(strcmp(command, "foo") == 0);

    assert(print_notice("T: please enter 'bar' below.") == 0);
    assert(read_command(&command) == 0);
    assert(strcmp(command, "bar") == 0);

    /* close_interface */
    assert(close_interface() == 0);

    free(command);
    free(b);
    return 0;
}
