#include <ncurses.h>
#include <iostream>

#include "game.h"

using namespace std;
using namespace game;

void print_board (Tiles *t)
{
    clear ();
    mvprintw (0, 0, "score: %d\n", t->score ());
    printw ("\n");

    const vector<Line> rows = t->rows ();
    for (auto& r : rows) {
        for (auto& c : r) {
            size_t v = c->val;
            if (v) printw ("%d\t", c->val);
            else printw (".\t");
        }
        printw ("\n");
    }
    printw ("\n");
    printw ("h-j-k-l : right-down-up-left\n");
    printw ("q       : quit\n");
}

int main (int argc, char *argv[])
{
    cout << "playing game..." << endl;

    initscr ();
    raw ();
    keypad (stdscr, TRUE);
    noecho ();

    srand (time (0));
    //srand (0);


    Tiles tgame;
    print_board (&tgame);

    char ch;
    bool quit = false;
    while (true) {
        ch = getch ();

        Direction d;
        switch (ch) {
            case 'h':
                d = LEFT;
                break;
            case 'j':
                d = DOWN;
                break;
            case 'k':
                d = UP;
                break;
            case 'l':
                d= RIGHT;
                break;
            case 'q':
            case 'Q':
                quit = true;
        }

        //Direction d = static_cast<Direction>(rand () % 4);
        tgame.move (d);
        print_board (&tgame);

        if (tgame.done ()) {
            mvprintw (0,0, "GAME OVER\n");
            break;
        }
        else if (quit) {
            clear ();
            mvprintw (0,0, "QUITTER\n\npress any key\n");
            break;
        }
    }

    refresh ();
    getch ();
    endwin ();

    return 0;
}
