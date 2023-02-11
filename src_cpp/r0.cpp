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

/*   for (int i = 0; i < forbid_pos.size()-1; i++) {
    for (int j = i + 1; j < forbid_pos.size(); j++) {
      vector<Position> other_forb_pos =
          check_wall_line(forbid_pos.at(i), forbid_pos.at(j), S);
      for (auto k : other_forb_pos) {
        forbid_pos.push_back(k);
      }
    }
  } */
  return forbid_pos;
}

// pour une case (pos) regarde si il y a 2 murs adjacent et qu'il n'y pas de
// point final
bool check_corner(sok_board_t S, Position pos) {
  if (S.board[pos.x][pos.y - 1] == WALL && S.board[pos.x + 1][pos.y] == WALL) {
    return true;
  } else if (S.board[pos.x + 1][pos.y] == WALL &&
             S.board[pos.x + 1][pos.y + 1] == WALL) {
    return true;
  } else if (S.board[pos.x][pos.y + 1] == WALL &&
             S.board[pos.x - 1][pos.y] == WALL) {
    return true;
  } else if (S.board[pos.x - 1][pos.y] == WALL &&
             S.board[pos.x][pos.y - 1] == WALL) {
    return true;
  } else {
    return false;
  }
}
// regarde s'il y a un mur complet entre 2 positions interdites et qu'il n'y a
// pas de point final
vector<Position> check_wall_line(Position pos1, Position pos2, sok_board_t S) {
  int diff_pos;
  bool case_x; // true == x | false == y
  vector<Position> forbid_pos1;
  vector<Position> forbid_pos2;
  vector<Position> vide;
  Position pos;

  if (pos1.x == pos2.x) {
    diff_pos = pos1.x - pos2.x;
    case_x = true;
  } else if (pos1.y != pos2.y) {
    diff_pos = pos1.y - pos2.y;
    case_x = true;
  } else {
    return vide;
  }

  bool wall1 = true;
  bool wall2 = true;

  if (case_x) {
    if (diff_pos < 0) {

      wall1 = true;
      wall2 = true;
      for (int i = pos1.x; i < pos2.x; i++) {
        if (S.board[i][pos1.y] == TARGET) {
          return vide;
        }

        if (S.board[i - 1][pos1.y] != WALL) {
          wall1 = false;
        } else {
          pos.x = i;
          pos.y = pos1.y;
          forbid_pos1.push_back(pos);
        }

        if (S.board[i + 1][pos1.y] != WALL) {
          wall2 = false;
        } else {
          pos.x = i;
          pos.y = pos1.y;
          forbid_pos2.push_back(pos);
        }
      }
      if (wall1) {
        return forbid_pos1;
      }
      if (wall2) {
        return forbid_pos2;
      }
    } else {
      wall1 = true;
      wall2 = true;
      for (int i = pos1.x; i > pos2.x; i--) {
        if (S.board[i][pos1.y] == TARGET) {
          return vide;
        }
        if (S.board[i - 1][pos1.y] != WALL) {
          wall1 = false;
        } else {
          pos.x = i;
          pos.y = pos1.y;
          forbid_pos1.push_back(pos);
        }
        if (S.board[i + 1][pos1.y] != WALL) {
          wall2 = false;
        } else {
          pos.x = i;
          pos.y = pos1.y;
          forbid_pos2.push_back(pos);
        }
      }
      if (wall1) {
        return forbid_pos1;
      }
      if (wall2) {
        return forbid_pos2;
      }
    }
  } else {

    if (diff_pos < 0) {
      wall1 = true;
      wall2 = true;
      for (int i = pos1.y; i < pos2.y; i++) {
        if (S.board[pos1.x][i] == TARGET) {
          return vide;
        }
        if (S.board[pos1.x][i - 1] != WALL) {
          wall1 = false;
        } else {
          pos.x = pos1.x;
          pos.y = i;
          forbid_pos1.push_back(pos);
        }
        if (S.board[pos1.x][i + 1] != WALL) {
          wall2 = false;
        } else {
          pos.x = pos1.x;
          pos.y = i;
          forbid_pos2.push_back(pos);
        }
      }
      if (wall1) {
        return forbid_pos1;
      }
      if (wall2) {
        return forbid_pos2;
      }
    } else {
      wall1 = true;
      wall2 = true;
      for (int i = pos1.x; i > pos2.x; i--) {
        if (S.board[pos1.x][i] == TARGET) {
          return vide;
        }
        if (S.board[pos1.x][i - 1] != WALL) {
          wall1 = false;
        } else {
          pos.x = pos1.x;
          pos.y = i;
          forbid_pos1.push_back(pos);
        }
        if (S.board[pos1.x][i + 1] != WALL) {
          wall2 = false;
        } else {
          pos.x = pos1.x;
          pos.y = i;
          forbid_pos2.push_back(pos);
        }
      }
      if (wall1) {
        return forbid_pos1;
      }
      if (wall2) {
        return forbid_pos2;
      }
    }
  }
  return vide;
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
  for(auto i: vector_forbid_pos) {
    printf("[x: %d, y: %d]\n", i.x, i.y);
  }

  if (S.verife_win())
    printf("win\n");
  return 0;
}
