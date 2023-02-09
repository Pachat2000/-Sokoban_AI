//#include <cstdio>
#include "mysok.h"
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

// creation liste des positions impossibles
vector<Position> get_impossible_positions(int **board) {
  vector<Position> forbid_pos;
  bool begin_check = false;
  Position pos;
  for (int i = 0; i < NBL; i++) {
    for (int j = 0; j < NBC; j++) {
      if (board[i][j] == WALL)
        begin_check = true;
      if (begin_check) {

        if (board[i][j] == FREE) {
          pos.x = i;
          pos.y = j;
          if (check_corner(board, pos))
            forbid_pos.push_back(pos);
        }
      }
    }
    begin_check = false;
  }


/*   for (int i = 0; i < forbid_pos.size(); i++) {
    for (int j = i + 1, j < forbid_pos.size(); i++) {
       if(check_wall_line(forbid_pos.at(i), forbid_pos.at(j), board)) {

       }
    }
  } */
  return forbid_pos;
}

// pour une case (pos) regarde si il y a 2 murs adjacent et qu'il n'y pas de
// point final
bool check_corner(int** Table, Position pos) { 
  if (Table[pos.x][pos.y-1] == WALL && Table[pos.x+1][pos.y] == WALL) {
    return true;
  } else if (Table[pos.x+1][pos.y] == WALL && Table[pos.x+1][pos.y+1] == WALL) {
    return true;
  } else if (Table[pos.x][pos.y+1] == WALL && Table[pos.x-1][pos.y] == WALL) {
    return true;
  } else if (Table[pos.x-1][pos.y] == WALL && Table[pos.x][pos.y-1] == WALL) {
    return true;
  } else {
    return false;
  }
}
// regarde s'il y a un mur complet entre 2 positions interdites et qu'il n'y a pas
// de point final
bool check_wall_line(Position pos1, Position pos2, int** Table) { 
  int diff_pos;
  bool case_x; // true == x | false == y
  if (pos1.x == pos2.x) {
    diff_pos = pos1.x - pos2.x;
    case_x = true;
  } else if (pos1.y != pos2.y) {
    diff_pos = pos1.y - pos2.y;
    case_x = true;
  } else {
    return false;
  }

  if (case_x) {
    if (diff_pos < 0) {
      for (int i = pos1.x; i < pos2.x; i++) {
        if (Table[i][pos1.y] == TARGET) {
          return false;
        }
      }
    } else {
      for (int i = pos1.x; i > pos2.x; i--) {
        if (Table[i][pos1.y] == TARGET) {
          return false;
        }
      }
    }
  } else {
    if (diff_pos < 0) {
        for (int i = pos1.y; i < pos2.y; i++) {
          if (Table[pos1.x][i] == TARGET) {
            return false;
          }
        }
      } else {
        for (int i = pos1.x; i > pos2.x; i--) {
          if (Table[pos1.x][i] == TARGET) {
            return false;
          }
        }
      }

      
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
  vector<Position> list_forbid_pos = get_impossible_positions(board)
  
  if (S.verife_win())
    printf("win\n");
  return 0;
}
