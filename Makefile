# LC4 project 2011/2012
# by Baptiste Fontaine
# v0.1

CC=gcc

SRC=src/
SRC_TESTS=tests/

OPT=-Wall -I $(SRC)
OPT_TESTS=-Wall -I $(SRC_TESTS)

default : game

# othello == reversi

game : othello

# tests
run-tests :
	./run_tests.sh

# cleaning

clean :
	find . -name *~ -delete
	find . -name *.o -delete
	find . -name a.out -delete
