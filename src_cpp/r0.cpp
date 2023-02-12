#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>
#include "mysok.h"

int main(int _ac, char** _av) {
  if(_ac != 2) { printf("usage: %s SOK_FILE\n", _av[0]); return 0;}
  sok_board_t S;
  S.load(_av[1]);
  S.print_board();
  vector<string> list_moves ={ "right", "down", "down"} ;
  S.move(list_moves );
  if(S.verife_win())
    printf("win\n");
  return 0;
}
