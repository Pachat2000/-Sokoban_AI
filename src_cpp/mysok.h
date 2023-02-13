#ifndef MYSOK_H
#define MYSOK_H
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

#define NBL 20
#define NBC 20
#define MAX_CRATES 20

#define MOVE_U 0
#define MOVE_D 1
#define MOVE_L 2
#define MOVE_R 3
#define MOVE_W 4

#define OUT 0             // ' '
#define FREE 1            // '_'
#define TARGET 2          // '.'
#define WALL 3            // '#'
#define CRATE_ON_FREE 4   // '$'
#define CRATE_ON_TARGET 5 // '*'
#define MAN1_ON_FREE 6    // '1'
#define MAN1_ON_TARGET 7  // 'u'
#define MAN2_ON_FREE 8    // '2'
#define MAN2_ON_TARGET 9  // 'd'
#define END_OF_LINE 10    // 'a'

using namespace std;

char board_str[] = {' ', '_', '.', '#', '$', '*', '1', 'u', '2', 'd', 'a'};
std::string move_str[] = {"Up", "Down", "Left", "Right", "Wait"};

typedef struct position {
  int x;
  int y;
} Position;

typedef struct reponse {
  bool win;
  vector<string> move;
} Reponse;

struct sok_board_t {
  int board[NBL][NBC];
  int board_nbl;
  int man1_x;
  int man1_y;
  int man2_x;
  int man2_y;

  sok_board_t();
  void print_board();
  void load(char *_file);
  vector<string> move_option(vector<Position> impossi_move);
  bool verife_win();
  void copy(int B[NBL][NBC]);
  Reponse move(vector<string> list_moves, vector<Position> impossi_move);
  void sous_func_move(int temp_pos_man1_x, int temp_pos_man1_y, int add_x,
                      int add_y, int is_man_on_target);
};

// PROTOTYPES
int **move(vector<string> list_moves, int **tab_init);
vector<string> IDD(int Max_Depth, int **Table, position *List_impossible_moves);
vector<Position> get_impossible_positions(int **board);
bool check_corner(sok_board_t S, Position pos);
vector<Position> check_wall_line(Position pos1, Position pos2, sok_board_t S);

vector<string> IDD(int Max_Depth, sok_board_t Table,
                   vector<Position> List_imposible_moves) {

  Table.move_option(List_imposible_moves);
  int diff_profondeur = 0;
  int svg = 0;
  int profondeur = 0;
  vector<pair<string, int>> pile;
  pile.push_back(make_pair("", 0));
  vector<string> chemin_parcouru;
  do {
    if (pile.size() == 0) {
      profondeur++;
      cout << profondeur << endl;
      diff_profondeur = 0;
      svg = 0;
      chemin_parcouru.clear();
      pile.push_back(make_pair("", 0));
    }

    diff_profondeur = svg;
    pair<string, int> n = pile[pile.size() - 1];
    svg = n.second;
    pile.pop_back();
    if (n.second < diff_profondeur) {
      for (int i = 0; i < (diff_profondeur - n.second); i++) {
        chemin_parcouru.pop_back();
      }
    }
    chemin_parcouru.push_back(n.first);
    if (n.second == profondeur) {

      Reponse t = Table.move(chemin_parcouru, List_imposible_moves);
      if (t.win) {
        cout << profondeur << endl;
        return chemin_parcouru;
      } else {
        chemin_parcouru.pop_back();
      }
    } else {
      Reponse t = Table.move(chemin_parcouru, List_imposible_moves);
      vector<string> new_move = t.move;
      for (auto i : new_move) {
        // cout << "COUCOUC " + i;
      }
      // cout << endl;
      if (find(new_move.begin(), new_move.end(), "r") != new_move.end()) {
        pile.push_back(make_pair("r", n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), "l") != new_move.end()) {
        pile.push_back(make_pair("l", n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), "d") != new_move.end()) {
        pile.push_back(make_pair("d", n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), "u") != new_move.end()) {
        pile.push_back(make_pair("u", n.second + 1));
      }
    }
  } while (profondeur != Max_Depth);
  return chemin_parcouru;
}

inline sok_board_t::sok_board_t() {
  for (int i = 0; i < NBL; i++)
    for (int j = 0; j < NBC; j++)
      board[i][j] = FREE;
}

inline void sok_board_t::print_board() {
  for (int i = 0; i < board_nbl; i++) {
    for (int j = 0; j < NBC; j++) {
      if (board[i][j] == END_OF_LINE)
        break;
      printf("%c", board_str[board[i][j]]);
    }
    printf("\n");
  }
}

// TO-DO pour Bruno: Il faudrait que la fonction verif win prenne
// en argument la tableau initial et la liste de chemin pour pouvoir
// l'utiliser dans une fonction move que Manal va faire (plus pratique pour
// pachat)
inline bool sok_board_t::verife_win() {
  for (int i = 0; i < board_nbl; i++) {
    for (int j = 0; j < NBC; j++) {
      if (board_str[board[i][j]] == '.' || board_str[board[i][j]] == 'u')
        return false;
    }
  }
  return true;
}

vector<string> sok_board_t::move_option(vector<Position> impossi_move) {
  vector<string> mouvement;
  int posx = 0;
  int posy = 0;
  for (int i = 0; i < board_nbl; i++) {
    for (int j = 0; j < NBC; j++) {
      if (board_str[board[i][j]] == '1' || board_str[board[i][j]] == 'u') {
        posx = j;
        posy = i;
      }
    }
  }
  int x = 0;
  int y = 0;
  string direction = "";
  for (int i = 0; i < 4; i++) {
    switch (i) {
    case 0:
      direction = "u";
      y = posy - 1;
      x = posx;
      break;
    case 1:
      direction = "d";
      y = posy + 1;
      x = posx;
      break;
    case 2:
      direction = "l";
      x = posx - 1;
      y = posy;
      break;
    case 3:
      direction = "r";
      x = posx + 1;
      y = posy;
      break;
    }
    if (board_str[board[y][x]] == '$' || board_str[board[y][x]] == '*') {
      if (board_str[board[(posy + (posy - y) * -2)]
                         [(posx + (posx - x) * -2)]] != '$' &&
          board_str[board[(posy + (posy - y) * -2)]
                         [(posx + (posx - x) * -2)]] != '*' &&
          board_str[board[(posy + (posy - y) * -2)]
                         [(posx + (posx - x) * -2)]] != '#') {
        bool test = true;
        for (auto i : impossi_move) {
          if (i.y == (posx + (posx - x) * -2) &&
              i.x == (posy + (posy - y) * -2)) {
            test = false;
          }
        }
        if (test) {
          mouvement.push_back(direction);
        }
      }
    } else if (board_str[board[y][x]] != '#') {
      mouvement.push_back(direction);
    }
  }
  return mouvement;
}

/*position sok_board_t::research_man_position(){
  for(int i = 0; i < board_nbl; i++) {
    for(int j = 0; j < NBC; j++) {
      if(board[i][j]==END_OF_LINE) break;
      if ((board[i][j]==MAN1_ON_FREE)||(board[i][j]==MAN1_ON_TARGET)) return
position(i,j);
    }
  }
}*/
/* sok */
// Renvois le nouveau tableau après application de la liste de déplacement
inline void sok_board_t::copy(int B[NBL][NBC]) {
  for (int i = 0; i < board_nbl; i++) {
    for (int j = 0; j < NBC; j++) {
      if (B[i][j] == END_OF_LINE)
        break;
      board[i][j] = B[i][j];
    }
  }
}

inline void sok_board_t::sous_func_move(int temp_pos_man1_x,
                                        int temp_pos_man1_y, int add_x,
                                        int add_y, int is_man_on_target) {
  int next_man_position;
  int next_box_position; // box state after move
  if ((board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] == FREE) ||
      (board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] ==
       CRATE_ON_FREE)) {
    next_man_position = MAN1_ON_FREE;
  } else {
    next_man_position = MAN1_ON_TARGET;
  }
  /* Man moves alone*/
  if ((board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] == FREE) ||
      (board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] == TARGET)) {
    board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] = next_man_position;
    board[temp_pos_man1_x][temp_pos_man1_y] = is_man_on_target;
    temp_pos_man1_y -= 1;

  } else {
    /* next one is box*/
    if (board[temp_pos_man1_x + add_x * 2][temp_pos_man1_y + add_y * 2] ==
        TARGET) {
      next_box_position = CRATE_ON_TARGET;
    } else {
      next_box_position = CRATE_ON_FREE;
    }
    board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] = next_man_position;
    board[temp_pos_man1_x][temp_pos_man1_y] = is_man_on_target;
    board[temp_pos_man1_x + add_x * 2][temp_pos_man1_y + add_y * 2] =
        next_box_position;
  }
}

inline reponse sok_board_t::move(vector<string> list_moves,
                                 vector<Position> impossi_move) {
  int temp_pos_man1_x = man1_x;
  int temp_pos_man1_y = man1_y;
  int is_man_on_target; // What stays after the man leaves
  sok_board_t S;
  S.board_nbl = board_nbl;
  S.copy(board);
  for (unsigned int i = 0; i < list_moves.size(); i++) {
    string str = list_moves.at(i);
    if (S.board[temp_pos_man1_x][temp_pos_man1_y] == MAN1_ON_TARGET) {
      is_man_on_target = TARGET;
    } else {
      is_man_on_target = FREE;
    }

    if (str == "l") {
      S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 0, -1,
                       is_man_on_target);
      temp_pos_man1_y -= 1;
    } else if (str == "r") {
      S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 0, 1,
                       is_man_on_target);
      temp_pos_man1_y += 1;
    } else if (str == "d") {
      S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 1, 0,
                       is_man_on_target);
      temp_pos_man1_x += 1;
    } else if (str == "u") {
      S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, -1, 0,
                       is_man_on_target);
      temp_pos_man1_x -= 1;
    }
  }
  // S.print_board();
  reponse t;
  t.win = S.verife_win();
  t.move = S.move_option(impossi_move);
  return t;
}
inline void sok_board_t::load(char *_file) {
  FILE *fp = fopen(_file, "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  board_nbl = 0;
  while ((nread = getline(&line, &len, fp)) != -1) {
    if (((int)nread) > 0) {
      bool read_ok = false;
      for (int i = 0; i < nread; i++) {
        if (line[i] == board_str[FREE]) {
          board[board_nbl][i] = FREE;
        } else if (line[i] == board_str[TARGET]) {
          board[board_nbl][i] = TARGET;
        } else if (line[i] == board_str[WALL]) {
          read_ok = true;
          board[board_nbl][i] = WALL;
        } else if (line[i] == board_str[CRATE_ON_FREE]) {
          board[board_nbl][i] = CRATE_ON_FREE;
        } else if (line[i] == board_str[CRATE_ON_TARGET]) {
          board[board_nbl][i] = CRATE_ON_TARGET;
        } else if (line[i] == board_str[MAN1_ON_FREE]) {
          man1_x = board_nbl;
          man1_y = i;
          board[board_nbl][i] = MAN1_ON_FREE;
        } else if (line[i] == board_str[MAN1_ON_TARGET]) {
          man1_x = board_nbl;
          man1_y = i;
          board[board_nbl][i] = MAN1_ON_TARGET;
        } else if (line[i] == board_str[MAN2_ON_FREE]) {
          man2_x = board_nbl;
          man2_y = i;
          board[board_nbl][i] = MAN2_ON_FREE;
        } else if (line[i] == board_str[MAN2_ON_TARGET]) {
          man2_x = board_nbl;
          man2_y = i;
          board[board_nbl][i] = MAN2_ON_TARGET;
        }
      }
      if (read_ok) {
        board[board_nbl][nread - 1] = END_OF_LINE;
        board_nbl++;
      }
    }
  }
  free(line);
  fclose(fp);
}

#endif
