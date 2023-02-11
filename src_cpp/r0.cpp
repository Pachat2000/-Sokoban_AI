//#include <cstdio>
#include "mysok.h"
#include <cstdlib>
#include <string.h>
#include <string>

using namespace std;

// creation liste des positions impossibles
vector<Position> get_impossible_positions(sok_board_t S) {
  vector<Position> forbid_pos;
  bool begin_check = false;
  Position pos;
  for (int i = 0; i < NBL; i++) {
    for (int j = 0; j < NBC; j++) {
      if (S.board[i][j] == WALL)
        begin_check = true;
      if (begin_check) {

        if (S.board[i][j] == FREE) {
          pos.x = i;
          pos.y = j;
          if (check_corner(S, pos))
            forbid_pos.push_back(pos);
        }
      }
    }
    begin_check = false;
  }
  Position p = {40,40};
  forbid_pos.push_back(p);
  int vec_size = forbid_pos.size();
  vector<Position> other_forb_pos;

  for (int i = 0; i < vec_size - 1; i++) {
    for (int j = i + 1; j < vec_size; j++) {
      other_forb_pos = check_wall_line(forbid_pos.at(i), forbid_pos.at(j), S);
      for (auto k : other_forb_pos) {
        forbid_pos.push_back(k);
      }
    }
  }

  return forbid_pos;
}

// pour une case (pos) regarde si il y a 2 murs adjacent et qu'il n'y pas de
// point final
bool check_corner(sok_board_t S, Position pos) {
  if (S.board[pos.x - 1][pos.y] == WALL && S.board[pos.x][pos.y + 1] == WALL) {
    return true;
  } else if (S.board[pos.x][pos.y + 1] == WALL &&
             S.board[pos.x + 1][pos.y] == WALL) {
    return true;
  } else if (S.board[pos.x + 1][pos.y] == WALL &&
             S.board[pos.x][pos.y - 1] == WALL) {
    return true;
  } else if (S.board[pos.x][pos.y - 1] == WALL &&
             S.board[pos.x - 1][pos.y] == WALL) {
    return true;
  }
  return false;
}

// regarde s'il y a un mur complet entre 2 positions interdites et qu'il n'y a
// pas de point final

vector<Position> check_wall_line(Position pos1, Position pos2, sok_board_t S) {
  vector<Position> vec_pos;
  vector<Position> vide{};
  Position pos;
  bool wall1 = true;
  bool wall2 = true;

  if (pos1.x == pos2.x) {
    for (int i = pos1.y + 1; i < pos2.y; i++) {
      pos.x = pos1.x;
      pos.y = i;
      vec_pos.push_back(pos);

      if (S.board[pos.x][pos.y] == TARGET)
        return vide;
      if (S.board[pos.x - 1][pos.y] != WALL)
        wall1 = false;
      if (S.board[pos.x + 1][pos.y] != WALL)
        wall2 = false;
    }
    if (wall1 || wall2) {
      return vec_pos;
    } else {
      return vide;
    }
  } else if (pos1.y == pos2.y) {
    for (int i = pos1.x + 1; i < pos2.x; i++) {
      pos.x = i;
      pos.y = pos1.y;
      vec_pos.push_back(pos);

      if (S.board[pos.x][pos.y] == TARGET)
        return vide;
      if (S.board[pos.x][pos.y - 1] != WALL)
        wall1 = false;
      if (S.board[pos.x][pos.y + 1] != WALL)
        wall2 = false;
    }
    if (wall1 || wall2) {
      return vec_pos;
    } else {
      return vide;
    }
  } else {
    return vide;
  }
}

  int main(int _ac, char **_av) {
    if (_ac != 2) {
      printf("usage: %s SOK_FILE\n", _av[0]);
      return 0;
    }

    sok_board_t S;
    S.load(_av[1]);
    S.print_board();
    vector<Position> vector_forbid_pos = get_impossible_positions(S);
    for (auto i : vector_forbid_pos) {
      printf("[x: %d, y: %d]\n", i.x, i.y);
    }

    if (S.verife_win())
      printf("win\n");
    return 0;
  }
