/*
 * Tile game (originally for 4x4 grid, adding up to 2048).
 *
 * Random 2's and 4's are generated, with probability 0.9 and 0.1, resp.
 *
 */
#ifndef __TILES_GAME_H__
#define __TILES_GAME_H__

#include <vector>

namespace game {

const size_t SIZE_2048 = 4;

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};


struct Cell
{
  Cell () : val (0) {}
  size_t val;

  bool operator==(const Cell& rhs) {return val==rhs.val;}
  bool operator==(const size_t& rhs) {return val==rhs;}
};

typedef std::vector<Cell*> Line;

class Tiles
{
public:
  Tiles (size_t sz=SIZE_2048);
  ~Tiles ();

  void move (Direction d);

  const std::vector<Line>& rows () {return _rows;}
  const std::vector<Line>& cols () {return _cols;}

  size_t score () {return _score;}
  size_t max () {return _max;}
  bool done () {return _done;}

private:
  bool _done;
  size_t _score, _max;

  const size_t _size;
  std::vector<Cell*> _grid;
  std::vector<Line> _cols;
  std::vector<Line> _rows;

  template<class T>
  bool collapse (Line* l, T begin, T end);

  bool collapsable (Line *l);
  void check_status ();

  std::vector<Cell*> available ();
  void insert_random ();
};

} // game

#endif // __TILES_GAME_H__
