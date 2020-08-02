/**
* LanGong 2020
* @langong-dev
* &minesweeper
**/


#include <iostream>
#include <cstdio>
#include <curses.h>
#include <unistd.h>
using namespace std;


#include "getkeyboard.cpp"

namespace getkey
{
  int keyboard()
  {
  	return key::getkey();
  }
  int checkkey(int num){
  	if(num==72||num=='w'||num=='W')return 1;
  	if(num==80||num=='s'||num=='S')return 2;
  	if(num==75||num=='a'||num=='A')return 3;
  	if(num==77||num=='d'||num=='D')return 4;
  	if(num==10)return 13;
  	if(num==114)return 7;
  	if(num==112)return 8;
  	if(num==113)return 9;
  	if(num==27)return 27;
    if(num==224||num==-32)return -1;
  	else return 0;
  }
}

const int small = 10;
const int mid = 20;
const int big = 50;
const int inf = 55;
const char con[10] = "/dev/tty";

using namespace getkey;

int filed [55][55];

class User
{
public:
  int level;
  char level_file[1000];
  char user[1000];
  char log_file[1000];
} user;

void StartProgress ()
{
  printf (" Starting MineSweeper game...\n");
  system ("echo $HOME/.local/share/minesweeper/log > /tmp/minesweeper-log");
  system ("echo $USER > /tmp/minesweeper-user");
  system ("echo $HOME/.local/share/minesweeper/level > /tmp/minesweeper-lev");
  freopen ("/tmp/minesweeper-log", "r", stdin);
  cin >> user.log_file;
  freopen ("/tmp/minesweeper-user", "r", stdin);
  cin >> user.user;
  freopen ("/tmp/minesweeper-lev", "r", stdin);
  cin >> user.level_file;
  freopen (user.level_file, "r", stdin);
  cin >> user.level;
  freopen (con, "r", stdin);
  cout << user.user << " " << user.level << " " << user.log_file;
}

int main (int argc, char* argv[])
{
  StartProgress();
}
