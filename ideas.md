Data structures
--------------

- For the game, use a `typedef struct {…} reversi_game`, with functions to map
  each square name (e.g. __D4__, __H7__) to an array position.
- Use a short array for the game, with `2` for the black player, and `1` for the
  white one. `0` should be an empty square.

Interface
---------

- Use ncurses to draw the game, and to map keys (e.g. arrow keys to move on the
  game, spacebar to put a token on it, etc)
