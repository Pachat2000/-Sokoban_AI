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
  vector<char> move;
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
  vector<char> move_option(vector<Position> impossi_move, char last_move,
                           int joueur);
  bool verife_win(vector<Position> vec_finish);
  vector<Position> get_vec_finish();
  void copy(int B[NBL][NBC]);
  Reponse move(vector<char> list_moves, vector<Position> impossi_move,
               vector<Position> vec_finish, int joeur);
  void sous_func_move(int temp_pos_man1_x, int temp_pos_man1_y, int add_x,
                      int add_y, int is_man_on_target, int joueur);
  int get_min_profondeur(vector<Position> vec_finish);
  void move_back(char str);
};

// PROTOTYPES
vector<char> IDD(int Max_Depth, int **Table, position *List_impossible_moves,
                 vector<Position> vec_finish);
vector<Position> get_impossible_positions(int **board);
bool check_corner(sok_board_t S, Position pos);
vector<Position> check_wall_line(Position pos1, Position pos2, sok_board_t S);

void print_vec(vector<char> chemin_parcouru){
   for (auto i : chemin_parcouru) {
    cout << i ;
 }
 cout << endl;
}

vector<char> IDD(int Max_Depth, sok_board_t Table,
                 vector<Position> List_imposible_moves,
                 vector<Position> vec_finish) {
  Table.move_option(List_imposible_moves, ' ', 1);
  int diff_profondeur = 0;
  int svg = 0;
  int profondeur = Table.get_min_profondeur(vec_finish);
  vector<pair<char, int>> pile;
  pile.push_back(make_pair(' ', 0));
  vector<char> chemin_parcouru;
  int joueur = 2;
  do {
    if (joueur == 1) {
      joueur = 2;
    } else {
      joueur = 1;
    }
    if (pile.size() == 0) {
      
        for (auto _ : chemin_parcouru) {
           Table.move_back(chemin_parcouru.back());
           chemin_parcouru.pop_back();
        }

      profondeur++;
      cout << profondeur << endl;
      diff_profondeur = 0;
      svg = 0;
      
      chemin_parcouru.clear();
      pile.push_back(make_pair(' ', 0));
      joueur = 1;
    }
    diff_profondeur = svg;
    pair<char, int> n = pile[pile.size() - 1];
    svg = n.second;
    pile.pop_back();
    if (n.second < diff_profondeur) {
      for (int i = 0; i < (diff_profondeur - n.second); i++) {
        //Table.move_back(chemin_parcouru.back());
        cout << chemin_parcouru.back() << endl;
         chemin_parcouru.pop_back();
      }
    }
    chemin_parcouru.push_back(n.first);
    if (n.second == profondeur) {

      Reponse t =
          Table.move({chemin_parcouru.back()}, List_imposible_moves, vec_finish, joueur);
          print_vec(chemin_parcouru);
      if (t.win) {

        cout << profondeur << endl;
        //Table.print_board();


        return chemin_parcouru;
      } else {
        //Table.move_back(chemin_parcouru.back());
        chemin_parcouru.pop_back();
      }
    } else {
      Reponse t =
          Table.move({chemin_parcouru.back()}, List_imposible_moves, vec_finish, joueur);
      vector<char> new_move = t.move;
      if (find(new_move.begin(), new_move.end(), 't') != new_move.end()) {
        pile.push_back(make_pair('t', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'g') != new_move.end()) {
        pile.push_back(make_pair('g', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'b') != new_move.end()) {
        pile.push_back(make_pair('b', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'h') != new_move.end()) {
        pile.push_back(make_pair('h', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'w') != new_move.end()) {
        pile.push_back(make_pair('w', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'z') != new_move.end()) {
        pile.push_back(make_pair('z', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'y') != new_move.end()) {
        pile.push_back(make_pair('y', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'x') != new_move.end()) {
        pile.push_back(make_pair('x', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'r') != new_move.end()) {
        pile.push_back(make_pair('r', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'l') != new_move.end()) {
        pile.push_back(make_pair('l', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'd') != new_move.end()) {
        pile.push_back(make_pair('d', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'u') != new_move.end()) {
        pile.push_back(make_pair('u', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'p') != new_move.end()) {
        pile.push_back(make_pair('p', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'o') != new_move.end()) {
        pile.push_back(make_pair('o', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'n') != new_move.end()) {
        pile.push_back(make_pair('n', n.second + 1));
      }
      if (find(new_move.begin(), new_move.end(), 'm') != new_move.end()) {
        pile.push_back(make_pair('m', n.second + 1));
      }

      if (new_move.size() == 0) {
        //Table.move_back(chemin_parcouru.back());
        chemin_parcouru.pop_back();
      }
    }
  } while (profondeur != Max_Depth);
  return chemin_parcouru;
}

inline int sok_board_t::get_min_profondeur(vector<Position> vec_finish) {
  int pox = 0;
  int poy = 0;
  vector<Position> box;
  for (int i = 0; i < board_nbl; i++) {
    for (int j = 0; j < NBC; j++) {
      if (board_str[board[i][j]] == '1' || board_str[board[i][j]] == 'u') {
        pox = j;
        poy = i;
      }
      if (board_str[board[i][j]] == '$') {
        Position a;
        a.x = j;
        a.y = i;
        box.push_back(a);
      }
    }
  }
  int res = 0;
  do {
    int index = 0;
    int distance = 100;
    for (std::vector<Position>::size_type i = 0; i < box.size(); i++) {
      if (abs(pox - box.at(i).x) + abs(poy - box.at(i).y) < distance) {
        distance = abs(pox - box.at(i).x) + abs(poy - box.at(i).y);
        index = i;
      }
    }
    pox = box.at(index).x;
    poy = box.at(index).y;
    res += distance;
    distance = 100;
    for (std::vector<Position>::size_type i = 0; i < vec_finish.size(); i++) {
      if (abs(poy - vec_finish.at(i).x) + abs(pox - vec_finish.at(i).y) <
          distance) {
        distance =
            abs(poy - vec_finish.at(i).x) + abs(pox - vec_finish.at(i).y);
      }
    }
    res += distance - 1;
    box.erase(box.begin() + index);
  } while (box.size() > 0);
  return res;
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

inline vector<Position> sok_board_t::get_vec_finish() {
  vector<Position> vec_finish;
  Position pos;
  for (int i = 0; i < board_nbl; i++) {
    for (int j = 0; j < NBC; j++) {
      if (board[i][j] == TARGET || board[i][j] == MAN1_ON_TARGET) {
        pos.x = i;
        pos.y = j;
        vec_finish.push_back(pos);
      }
    }
  }
  return vec_finish;
}

inline bool sok_board_t::verife_win(vector<Position> vec_finish) {
  for (auto i : vec_finish) {
    if (board[i.x][i.y] == TARGET || board[i.x][i.y] == MAN1_ON_TARGET) {
      return false;
    }
  }
  return true;
}

vector<char> sok_board_t::move_option(vector<Position> impossi_move,
                                      char last_move, int joueur) {
  vector<char> mouvement;
  int posx = 0;
  int posy = 0;
  int x = 0;
  int y = 0;
  char last = ' ';
  char direction = ' ';
  char div = ' ';
  for (int q = 0; q < 2; q++) {
    if (q == 0) {
      posx = man1_y;
      posy = man1_x;
    } else {

      posx = man2_y;
      posy = man2_x;
    }
    for (int i = 0; i < 4; i++) {
      switch (q) {
      case 0:
        switch (i) {
        case 0:
          last = 'd';
          div = 'm';
          direction = 'u';
          y = posy - 1;
          x = posx;
          break;
        case 1:
          last = 'u';
          div = 'n';
          direction = 'd';
          y = posy + 1;
          x = posx;
          break;
        case 2:
          last = 'r';
          div = 'o';
          direction = 'l';
          x = posx - 1;
          y = posy;
          break;
        case 3:
          last = 'l';
          div = 'p';
          direction = 'r';
          x = posx + 1;
          y = posy;
          break;
        }
        break;
      case 1:
        switch (i) {
        case 0:
          last = 'b';
          div = 'x';
          direction = 'h';
          y = posy - 1;
          x = posx;
          break;
        case 1:
          last = 'h';
          div = 'y';
          direction = 'b';
          y = posy + 1;
          x = posx;
          break;
        case 2:
          last = 't';
          div = 'z';
          direction = 'g';
          x = posx - 1;
          y = posy;
          break;
        case 3:
          last = 'g';
          div = 'w';
          direction = 't';
          x = posx + 1;
          y = posy;
          break;
        }
        break;
      }
      if (board_str[board[y][x]] == '$' || board_str[board[y][x]] == '*') {
        if (board_str[board[(posy + (posy - y) * -2)]
                           [(posx + (posx - x) * -2)]] != '$' &&
            board_str[board[(posy + (posy - y) * -2)]
                           [(posx + (posx - x) * -2)]] != '*' &&
            board_str[board[(posy + (posy - y) * -2)]
                           [(posx + (posx - x) * -2)]] != '#' &&
            board_str[board[(posy + (posy - y) * -2)]
                           [(posx + (posx - x) * -2)]] != '2' &&
            board_str[board[(posy + (posy - y) * -2)]
                           [(posx + (posx - x) * -2)]] != 'd' &&
            board_str[board[(posy + (posy - y) * -2)]
                           [(posx + (posx - x) * -2)]] != '1' &&
            board_str[board[(posy + (posy - y) * -2)]
                           [(posx + (posx - x) * -2)]] != 'u') {
          bool test = true;
          for (auto i : impossi_move) {
            if (i.y == (posx + (posx - x) * -2) &&
                i.x == (posy + (posy - y) * -2)) {
              test = false;
            }
          }
          if (test) {
            mouvement.push_back(div);
          }
        }
      } else if (board_str[board[y][x]] != '#' &&
                 board_str[board[y][x]] != '2' &&
                 board_str[board[y][x]] != 'd' &&
                 board_str[board[y][x]] != '1' &&
                 board_str[board[y][x]] != 'u') {
        if (last_move != last) {
          mouvement.push_back(direction);
        }
      }
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
                                        int add_y, int is_man_on_target,
                                        int joueur) {
  int next_man_position;
  int next_box_position; // box state after move
  if (joueur == 1) {
    if ((board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] == FREE) ||
        (board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] ==
         CRATE_ON_FREE)) {
      next_man_position = MAN1_ON_FREE;
    } else {
      next_man_position = MAN1_ON_TARGET;
    }
  } else {
    if ((board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] == FREE) ||
        (board[temp_pos_man1_x + add_x][temp_pos_man1_y + add_y] ==
         CRATE_ON_FREE)) {
      next_man_position = MAN2_ON_FREE;
    } else {
      next_man_position = MAN2_ON_TARGET;
    }
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

inline reponse sok_board_t::move(vector<char> list_moves,
                                 vector<Position> impossi_move,
                                 vector<Position> vec_finish, int joueur) {
  int temp_pos_man1_x = man1_x;
  int temp_pos_man1_y = man1_y;
  int temp_pos_man2_x = man2_x;
  int temp_pos_man2_y = man2_y;
  int is_man_on_target;  // What stays after the man leaves
  int is_man_on_target2; // What stays after the man leaves
  sok_board_t S;
  S.board_nbl = board_nbl;
  S.copy(board);
  for (unsigned int i = 0; i < list_moves.size(); i++) {
    char str = list_moves.at(i);
    if (S.board[temp_pos_man1_x][temp_pos_man1_y] == MAN1_ON_TARGET) {
      is_man_on_target = TARGET;
    } else {
      is_man_on_target = FREE;
    }
    if (str == 'l' || str == 'o') {
      S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 0, -1,
                       is_man_on_target, 1);
      temp_pos_man1_y -= 1;
    } else if (str == 'r' || str == 'p') {
      S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 0, 1, is_man_on_target,
                       1);
      temp_pos_man1_y += 1;
    } else if (str == 'd' || str == 'n') {
      S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 1, 0, is_man_on_target,
                       1);
      temp_pos_man1_x += 1;
    } else if (str == 'u' || str == 'm') {
      S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, -1, 0,
                       is_man_on_target, 1);
      temp_pos_man1_x -= 1;
    }

    if (S.board[temp_pos_man2_x][temp_pos_man2_y] == MAN2_ON_TARGET) {
      is_man_on_target2 = TARGET;
    } else {
      is_man_on_target2 = FREE;
    }
    if (str == 'g' || str == 'z') {
      S.sous_func_move(temp_pos_man2_x, temp_pos_man2_y, 0, -1,
                       is_man_on_target2, 2);
      temp_pos_man2_y -= 1;
    } else if (str == 't' || str == 'w') {
      S.sous_func_move(temp_pos_man2_x, temp_pos_man2_y, 0, 1,
                       is_man_on_target2, 2);
      temp_pos_man2_y += 1;
    } else if (str == 'b' || str == 'y') {
      S.sous_func_move(temp_pos_man2_x, temp_pos_man2_y, 1, 0,
                       is_man_on_target2, 2);
      temp_pos_man2_x += 1;
    } else if (str == 'h' || str == 'x') {
      S.sous_func_move(temp_pos_man2_x, temp_pos_man2_y, -1, 0,
                       is_man_on_target2, 2);
      temp_pos_man2_x -= 1;
    }
  }
  S.print_board();
  S.man1_x = temp_pos_man1_x;
  S.man1_y = temp_pos_man1_y;
  S.man2_x = temp_pos_man2_x;
  S.man2_y = temp_pos_man2_y;
  reponse t;
  t.win = S.verife_win(vec_finish);
  t.move =
      S.move_option(impossi_move, list_moves.at(list_moves.size() - 1), joueur);
  return t;
}


inline void sok_board_t::move_back(char str){
  int is_man_on_target;  // What stays after the man leaves
  int next_man_position;
  int next_box_position; 

  if (str == 'l') {
    if (board[man1_x][man1_y] == MAN1_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }

    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man1_x ][man1_y + 1] == FREE) {
      next_man_position = MAN1_ON_FREE;
    } else {
      next_man_position = MAN1_ON_TARGET;
    }
    board[man1_x][man1_y + 1] = next_man_position ;
    board[man1_x][man1_y] = is_man_on_target;
    man1_y += 1;
    /*S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 0, - 1, is_man_on_target);
      temp_pos_man1_y -= 1;*/
  } else if (str == 'o') { 
      if (board[man1_x][man1_y] == MAN1_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 


    if (board[man1_x ][man1_y + 1] == FREE) {
      next_man_position = MAN1_ON_FREE;
    } else {
      next_man_position = MAN1_ON_TARGET;
    }
    if ((board[man1_x][man1_y-1] == CRATE_ON_FREE)) {
      board[man1_x][man1_y + 1] = next_man_position ;
      board[man1_x][man1_y] = next_box_position;
      board[man1_x][man1_y-1] = FREE;
    }else if (board[man1_x][man1_y-1] == CRATE_ON_TARGET){
      board[man1_x][man1_y + 1] = next_man_position ;
      board[man1_x][man1_y] = next_box_position;
      board[man1_x][man1_y-1] = TARGET;
    }
    man1_y += 1;

  } else if (str == 'r') {  
    if (board[man1_x][man1_y] == MAN1_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 


    if (board[man1_x ][man1_y - 1] == FREE) {
      next_man_position = MAN1_ON_FREE;
    } else {
      next_man_position = MAN1_ON_TARGET;
    }
    board[man1_x][man1_y - 1] = next_man_position ;
    board[man1_x][man1_y] = is_man_on_target;
    man1_y -= 1;
    /*S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 0, 1, is_man_on_target);
    temp_pos_man1_y += 1;*/
  } else if (str == 'p') {
      if (board[man1_x][man1_y] == MAN1_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man1_x ][man1_y - 1] == FREE) {
      next_man_position = MAN1_ON_FREE;
    } else {
      next_man_position = MAN1_ON_TARGET;
    }
    if ((board[man1_x][man1_y+1] == CRATE_ON_FREE)) {
      board[man1_x][man1_y - 1] = next_man_position ;
      board[man1_x][man1_y] = next_box_position;
      board[man1_x][man1_y+1] = FREE;
    }else if (board[man1_x][man1_y+1] == CRATE_ON_TARGET){
      board[man1_x][man1_y - 1] = next_man_position ;
      board[man1_x][man1_y] = next_box_position;
      board[man1_x][man1_y+1] = TARGET;
    }
    man1_y -= 1;
  } else if (str == 'd') {
      if (board[man1_x][man1_y] == MAN1_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }

  if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man1_x -1 ][man1_y ] == FREE) {
      next_man_position = MAN1_ON_FREE;
    } else {
      next_man_position = MAN1_ON_TARGET;
    }
    board[man1_x-1][man1_y] = next_man_position ;
    board[man1_x][man1_y] = is_man_on_target;
    man1_x -= 1;
    /*S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 1, 0, is_man_on_target);
    temp_pos_man1_x += 1;*/
  } else if (str == 'n') {
      if (board[man1_x][man1_y] == MAN1_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man1_x -1 ][man1_y ] == FREE) {
      next_man_position = MAN1_ON_FREE;
    } else {
      next_man_position = MAN1_ON_TARGET;
    }
    if ((board[man1_x+1][man1_y] == CRATE_ON_FREE)) {
      board[man1_x-1][man1_y ] = next_man_position ;
      board[man1_x][man1_y] = next_box_position;
      board[man1_x+1][man1_y] = FREE;
    }else if (board[man1_x+1][man1_y] == CRATE_ON_TARGET){
      board[man1_x-1][man1_y ] = next_man_position ;
      board[man1_x][man1_y] = next_box_position;
      board[man1_x+1][man1_y] = TARGET;
    }
    man1_x -= 1;
  
  } else if (str == 'u') {
      if (board[man1_x][man1_y] == MAN1_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }

  if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man1_x +1 ][man1_y ] == FREE) {
      next_man_position = MAN1_ON_FREE;
    } else {
      next_man_position = MAN1_ON_TARGET;
    }
    board[man1_x+1][man1_y] = next_man_position ;
    board[man1_x][man1_y] = is_man_on_target;
    man1_x += 1;

    /*S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, -1, 0, is_man_on_target);
    temp_pos_man1_x -=  1; */
  }else if (str == 'm') {
      if (board[man1_x][man1_y] == MAN1_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man1_x +1 ][man1_y ] == FREE) {
      next_man_position = MAN1_ON_FREE;
    } else {
      next_man_position = MAN1_ON_TARGET;
    }
    if ((board[man1_x-1][man1_y] == CRATE_ON_FREE)) {
      board[man1_x+1][man1_y ] = next_man_position ;
      board[man1_x][man1_y] = next_box_position;
      board[man1_x-1][man1_y] = FREE;
    }else if (board[man1_x-1][man1_y] == CRATE_ON_TARGET){
      board[man1_x+1][man1_y ] = next_man_position ;
      board[man1_x][man1_y] = next_box_position;
      board[man1_x-1][man1_y] = TARGET;
    }
    man1_x += 1;
  } 
  /*player 2___________________________________________________________________*/
  else if (str == 'g') {
      if (board[man2_x][man2_y] == MAN2_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man2_x ][man2_y + 1] == FREE) {
      next_man_position = MAN2_ON_FREE;
    } else {
      next_man_position = MAN2_ON_TARGET;
    }
    board[man2_x][man2_y + 1] = next_man_position ;
    board[man2_x][man2_y] = is_man_on_target;
    man2_y += 1;
    /*S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 0, - 1, is_man_on_target);
      temp_pos_man1_y -= 1;*/
  } else if (str == 'z') { 

    if (board[man2_x][man2_y] == MAN2_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man2_x ][man2_y + 1] == FREE) {
      next_man_position = MAN2_ON_FREE;
    } else {
      next_man_position = MAN2_ON_TARGET;
    }
    if ((board[man2_x][man2_y-1] == CRATE_ON_FREE)) {
      board[man2_x][man2_y + 1] = next_man_position ;
      board[man2_x][man2_y] = next_box_position;
      board[man2_x][man2_y-1] = FREE;
    }else if (board[man2_x][man2_y-1] == CRATE_ON_TARGET){
      board[man2_x][man2_y + 1] = next_man_position ;
      board[man2_x][man2_y] = next_box_position;
      board[man2_x][man2_y-1] = TARGET;
    }
    man2_y += 1;

  } else if (str == 't') {
    if (board[man2_x][man2_y] == MAN2_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
  if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man2_x ][man2_y - 1] == FREE) {
      next_man_position = MAN2_ON_FREE;
    } else {
      next_man_position = MAN2_ON_TARGET;
    }
    board[man2_x][man2_y - 1] = next_man_position ;
    board[man2_x][man2_y] = is_man_on_target;
    man2_y -= 1;
    /*S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 0, 1, is_man_on_target);
    temp_pos_man1_y += 1;*/
  } else if (str == 'w') {
    if (board[man2_x][man2_y] == MAN2_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man2_x ][man2_y - 1] == FREE) {
      next_man_position = MAN2_ON_FREE;
    } else {
      next_man_position = MAN2_ON_TARGET;
    }
    if ((board[man2_x][man2_y+1] == CRATE_ON_FREE)) {
      board[man2_x][man2_y - 1] = next_man_position ;
      board[man2_x][man2_y] = next_box_position;
      board[man2_x][man2_y+1] = FREE;
    }else if (board[man2_x][man2_y+1] == CRATE_ON_TARGET){
      board[man2_x][man2_y - 1] = next_man_position ;
      board[man2_x][man2_y] = next_box_position;
      board[man2_x][man2_y+1] = TARGET;
    }
    man2_y -= 1;
  } else if (str == 'b') {
    if (board[man2_x][man2_y] == MAN2_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 


    if (board[man2_x -1 ][man2_y ] == FREE) {
      next_man_position = MAN2_ON_FREE;
    } else {
      next_man_position = MAN2_ON_TARGET;
    }
    board[man2_x-1][man2_y] = next_man_position ;
    board[man2_x][man2_y] = is_man_on_target;
    man2_x -= 1;
    /*S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, 1, 0, is_man_on_target);
    temp_pos_man1_x += 1;*/
  } else if (str == 'y') {
    if (board[man2_x][man2_y] == MAN2_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man2_x -1 ][man2_y ] == FREE) {
      next_man_position = MAN2_ON_FREE;
    } else {
      next_man_position = MAN2_ON_TARGET;
    }
    if ((board[man2_x+1][man2_y] == CRATE_ON_FREE)) {
      board[man2_x-1][man2_y ] = next_man_position ;
      board[man2_x][man2_y] = next_box_position;
      board[man2_x+1][man2_y] = FREE;
    }else if (board[man2_x+1][man2_y] == CRATE_ON_TARGET){
      board[man2_x-1][man2_y ] = next_man_position ;
      board[man2_x][man2_y] = next_box_position;
      board[man2_x+1][man2_y] = TARGET;
    }
    man2_x -= 1;
  
  } else if (str == 'h') {
    if (board[man2_x][man2_y] == MAN2_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
  if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man2_x +1 ][man2_y ] == FREE) {
      next_man_position = MAN2_ON_FREE;
    } else {
      next_man_position = MAN2_ON_TARGET;
    }
    board[man2_x+1][man2_y] = next_man_position ;
    board[man2_x][man2_y] = is_man_on_target;
    man2_x += 1;

    /*S.sous_func_move(temp_pos_man1_x, temp_pos_man1_y, -1, 0, is_man_on_target);
    temp_pos_man1_x -=  1; */
  }else if (str == 'x') {
    if (board[man2_x][man2_y] == MAN2_ON_TARGET) {
    is_man_on_target = TARGET;
  } else {
    is_man_on_target = FREE;
  }
    if(is_man_on_target == TARGET){
    next_box_position = CRATE_ON_TARGET;
  } else {
    next_box_position = CRATE_ON_FREE;
  } 

    if (board[man2_x +1 ][man2_y ] == FREE) {
      next_man_position = MAN2_ON_FREE;
    } else {
      next_man_position = MAN2_ON_TARGET;
    }
    if ((board[man2_x-1][man2_y] == CRATE_ON_FREE)) {
      board[man2_x+1][man2_y ] = next_man_position ;
      board[man2_x][man2_y] = next_box_position;
      board[man2_x-1][man2_y] = FREE;
    }else if (board[man2_x-1][man2_y] == CRATE_ON_TARGET){
      board[man2_x+1][man2_y ] = next_man_position ;
      board[man2_x][man2_y] = next_box_position;
      board[man2_x-1][man2_y] = TARGET;
    }
    man2_x += 1;
  }
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
