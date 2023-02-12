// #include <cstdio>
#include "mysok.h"
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

// creation liste des positions impossibles
vector<Position> get_impossible_positions(int **board) {
  vector<Position> forbid_pos;

  return forbid_pos;
}

// pour une case (pos) regarde si il y a 2 murs adjacent et qu'il n'y pas de
// point final
bool check_corner(char *Table, Position pos) { return true; }
// regarde il y as un mur complet entre 2 positions interdite et qu'il n'y a pas
// de point final
bool check_wall_line(Position pos1, Position pos2, char *Table) { return true; }

int main(int _ac, char **_av) {
  if (_ac != 2) {
    printf("usage: %s SOK_FILE\n", _av[0]);
    return 0;
  }
  sok_board_t S;
  S.load(_av[1]);
  S.print_board();
  vector<string> list_moves = {"right", "down", "down"};
  S.move(list_moves);
  if (S.verife_win())
    printf("win\n");
  return 0;
}
