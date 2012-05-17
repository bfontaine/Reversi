Reversi
=======

This is a Reversi game for the C class.

Usage
-----

Compiling: `make`
Playing: `./othello --play`

Use these commands to play:
- `affiche` : print the board
- `coups` : print possible moves
- `newgame` : new game
- `score` : print the current player's score

To make a move, the command has 3 chars: The first is the name of the current
player (B for White (*Blanc* in French), and N for Black (*Noir* in French)).
The next to chars are `PA` if the player wants to pass his turn, or a square
name (e.g. `B6`, `H2`). For example, if the current player is White and wants to
play in C3, type:
    
    BC3

The program responds with "OK" if the move is ok, "ERREUR …" if there is an
error.
