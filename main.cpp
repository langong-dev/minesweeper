#define LanGong 2020


/**
* LanGong 2020
* @langong-dev
* &minesweeper
**/


#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <curses.h>
#include <unistd.h>
#include <ctime>
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
    if(num==32)return 14;
    if(num==224||num==-32)return -1;
  	else return 0;
  }
}

const int small = 10;
const int mid = 15;
const int big = 25;
const int inf = 55;
const int shot = 10;
const int mid_le = 20;
const int many = 40;

const char con[10] = "/dev/tty";
const char error[100][100] = {
  "--------- Error UKE: Unknow Error ----------\n",
  "--------- Error 1: User not found ----------\n"
};

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const int nx[8] = {1, 1, 1, 0, -1, -1, -1, 0};
const int ny[8] = {1, 0, -1, -1, -1, 0, 1, 1};

clock_t stime, etime;

using namespace getkey;

int field [inf][inf], back [inf][inf], num[inf][inf], flag[inf][inf];
bool vis[inf][inf];
int sig, x, y, fcount, ftrue;

int gw ()
{
  switch (sig) {
    case 0: return 0;
    case 1: return small;
    case 2: return mid;
    case 3: return big;
    default: return 0;
  }
}

int gr ()
{
  switch (sig) {
    case 0: return 0;
    case 1: return shot;
    case 2: return mid_le;
    case 3: return many;
    default: return 0;
  }
}

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
  user.level = -1;
  printf (" Starting Terminal MineSweeper game...\n");
  system ("echo $HOME/.local/share/tminesweeper/log > /tmp/tminesweeper-log");
  system ("echo $USER > /tmp/tminesweeper-user");
  system ("echo $HOME/.local/share/tminesweeper/level > /tmp/tminesweeper-lev");
  freopen ("/tmp/tminesweeper-log", "r", stdin);
  cin >> user.log_file;
  freopen ("/tmp/tminesweeper-user", "r", stdin);
  cin >> user.user;
  freopen ("/tmp/tminesweeper-lev", "r", stdin);
  cin >> user.level_file;
  freopen (user.level_file, "r", stdin);
  cin >> user.level;
  freopen (con, "r", stdin);
  //cout << user.user << " " << user.level << " " << user.log_file;
  if (user.level == -1)
  {
    printf (" %s Use 'tminesweeper init' to creat a user.\n", error[1]);
    exit (1);
  }
  if (user.level <= 25)
  {
    sig = 1;
  }
  if (user.level > 25)
  {
    sig = 2;
  }
  if (user.level > 50)
  {
    sig = 3;
  }
  if (sig == 0)
  {
    printf ("%s", error[0]);
    exit (-1);
  }
}


/*
field[i][j] = {
  1 => WALL
  2 => GROUND
}
*/


void InitsialGame ()
{
  printf (" Initsialing game\n");
  for (int i = 1; i <= gw(); i ++)
  {
    for (int j = 1; j <= gw(); j ++)
    {
      field[i][j] = 1;
      back[i][j] = 0;
      vis [i][j] = 0;
      num[i][j] = 0;
      flag[i][j] = 0;
    }
  }
  x = 1, y = 1, fcount = 0, ftrue = 0;
  int lea = 0;
  // for (int i = 1; i <= gw(); i ++)
  // {
  //   for (int j = 1; j <= gw(); j ++)
  //   {
  //     int r = 1ll * rand() * 33 / 77 % 400;
  //     r &= 77;
  //     r |= 77;
  //     r *= 77;
  //     r = r % 20;
  //     if (lea >= gr()) break;
  //     if (r == 1 || r == 7 || r == 9 || r == 17)
  //     {
  //       back[i][j] = -1;
  //       lea++;
  //       for (int i = 0; i < 8; i ++)
  //       {
  //         int xx = nx[i] + i;
  //         int yy = ny[i] + j;
  //         if (xx < 1 || yy < 1 || xx > gw() || yy > gw())
  //         {
  //           continue;
  //         }
  //         if (back[xx][yy] == -1)
  //         {
  //           continue;
  //         }
  //         back[xx][yy] ++;
  //       }
  //     }
  //     else if (r == 3 || r == 8 || r ==13 || r ==17)
  //     {
  //       int sr = 1ll * rand() * r ^ r % 2;
  //       if (sr == 1)
  //       {
  //         back[i][j] = -1;
  //         lea++;
  //         for (int i = 0; i < 8; i ++)
  //         {
  //           int xx = nx[i] + i;
  //           int yy = ny[i] + j;
  //           if (xx < 1 || yy < 1 || xx > gw() || yy > gw())
  //           {
  //             continue;
  //           }
  //           if (back[xx][yy] == -1)
  //           {
  //             continue;
  //           }
  //           back[xx][yy] ++;
  //         }
  //       }
  //     }
  //   }
  // }
  for (int i = 0; i < gr(); i ++)
  {
    int x = 1ll * (rand ()) / 555 % gw() + 1;
    int y = 1ll * (rand ()) / 555 % gw() + 1;
    if (back [x][y] == -1)
    {
      i --;
      //printf ("AH%d %d\n", x, y);
      continue;
    }
    back[x][y] = -1;
    for (int j = 0; j < 8; j ++)
    {
      int xx = nx[j] + x;
      int yy = ny[j] + y;
      if (xx < 1 || yy < 1 || xx > gw() || yy > gw())
      {
        continue;
      }
      if (back[xx][yy] == -1)
      {
        continue;
      }
      back[xx][yy] ++;
    }
  }
}

void dead (){
  etime = clock();
  // system ("clear");
  printf ("\033[31m Boom! You lose!\033[0m\n");
  freopen ("/tmp/minesweeper-tmp", "w", stdout);
  printf ("User %s lose the game. Used %lf sec.\n", user.user, double(etime-stime)/CLOCKS_PER_SEC);
  system ("echo $(cat /tmp/tminesweeper-tmp) >> $HOME/.local/share/tminesweeper/log");
  exit (0);
}

void win ()
{
  etime = clock();
  // system ("clear");
  printf ("\033[32m Well done! You win the game! Used %lf sec!\033[0m\n", double(etime-stime)/CLOCKS_PER_SEC);
  freopen (user.level_file, "w", stdout);
  printf ("%d", ++ user.level);
  freopen ("/tmp/tminesweeper-tmp", "w", stdout);
  printf ("User %s win the level %d in %lf sec.", user.user, user.level, double(etime-stime)/CLOCKS_PER_SEC);
  system ("echo $(cat /tmp/tminesweeper-tmp) >> $HOME/.local/share/tminesweeper/log");
  exit (0);
}

void dfs (int x, int y)
{
  if (vis[x][y])
  {
    return;
  }
  vis[x][y] = 1;
  if (back[x][y] == -1)
  {
    dead();
  }
  if (flag[x][y])
  {
    fcount--;
    flag[x][y] = 1;
  }
  if (back[x][y] == 0)
  {
    field[x][y] = 2;
    num[x][y] = 0;
  }
  else{
    field[x][y] = 2;
    num[x][y] = back[x][y];
    return;
  }
  for (int i = 0; i < 4; i ++)
  {
    int xx = dx[i] + x;
    int yy = dy[i] + y;
    if (xx < 1 || yy < 1 || xx > gw() || yy > gw())
    {
      continue;
    }
    dfs (xx, yy);
  }
}

int StartGame()
{
  int mylei = 0;
  int truelei = 0;
  stime = clock ();
  while (true)
  {
    system ("clear");
    if (ftrue >= gr())
    {
      // win ();
      win ();
      return 0;
      break;
    }
    //34Blue 32Green
    for (int i = 1; i <= gw(); i ++)
    {
      printf (" ");
      for (int j = 1; j <= gw(); j ++)
      {
        if (field[i][j] == 1)
        {
          if (x == i && y == j)
          {
            printf ("\033[43m");
          }
          else{
            printf ("\033[44m");
          }

          if (flag[i][j])
          {
            printf ("F");
          }
          else if (num[i][j] == 0)
          {
            printf (" ");
          }
          else
          {
            printf ("%d", num[i][j]);
          }
          printf (" \033[0m");
        }
        else
        {
          if (x == i && y == j)
          {
            printf ("\033[43m");
          }
          else{
            printf ("\033[42m");
          }
          if (flag[i][j])
          {
            printf ("F");
          }
          else if (num[i][j] == 0)
          {
            printf (" ");
          }
          else
          {
            printf ("%d", num[i][j]);
          }
          printf (" \033[0m");
        }
      }
      printf ("\n");
    }
    printf ("\n");
    printf (" Use UP DOWN LEFT RIGHT to move\n Use SPACE to mark it\n Use ENTER to check\n\n Your level is %d\n There are %d bombs left\n", user.level, gr() - fcount);
    int r = checkkey(keyboard());
    if (r == 1)
    {
      if (x > 1)
      {
        x --;
      }
    }
    if (r == 2)
    {
      if (x < gw())
      {
        x ++;
      }
    }
    if (r == 3)
    {
      if (y > 1)
      {
        y --;
      }
    }
    if (r == 4)
    {
      if (y < gw())
      {
        y ++;
      }
    }
    if (r == 9)
    {
      return 0;
    }
    if (r == 13)
    {
      //printf ("Check...");
      dfs (x, y);
      // for (int i = 1; i <= gw(); i ++)
      // {
      //   for (int j = 1; j <=gw(); j ++)
      //   {
      //     printf ("%d ", num[i][j]);
      //   }
      //   printf ("\n");
      // }sleep(1);
    }
    if (r == 14)
    {
      // printf ("FLAG");
      if (flag[x][y])
      {
        fcount --;
        flag[x][y] = false;
        if (back[x][y] == -1)
        {
          ftrue --;
        }
      }
      else
      {
        if (fcount >= gr())
        {
          continue;
        }
        fcount ++;
        flag[x][y]  = true;
        if (back[x][y] == -1)
        {
          ftrue ++;
        }
      }
      // for (int i = 1; i <= gw(); i ++)
      // {
      //   for (int j = 1; j <=gw(); j ++)
      //   {
      //     printf ("%d ", flag[i][j]);
      //   }
      //   printf ("\n");
      // }sleep(1);
    }
    // break;
  }
  return 0;
}

int main (int argc, char* argv[])
{
  if (argc > 1)
  {
    if (strcmp (argv[1], "init") == 0)
    {
      system ("bash /usr/share/tminesweeper/init.sh");
    }
    if (strcmp (argv[1], "uninstall") == 0)
    {
      printf (" This need sudo, If you are using root, you can input 'y'-ENTER and ignore me or input something with ENTER to exit.\n Input: ");
      char a;
      scanf ("%c", &a);
      if (a == 'y')
        system ("bash /usr/share/tminesweeper/uninstall.sh");
    }
    /*if (strcmp (argv[1], "log"))
    {
      system ("cat ~/.local/share/minesweeper/log");
    }*/
    return 0;
  }
  StartProgress();
  InitsialGame();
  system ("clear");
  // for (int i = 1; i <= gw(); i ++)
  // {
  //   for (int j = 1; j <=gw(); j ++)
  //   {
  //     printf ("%d ", back[i][j]);
  //   }
  //   printf ("\n");
  // }return 0;
  int st = StartGame();
  return st;
}









#ifdef LanGong
  #undef LanGong
#endif
