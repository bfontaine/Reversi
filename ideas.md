"Modules"
---------

Each module is a file with structs and functions related to something in
particular.

- `board` for the board-related structs and functions
- `player` for the players
- `interfaces/text` for the text interface
- `interfaces/ncurses` for the ncurses interface. All interface modules should
  provide the same functions, so we can switch easily between them.
- `[module name]_test` for each module's tests

Data structures
--------------

- For the board, use a `typedef struct {…} board`, with functions to map
  each square name (e.g. __D4__, __H7__) to an array position.
- Use a `short` array for the board, with `2` for the black player, and `1` for the
  white one. `0` should be an empty square.

Interface
---------

- Use an "INTERFACE" option to set the interface when compiling
- Use ncurses to draw the board, and to map keys (e.g. arrow keys to move on the
  game, spacebar to put a token on it, etc)

Interfaces: ncurses, text (reading STDIN, writing on STDOUT), text2 (text
improved, with  a ASCII-board).

Testing
-------

- for memory leaks, use
  [Valgrind](http://www.cprogramming.com/debugging/valgrind.html).

Architecture
------------

3 parts: __interface__ (view), __data__ (model), and __main__ (controller).
- interface : `src/interface/*`
- data : `src/board.*`
- controller : (soon…)

All interfaces use `src/interface/interface.h` functions.
The controller is just a `main` programm which use the model to update/respond
to the interface. The AI may be a specific interface, or a `main` program
which use another interface for the human player.
