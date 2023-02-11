#ifndef MYSOK_H
#define MYSOK_H
#include <cstdio>
#include <cstdlib>
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

bool verif_win (int ** Table, vector<string> chemin);
int ** move(vector<string> Liste_moves, int** Table);
vector<string> move_options(int ** Table, position * List_imposible_moves);
char board_str[] = {' ','_','.','#','$','*','1','u','2','d','a'};
std::string move_str[] = {"Up", "Down", "Left", "Right", "Wait"};

typedef struct position{
  int x;
  int y;
}position;

typedef struct noeud {
  int profondeur;
  string direction;
  noeud* up;
  noeud* down;
  noeud* left;
  noeud* right;
} Noeud;

Noeud* new_noeud(int prof,string direct, Noeud* u, Noeud* d, Noeud* l, Noeud* r){
  Noeud * n = new Noeud;
  n->profondeur = prof;
  n->direction = direct;
  n->up = u;
  n->down = d;
  n->left = l;
  n->right = r;
  return n;
}

void supr_noeud(Noeud * noeud){
  delete noeud;
  noeud = NULL;
}

void suppr_arbre(Noued* arbre){
  vector<Noeud*> pile;
  pile.push_back(arbre);
  while(pile.length != 0){
    Noeud* n = pile.pop();
    if(n->up == NULL && n->down == NULL && n->left == NULL && n->rigth == NULL) suppr_noeud(n);
    else{
      if(n->rigth != NULL) pile.push_back(n->right);
      if(n->left != NULL) pile.push_back(n->left);
      if(n->down != NULL) pile.push_back(n->down);
      if(n->up != NULL) pile.push_back(n->up);
    }
  }
}

vector<string> IDD (int Max_Depth, int ** Table,  position * List_imposible_moves){
  int profondeur = 0;
  Noeud* racine = new_noeud(profondeur, "", NULL, NULL, NULL, NULL);
  vector<Noeud*> pile;
  vector<string> chemin_parcouru;
  pile.push_back(racine);
  do{
    if(pile.length == 0) profondeur++; pile.push_back(racine);
    Noeud* n = pile.pop();
    chemin_parcouru.push_back(n->direction);
    if(n->profondeur == profondeur){
      if(verif_win(tableau,chemin_parcouru)){
	return chemin_parcouru;
      }
      else{
	chemin_parcouru.pop();
      }
    }
    else{
      int ** tmp = move(chemin_parcouru, Table);
      vector<string> new_move = move_option(tmp, List_imposible_moves);
      for(auto i : new_move){
	if(i == "up"){
	  n->up = new_noeud(n->profondeur+1, "up", NULL, NULL, NULL, NULL);
	}
	if(i == "down"){
	  n->down = new_noeud(n->profondeur+1, "down", NULL, NULL, NULL, NULL);
	}
	if(i == "left"){
	  n->left = new_noeud(n->profondeur+1, "left", NULL, NULL, NULL, NULL);
	}
	if(i == "rigth"){
	  n->rigth = new_noeud(n->profondeur+1, "rigth", NULL, NULL, NULL, NULL);
	}
      }
      if(n->right != NULL) pile.push_back(n->right);
      if(n->left != NULL) pile.push_back(n->left);
      if(n->down != NULL) pile.push_back(n->down);
      if(n->up != NULL) pile.push_back(n->up);
    }
  }while(profondeur != Max_Depth);
  suppr_arbre(racine);
  return chemin_parcouru;
}



struct sok_board_t {  
  int board[NBL][NBC];
  int board_nbl;
  int man1_x;
  int man1_y;
  int man2_x;
  int man2_y;
  
  sok_board_t();
  void print_board();
  void load(char* _file);
  void move_option();
  bool verife_win();
};

inline sok_board_t::sok_board_t() {
  for(int i = 0; i < NBL; i++)
    for(int j = 0; j < NBC; j++)
      board[i][j] = FREE;
}

inline void sok_board_t::print_board() {
  for(int i = 0; i < board_nbl; i++) {
    for(int j = 0; j < NBC; j++) {
      if(board[i][j]==END_OF_LINE) break;
      printf("%c", board_str[board[i][j]]);
    }
    printf("\n");
  }
}

inline bool sok_board_t::verife_win(){
  for(int i = 0; i < board_nbl; i++) {
    for(int j = 0; j < NBC; j++) {
      if(board_str[board[i][j]]=='.' || board_str[board[i][j]]=='u')
      return false;}}
      return true;
}

inline void sok_board_t::move_option(){
  int posx=0;
  int posy=0;
  int option[4][2];
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 2; j++) {
      option[i][j]=-1;}}
   for(int i = 0; i < board_nbl; i++) {
    for(int j = 0; j < NBC; j++) {
      if (board_str[board[i][j]]=='1'){
        posx=j;
        posy=i;}
    }}
    int index=0;
    int x=0;
    int y=0;
    for(int i = 0; i < 4; i++) {
      if(i<2){
        x=posx-1+i*2;
        y=posy;
      }
      else{
        x=posx;
        y=posy-1+(i-2)*2;}
      if(board_str[board[y][x]]=='$'){
          if(board_str[board[(posy+(posy-y)*-2)][(posx+(posx-x)*-2)]]!='$' && board_str[board[(posy+(posy-y)*-2)][(posx+(posx-x)*-2)]]!='#'){
            option[index][0]=x;
            option[index][1]=y;
        }}
        else if(board_str[board[y][x]]!='#'){
          option[index][0]=x;
          option[index][1]=y;
          index++;
        }
      }
      for(int i = 0; i < 4; i++) {
      if(option[i][0]!=-1)
      printf("next postion=%d;%d\n",option[i][0],option[i][1]);}
  
}
inline void sok_board_t::load(char* _file) {
  FILE *fp = fopen(_file, "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  if (fp == NULL) {
    perror("fopen"); exit(EXIT_FAILURE);
  }
  board_nbl = 0;
  while ((nread = getline(&line, &len, fp)) != -1) {
    if(((int)nread) > 0) {
      bool read_ok = false;
      for(int i = 0; i < nread; i++) {
        if(line[i] == board_str[FREE]) {
          board[board_nbl][i] = FREE;
        } else if(line[i] == board_str[TARGET]) {
          board[board_nbl][i] = TARGET;
        } else if(line[i] == board_str[WALL]) {
          read_ok = true;
          board[board_nbl][i] = WALL;
        } else if(line[i] == board_str[CRATE_ON_FREE]) {
          board[board_nbl][i] = CRATE_ON_FREE;
        } else if(line[i] == board_str[CRATE_ON_TARGET]) {
          board[board_nbl][i] = CRATE_ON_TARGET;
        } else if(line[i] == board_str[MAN1_ON_FREE]) {
          man1_x = board_nbl;
          man1_y = i; 
          board[board_nbl][i] = MAN1_ON_FREE;
        } else if(line[i] == board_str[MAN1_ON_TARGET]) {
          man1_x = board_nbl;
          man1_y = i; 
          board[board_nbl][i] = MAN1_ON_TARGET;
        } else if(line[i] == board_str[MAN2_ON_FREE]) {
          man2_x = board_nbl;
          man2_y = i; 
          board[board_nbl][i] = MAN2_ON_FREE;
        } else if(line[i] == board_str[MAN2_ON_TARGET]) {
          man2_x = board_nbl;
          man2_y = i; 
          board[board_nbl][i] = MAN2_ON_TARGET;
        }
      }
      if(read_ok) {
        board[board_nbl][nread-1]=END_OF_LINE;
        board_nbl++;
      }
    }
  }
  free(line);
  fclose(fp);
}

#endif
