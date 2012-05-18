# LC4 project 2011/2012
# by Baptiste Fontaine
# v0.1

CC=gcc

SRC=src
SRC_TESTS=tests
GAME_SRC=${SRC}/game
INTERFACE_SRC=${SRC}/interfaces

OPT=-Wall -I $(SRC) -std=c89
OPT_TESTS=-Wall -I $(SRC_TESTS) -std=c89

OBJS=board.o game.o text.o main.o

default : othello

# othello = reversi

othello: ${OBJS}
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
	rm -f .tests.tmp
#find . -name *~ -delete
#find . -name *.o -delete
#find . -name a.out -delete

board.o : ${GAME_SRC}/board.c ${GAME_SRC}/board.h ${SRC}/utils.h
	${CC} ${OPT} -c $< -o $@

game.o : ${GAME_SRC}/game.c ${GAME_SRC}/game.h ${SRC}/utils.h
	${CC} ${OPT} -c $< -o $@

text.o : ${INTERFACE_SRC}/text.c ${INTERFACE_SRC}/interface.h ${SRC}/utils.h
	${CC} ${OPT} -c $< -o $@

%.o : ${SRC}/%.c ${SRC}/%.h
	${CC} ${OPT} -c $< -o $@
