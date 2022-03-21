//Author: Zhu Lingxiao, Chen Huixiang
//Group project: Mine sweeping
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "loadgame.h"
#include "newgame.h"
using namespace std;

#define SIZE 10

//This function is used to play the game without the initalization
//Input: two int arrays Bomb,Board and one char array Shown
//Output: no output, the function is used to play the game without the initalization
//other documentations should be the same as "newgame()" in "newgame.cpp"
void oldgame(int Bomb[SIZE][SIZE], int Board[SIZE][SIZE], char Shown[SIZE][SIZE]){
  int x, y;
  int bombnum = 0;
  int win = 0;
  int *choice = new int;
  int *opt = new int;

  time_t t;
  t = time(NULL);
  struct tm *lt;
  int ii = time(&t);
  t = time(NULL);
  lt = localtime(&t);
  char nowtime[24];
  memset(nowtime, 0, sizeof(nowtime));
  strftime(nowtime, 24, "%Y_%m_%d_%H:%M:%S", lt);
  string s = nowtime; //sited from https://blog.csdn.net/hanghang121/article/details/50203353
  s = s + ".txt";

  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      if(Bomb[i][j] == 1)
        bombnum += 1;
    }
  }

  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      if(Shown[i][j] == '*')
        Shown[i][j] = ' ';
    }
  }
  //for debugging when the program is not fully finished
  //Display_Bomb(Bomb);
  //cout << endl;
  //print_array(Board);

  DisplayGrids(Shown, bombnum);
  *choice = Move();

  while(1){
    if (*choice == 1){
      cout << "Please input the coordinate of the grid:(format:x y)" << endl;
      cin >> x >> y;
      digGrid(x, y, win, Board, Bomb, Shown);
    }

    else if (*choice == 2){
      cout << "Please input the coordinate of the grid:(format:x y)" << endl;
      cin >> x >> y;
      signGrid(x, y, Board, Bomb, Shown);
    }

    else if (*choice == 3){
      cout << "Please input the coordinate of the sign:(format:x y)" << endl;
      cin >> x >> y;
      RemoveSign(x, y, Board, Bomb, Shown);
    }

    else if (*choice == 4){
      cout << "Please input the coordinate of the grid:(format:x y)" << endl;
      cin >> x >> y;
      tip(x, y, Board, Bomb, Shown);
    }

    else if (*choice == 0){
      break;
    }

    else{
      cout << "Invalid input! Please input again! " << endl;
    }

    DisplayGrids(Shown, bombnum);
    iswin(bombnum, win, Board, Bomb, Shown);
    if (win == 2){
      cout << "Congradulations! You find all the correct positions of the bombs!" << endl;
      cout << "Correct positions of the bombs are:" << endl;
      Display_Bomb(Bomb, Board);
      break;
    }
    else if (win == 1){
      cout << "Sorry! You falied! " << endl;
		  cout << "Correct positions of the bombs are:" << endl;
      Display_Bomb(Bomb, Board);

      int cho;
      cout << "Do you want to try again? " << endl;
      cout << " 1. Yes" << endl;
      cout << " 2. No" << endl;
      cin >> cho;
      if (cho == 1){
        newgame();
      }
      else{
        cout << "Good bye!" << endl;
        exit(1);
      }
    }
    *choice = Move();
  }

  if (*choice == 0){
    //是否存档？
    cout << "Do you want to save the game?" << endl;
    cout << " 1. Yes" << endl;
    cout << " 2. No" << endl;
    cin >> *opt;
    if(*opt == 1)
    {
      ofstream fout(s);
      if(fout.fail())
      {
        cout << "Error in file opening." << endl;
        exit(1);
      }
      for(int i = 0; i < SIZE; i++)
      {
        for(int j = 0; j < SIZE; j ++)
        {
          fout << Bomb[i][j] << ' ';
        }
      }
      fout << endl;
      for(int i = 0; i < SIZE; i++)
      {
        for(int j = 0; j < SIZE; j ++)
        {
          fout << Board[i][j] << ' ';
        }
      }
      fout << endl;
      for(int i = 0; i < SIZE; i++)
      {
        for(int j = 0; j < SIZE; j ++)
        {
          if(Shown[i][j] == ' ')
            Shown[i][j] = '*';
          fout << Shown[i][j] << ' ';
        }
      }
      fout << endl;
      fout.close();
      cout << "Save successfully! Welcome to continue the game!" << endl;
      cout << "The name of the saved file is " << s << endl;
    }
    else
      cout << "Quit successfully! Wellcome to try again! " << endl;
  }

  delete choice;
}

//This function is used to load the game from the saving files
//no Input
//output: no output, the function is used to load the game from the saving files
void loadgame(){
  string filename;
  int Bomb[SIZE][SIZE], p = 0;
  int Board[SIZE][SIZE];
  char Shown[SIZE][SIZE], q;

  ////load the game being saved
  cout << "Which game you want to continue?" << endl;
  cin >> filename;
  ifstream fin(filename.c_str());
  while(fin.fail())
  {
    cout << "Game doesn't exist! Please input again!" << endl;
    cin >> filename;
    ifstream fin(filename.c_str());
  }

  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      fin >> p;
      Bomb[i][j] = p;
    }
  }
  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      fin >> p;
      Board[i][j] = p;
    }
  }
  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      fin >> q;
      Shown[i][j] = q;
    }
  }
  fin.close();
  oldgame(Bomb, Board, Shown); ////continue the game from the saving files
}

