###2048

This is meant to be a playground for working with 2048 (or variants), a tile
based puzzle.

###The rules

* The board (typically 4x4) is initialized empty except for one random cell.
* All random cells are given value 2 (with p=0.9) or 4.
* Players can move all cells Left, Right, Up, or Down.
* A move results in a row or column collapse; nonzero cells are pushed in the
  direction of the move, cells with the same value are merged beginning from
  the direction of the move. If the cell configuration is changed, a random
  cell is placed with uniform probability over the empty cells.
* When two cells are merged, the score is incremented by the resulting value.
* The game is over when 2048 is reached or when no remaining moves exist.

###The code

`game.h/cpp` provides the game object (Tiles). The user can then request the
cell configuration, score, move, ...

###To run

> $ make    
> $ ./run  
