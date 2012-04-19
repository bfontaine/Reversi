# LC4 project 2011/2012
# by Baptiste Fontaine
# v0.1

CC=gcc

SRC=src/
SRC_TESTS=tests/

OPT=-Wall -I $(SRC)
OPT_TESTS=-Wall -I $(SRC_TESTS)

# othello == reversi
default : othello

game : othello

othello : othello.o
	$(CC) $(OPT) $< -o $@

# just an alias
reversi : othello.o
	$(CC) $(OPT) $< -o $@

othello.o : $(SRC)reversi.c $(SRC)reversi.h
	$(CC) $(OPT) -c $< -o $@


# tests
run-tests :
	./run_tests.sh

# cleaning

clean :
	rm -f ./*~
	rm -f ./*/*~
	rm -f ./*.o
	rm -f ./*/*.o
	rm -f ./a.out
	rm -f ./*/a.out
