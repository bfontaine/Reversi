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

Testing
-------

- for memory leaks, use
  [Valgrind](http://www.cprogramming.com/debugging/valgrind.html).
