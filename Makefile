# LC4 project 2011/2012
# by Baptiste Fontaine
# v0.1

CC=gcc

SRC=src
SRC_TESTS=tests
GAME_SRC=${SRC}/game
INTERFACE_SRC=${SRC}/interfaces

OPT=-Wall -I $(SRC) -std=c89
OPT_TESTS=-Wall -I $(SRC_TESTS)

default : othello

# othello = reversi

othello : main

main : main.o board.o game.o text.o
	${CC} ${OPT} $^ -o $@

# tests
run-tests :
	./run_tests.sh

# cleaning

clean :
	rm -f *~
	rm -f */*~
	rm -f */*/*~
	rm -f *.o
	rm -f a.out
#find . -name *~ -delete
#find . -name *.o -delete
#find . -name a.out -delete

board.o : ${GAME_SRC}/board.c ${GAME_SRC}/board.h
	${CC} ${OPT} -c $< -o $@

game.o : ${GAME_SRC}/game.c ${GAME_SRC}/game.h
	${CC} ${OPT} -c $< -o $@

text.o : ${INTERFACE_SRC}/text.c ${INTERFACE_SRC}/interface.h
	${CC} ${OPT} -c $< -o $@

%.o : ${SRC}/%.c
	${CC} ${OPT} -c $< -o $@
