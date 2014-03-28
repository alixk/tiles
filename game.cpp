#include <cstdlib>
#include <ctime>

#include "game.h"

using namespace std;

namespace game {

const double PROB_DRAW2 = 0.9;

Tiles::Tiles (size_t sz)
    : _done (false), _score (0), _max (0), _size (sz)
{
    // init board
    size_t n = _size*_size;
    _grid.reserve (n);
    for (size_t i=0;i<n;++i) 
        _grid.emplace_back (new Cell);

    // init row pointers
    for (size_t r=0;r<_size;++r) {
        Line row;
        for (size_t c=0;c<_size;++c)
            row.push_back (_grid[r*_size+c]);
        _rows.push_back (row);
    }

    // init col pointers
    for (size_t c=0;c<_size;++c) {
        Line col;
        for (size_t r=0;r<_size;++r)
            col.push_back (_grid[r*_size+c]);
        _cols.push_back (col);
    }

    // let's play
    insert_random ();
}

Tiles::~Tiles ()
{
    for (auto& c : _grid) delete c;
}

void Tiles::move (Direction d)
{
    if (_done) return;

    bool moved = false;
    switch (d) {
        case LEFT:
            for (auto& r : _rows) 
                moved |= collapse (&r, r.begin (), r.end ());
            break;
        case RIGHT:
            for (auto& r : _rows) 
                moved |= collapse (&r, r.rbegin (), r.rend ());
            break;
        case UP:
            for (auto& c : _cols) 
                moved |= collapse (&c, c.begin (), c.end ());
            break;
        case DOWN:
            for (auto& c : _cols) 
                moved |= collapse (&c, c.rbegin (), c.rend ());
            break;
    }

    if (moved) insert_random ();
    else check_status ();
}


template<class T>
bool Tiles::collapse (Line* l, T begin, T end)
{
    bool moved = false;
    auto lit = begin, rit = lit;
    while (lit != end) {
        while (rit != end && (*rit)->val==0) ++rit;
        if (rit == end) return moved;

        Cell *lhs = *lit, *rhs = *rit;
        if (lit == rit) {
            ++rit;
        }
        else if (*lhs == 0) {
            lhs->val = rhs->val;
            rhs->val = 0;
            moved = true;

            ++rit;
        }
        else if (*lhs == *rhs) {
            lhs->val += rhs->val;
            rhs->val = 0;
            _score +=  lhs->val;
            if (lhs->val > _max) _max = lhs->val;
            moved = true;

            ++lit;
            rit = lit;
        }
        else {
            ++lit;
        }
    }
    return moved;
}

vector<Cell*> Tiles::available ()
{
    vector<Cell*> cells;
    for (auto& r : _rows)
        for (auto& c : r)
            if (!c->val) cells.push_back (c);
    return cells;
}

bool Tiles::collapsable (Line *l)
{
    for (auto it=l->begin ();it!=--l->end ();++it) {
        Cell *lhs = *it, *rhs = *(it+1);
        if (*lhs == *rhs) return true;
        else if (*lhs == 0 || *rhs == 0) return true;
    }
    return false;
}

void Tiles::check_status ()
{
    for (auto& r : _rows)
        if (collapsable (&r)) return;
    for (auto& c : _cols)
        if (collapsable (&c)) return;
    _done = true;
}

void Tiles::insert_random ()
{
    vector<Cell*> cells = available ();
    if (cells.empty ()) return;

    Cell *c = cells[rand () % cells.size ()];

    double p = double (rand ())/double (RAND_MAX);
    c->val = (p < PROB_DRAW2) ? 2 : 4;
}

} // game
