# LC4 project 2011/2012
# by Baptiste Fontaine
# v0.1

CC=gcc

SRC=src
SRC_TESTS=tests
GAME_SRC=${SRC}/game
INTERFACE_SRC=${SRC}/interfaces
AI_SRC=${SRC}/ai

# Add -g below for debugging
BASIC_OPT= -std=c89 -Wall -Wextra -Wundef -Werror
OPT=${BASIC_OPT} -I $(SRC)
OPT_TESTS=${BASIC_OPT} -I $(SRC_TESTS)

OBJS_NO_MAIN=board.o game.o text.o ai.o 
OBJS=${OBJS_NO_MAIN} main.o

# @: force default to do not try to make default.o using the last target
default : othello
	@

# othello = reversi

othello: ${OBJS}
	${CC} ${OPT} $^ -o $@

othello_white_ai: ${OBJS_NO_MAIN} main_white_ai.o
	${CC} ${OPT} $^ -o $@

othello_black_ai: ${OBJS_NO_MAIN} main_black_ai.o
	${CC} ${OPT} $^ -o $@

othello_debug: ${OBJS}
	${CC} ${OPT} $^ -o $@

# tests
run-tests :
	./run_tests.sh

# cleaning

clean :
	rm -f *~
	rm -f */*~
	rm -f */*/*~
	rm -f ${OBJS}
	rm -f a.out
	rm -f .tests.tmp
	@# alternatives:
	@#find . -name *~ -delete
	@#find . -name *.o -delete
	@#find . -name a.out -delete

cleanall : clean
	rm -f othello

board.o : ${GAME_SRC}/board.c ${GAME_SRC}/board.h ${SRC}/utils.h
game.o : ${GAME_SRC}/game.c ${GAME_SRC}/game.h ${SRC}/utils.h
text.o : ${INTERFACE_SRC}/text.c ${INTERFACE_SRC}/interface.h ${SRC}/utils.h
ai.o : ${AI_SRC}/ai.c ${AI_SRC}/ai.h
main.o : ${SRC}/main.c ${SRC}/main.h

main_white_ai.o : ${SRC}/main.c ${SRC}/main.h
	${CC} ${OPT} -DWHITE_AI=1 -c $< -o $@

main_black_ai.o : ${SRC}/main.c ${SRC}/main.h
	${CC} ${OPT} -DBLACK_AI=1 -c $< -o $@

%.o :
	${CC} ${OPT} -c $< -o $@
