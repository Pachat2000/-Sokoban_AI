#ifndef MYSOK_H
#define MYSOK_H
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>

#define NBL 20
#define NBC 20
#define MAX_CRATES 20

#define MOVE_U 0
#define MOVE_D 1
#define MOVE_L 2
#define MOVE_R 3
#define MOVE_W 4

#define OUT 0
#define FREE 1
#define TARGET 2
#define WALL 3
#define CRATE_ON_FREE 4
#define CRATE_ON_TARGET 5
#define MAN1_ON_FREE 6
#define MAN1_ON_TARGET 7
#define MAN2_ON_FREE 8
#define MAN2_ON_TARGET 9
#define END_OF_LINE 10

using namespace std;

char board_str[] = {' ', '_', '.', '#', '$', '*', '1', 'u', '2', 'd', 'a'};
std::string move_str[] = {"Up", "Down", "Left", "Right", "Wait"};

typedef struct position {
  int x;
  int y;
} Position;

// PROTOTYPES
int** move(vector<string> list_moves, int** tab_init);
vector<string> IDD (int Max_Depth, int ** Table,  position * List_impossible_moves);
vector<Position> get_impossible_positions (int ** board);
bool check_corner(int** Table, Position pos);
bool check_wall_line(Position forbid1, Position forbid2, int** tab_init);

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
  vector<string> move_option(vector<string>,vector<Position>);
  bool verife_win(int **,vector<string>);
};


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
// l'utiliser dans une fonction move que Manal va faire (plus pratique pour pachat)
inline bool sok_board_t::verife_win() {
  for (int i = 0; i < board_nbl; i++) {
    for (int j = 0; j < NBC; j++) {
      if (board_str[board[i][j]] == '.' || board_str[board[i][j]] == 'u')
        return false;
    }
  }
  return true;
}

vector<string> sok_board_t::move_option(vector<Position> impossi_move,vector<string> mo) {
 vector<string> mouvement;
 int posx=0;
 int posy=0;
  for (int i = 0; i < board_nbl; i++) {
    for (int j = 0; j < NBC; j++) {
      if (board_str[board[i][j]] == '1') {
        posx = j;
        posy = i;
      }
    }
  }
  for(vector<string>::iterator it = mo.begin(); it != mo.end(); it++){
		if (*it=="Up")posx-=1;
    else if (*it=="Down")posx+=1;
    else if (*it=="Left")posy-=1;
    else if (*it=="Right")posy+=1;
	}
  int x = 0;
  int y = 0;
  string direction="";
  for (int i = 0; i < 4; i++) {
    switch(i){
      case 0:
      direction="Up";
      y=posy-1;
      x=posx;
      break;
      case 1:
      direction="Down";
      y=posy+1;
      x=posx;
      break;
      case 2:
      direction="Left";
      x=posx-1;
      y=posy;
      break;
      case 3:
      direction="Right";
      x=posx+1;
      y=posy;
      break;
    }
    bool test=true;
    for(auto i:impossi_move){
      if(i.y==x && i.x==y){
        test=false;
      }
    }
    if(test){
    if (board_str[board[y][x]] == '$') {
      if (board_str[board[(posy + (posy - y) * -2)]
                         [(posx + (posx - x) * -2)]] != '$' &&
          board_str[board[(posy + (posy - y) * -2)]
                         [(posx + (posx - x) * -2)]] != '#') {
        mouvement.push_back(direction);
      }
    } else if (board_str[board[y][x]] != '#') {
      mouvement.push_back(direction);
    }
  }}
  return mouvement;
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
