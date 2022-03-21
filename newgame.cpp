//Author: Zhu Lingxiao, Chen Huixiang
//Group project: Mine sweeping
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "newgame.h"
using namespace std;

//define the size of the board
#define SIZE 10

//This function is used to initalize the coordinate of the bomb in the Board
//Input: The integer array of the bomb,"0" means no bomb and "1" means have a bomb
//Output: The integer "bombnum" means the total number of bombs in the board
int InitBomb(int Bomb[SIZE][SIZE]){
  for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			Bomb[i][j] = 0;
    }
  }

  int bombnum;
  int *difficulty = new int;
  //the number of bombs is decided by the time
  srand(time(NULL));
  //Let the player to choose the difficulty mode
  cout << "Please select your preferred difficulty level: " << endl;
  cout << "1. Low( Number of bombs: 1 - 20 )" << endl;
  cout << "2. Medium( Number of bombs: 21 - 40 )" << endl;
  cout << "3. High( Number of bombs: 41 - 60 )" << endl;
  cout << "The difficulty you chose is: ";
  cin >> *difficulty;
  cout << endl;

  if (*difficulty == 1){
    bombnum = 1 + rand() % 20;
  }
  else if ( *difficulty == 2){
    bombnum = 21 + rand() % 20;
  }
  else if (*difficulty == 3){
    bombnum = 41 + rand() % 20;
  }
  else{
    cout << "Invalid input! Automatically low difficulty level!" << endl;
    bombnum = 1 + rand() % 20;
  }

  delete difficulty;
  //set the bomb
  for( int num = 0; num < bombnum; num++){
    int i = rand() % SIZE;
    int j = rand() % SIZE;
    if (Bomb[i][j] != 1){
      Bomb[i][j] = 1;
    }
    else{
      num--;
    }
  }

  return bombnum;
}

//This function is used to display the result of the game board after finishing the game
//Input: two integer arrays,  one shows the coordinate of bombs,
//       and the other one shows the number of bombs around the grid
//Output: no output, the function prints the result of the game board
void Display_Bomb(int Bomb[SIZE][SIZE], int Board[SIZE][SIZE]){
  int i, j;
  //set the game board
	cout << "  " << " | ";
	for(i = 0; i < SIZE; i++){
    if(i != 9){
		  cout << i << " | ";
    }
    else{
      cout << i << " |" << endl;
    }
  }
	cout << "---+---+---+---+---+---+---+---+---+---+---+" << endl;
  //making the symbol of bomb to be "*"
	for(i = 0; i < SIZE; i++){
		cout << ' ' << i << " | ";
		for(j = 0; j < SIZE; j++){
			if(Bomb[i][j] == 1){
        if (j == 9){
          cout << "* |" << endl;
        }
        else{
          cout << '*' << " | ";
        }
      }
			else{
        if (j == 9){
          cout << Board[i][j] << " |"<< endl;
        }
        else{
          cout << Board[i][j] << " | ";
        }
      }
		}
    if (i != 9){
	    cout << "---+---+---+---+---+---+---+---+---+---+---+" << endl;
    }
    else{
      cout << "---+---+---+---+---+---+---+---+---+---+---+" << endl;
    }
	}
}

//This function is used to decided the number to be printed on those safe grid,
//and the number is determined by the number of bombs around the grid.
//Input: two integer arrays, one shows the coordinate of bombs,
//       and the other one shows the number to be printed on the safe grid
//Output: no output, the function is used to initalize those safe grids
void InitBoard(int Board[SIZE][SIZE], int Bomb[SIZE][SIZE]){
	for(int i = 0;i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			Board[i][j] = 0;
    }
  }

	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
      if (Bomb[i][j] == 1){   //if one grid has a bomb, the numbers around the
        if (i == 0){          //grid will be added 1
          if (j == 0){
            Board[i][j+1]++;
            Board[i+1][j]++;
            Board[i+1][j+1]++;
          }
          else if (j >= 1 && j <= 8){
            Board[i+1][j]++;
            Board[i+1][j+1]++;
            Board[i+1][j-1]++;
            Board[i][j+1]++;
            Board[i][j-1]++;
          }
          else if (j == 9){
            Board[i][j-1]++;
            Board[i+1][j-1]++;
            Board[i+1][j]++;
          }
        }

        else if (i >= 1 && i <= 8){
          if (j == 0){
            Board[i-1][j]++;
            Board[i-1][j+1]++;
            Board[i][j+1]++;
            Board[i+1][j]++;
            Board[i+1][j+1]++;
          }
          else if (j >= 1 && j <= 8){
            Board[i+1][j]++;
            Board[i+1][j+1]++;
            Board[i+1][j-1]++;
            Board[i][j+1]++;
            Board[i][j-1]++;
            Board[i-1][j]++;
            Board[i-1][j+1]++;
            Board[i-1][j-1]++;
          }
          else if (j == 9){
            Board[i-1][j]++;
            Board[i-1][j-1]++;
            Board[i][j-1]++;
            Board[i+1][j]++;
            Board[i+1][j-1]++;
          }
        }

        else if (i == 9){
          if (j == 0){
            Board[i-1][j]++;
            Board[i-1][j+1]++;
            Board[i][j+1]++;
          }
          else if (j >= 1 && j <= 8){
            Board[i-1][j]++;
            Board[i-1][j+1]++;
            Board[i-1][j-1]++;
            Board[i][j+1]++;
            Board[i][j-1]++;
          }
          else if (j == 9){
            Board[i][j-1]++;
            Board[i-1][j-1]++;
            Board[i-1][j]++;
          }
        }
      }
    }
  }

  for(int i = 0;i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      if (Bomb[i][j] == 1){
        Board[i][j] = 0;
      }
    }
  }
}

//This function is used to initalize all the grids to be "#"
//Input: the character array to be initalized
//Output: no output, the function is used to initialize all the grids to be "#"
void InitShown(char Shown[SIZE][SIZE]){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			Shown[i][j] = '#';
    }
  }
}

//This function is used to display the start interface of the game
//Input: the character array and the integer bombnum
//Output: no output, the function is used to display the start interface of the game
void DisplayGrids(char Shown[SIZE][SIZE], int bombnum){
	cout << "Total number of bombs is: "<< bombnum << endl;

  int numOfSign = 0;
  for(int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      if (Shown[i][j] == '!'){
        numOfSign++;    //record the number of signs
      }
    }
  }
  cout << "Total number of signs is: " << numOfSign << endl;

	cout << "  " << " | ";
	for(int i = 0; i < SIZE; i++){
    if(i != 9){
		  cout << i << " | ";
    }
    else{
      cout << i << " |" << "(y)" << endl;
    }
  }
	cout << "---+---+---+---+---+---+---+---+---+---+---+" << endl;

	for(int i = 0; i < SIZE; i++){
		cout << ' ' << i << " | ";
		for(int j = 0; j < SIZE; j++){
      if (j != 9){
			  cout << Shown[i][j] << " | ";
      }
      else{
        cout << Shown[i][j] << " |" << endl;
      }

    }
    if (i != 9){
	    cout << "---+---+---+---+---+---+---+---+---+---+---+" << endl;
    }
    else{
      cout << "---+---+---+---+---+---+---+---+---+---+---+" << endl;
      cout << "(x)" << endl;
    }
	}
}

//This function is used to open the grid if the grid be digged is 0(no bomb around the grid)
//Input: integer i,j means the coordinate of the grid be digged;
//       two integer arrays and one character array
//Output: no output, the function is used to open the grid if the grid be digged is 0(no bomb around the grid)
void open(int i, int j, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]){
  Shown[i][j] = ' ';
  if (i == 0){
    if (j == 0){
      if (Board[i][j+1] == 0 && Bomb[i][j+1] != 1 && Shown[i][j+1] == '#'){
        open(i, j+1,Board, Bomb, Shown);
      }           //if the grid is 0, the open function continues
      else if (Board[i][j+1] != 0 && Shown[i][j+1] == '#'){
        Shown[i][j+1] = 48 + Board[i][j+1];
      }           //if the grid is not 0, the number of the grid will be printed

      if (Board[i+1][j] == 0 && Bomb[i+1][j] != 1 && Shown[i+1][j] == '#' ){
        open(i+1, j,Board, Bomb, Shown);
      }
      else if (Board[i+1][j] != 0 && Shown[i+1][j] == '#'){
        Shown[i+1][j] = 48 + Board[i+1][j];
      }

      if (Board[i+1][j+1] == 0 && Bomb[i+1][j+1] != 1 && Shown[i+1][j+1] == '#'){
        open(i+1, j+1,Board, Bomb, Shown);
      }
      else if (Board[i+1][j+1] != 0 && Shown[i+1][j+1] == '#'){
        Shown[i+1][j+1] = 48 + Board[i+1][j+1];
      }
    }
    else if (j >= 1 && j <= 8){
      if (Board[i+1][j] == 0 && Bomb[i+1][j] != 1 && Shown[i+1][j] == '#' ){
        open(i+1, j,Board, Bomb, Shown);
      }
      else if (Board[i+1][j] != 0 && Shown[i+1][j] == '#'){
        Shown[i+1][j] = 48 + Board[i+1][j];
      }

      if (Board[i+1][j+1] == 0 && Bomb[i+1][j+1] != 1 && Shown[i+1][j+1] == '#'){
        open(i+1, j+1,Board, Bomb, Shown);
      }
      else if (Board[i+1][j+1] != 0 && Shown[i+1][j+1] == '#'){
        Shown[i+1][j+1] = 48 + Board[i+1][j+1];
      }

      if (Board[i+1][j-1] == 0 && Bomb[i+1][j-1] != 1 && Shown[i+1][j-1] == '#'){
        open(i+1, j-1,Board, Bomb, Shown);
      }
      else if (Board[i+1][j-1] != 0 && Shown[i+1][j-1] == '#'){
        Shown[i+1][j-1] = 48 + Board[i+1][j-1];
      }

      if (Board[i][j+1] == 0 && Bomb[i][j+1] != 1 && Shown[i][j+1] == '#'){
        open(i, j+1,Board, Bomb, Shown);
      }
      else if (Board[i][j+1] != 0 && Shown[i][j+1] == '#'){
        Shown[i][j+1] = 48 + Board[i][j+1];
      }

      if (Board[i][j-1] == 0 && Bomb[i][j-1] != 1 && Shown[i][j-1] == '#'){
        open(i, j-1,Board, Bomb, Shown);
      }
      else if (Board[i][j-1] != 0 && Shown[i][j-1] == '#'){
        Shown[i][j-1] = 48 + Board[i][j-1];
      }

    }
    else if (j == 9){
      if (Board[i][j-1] == 0 && Bomb[i][j-1] != 1 && Shown[i][j-1] == '#'){
        open(i, j-1,Board, Bomb, Shown);
      }
      else if (Board[i][j-1] != 0 && Shown[i][j-1] == '#'){
        Shown[i][j-1] = 48 + Board[i][j-1];
      }

      if (Board[i+1][j-1]== 0 && Bomb[i+1][j-1] != 1 && Shown[i+1][j-1]== '#'){
        open(i+1, j+1,Board, Bomb, Shown);
      }
      else if (Board[i+1][j-1] != 0 && Shown[i+1][j-1] == '#'){
        Shown[i+1][j-1] = 48 + Board[i+1][j-1];
      }

      if (Board[i+1][j] == 0 && Bomb[i+1][j] != 1 && Shown[i+1][j] == '#'){
        open(i+1, j,Board, Bomb, Shown);
      }
      else if (Board[i+1][j] != 0 && Shown[i+1][j] == '#'){
        Shown[i+1][j] = 48 + Board[i+1][j];
      }
    }
  }

  else if (i >= 1 && i <= 8){
    if (j == 0){
      if (Board[i-1][j] == 0 && Bomb[i-1][j] != 1 && Shown[i-1][j] == '#'){
        open(i-1, j,Board, Bomb, Shown);
      }
      else if (Board[i-1][j] != 0 && Shown[i-1][j] == '#'){
        Shown[i-1][j] = 48 + Board[i-1][j];
      }

      if (Board[i-1][j+1] == 0 && Bomb[i-1][j+1] != 1 && Shown[i-1][j+1] == '#'){
        open(i-1, j+1,Board, Bomb, Shown);
      }
      else if (Board[i-1][j+1] != 0 && Shown[i-1][j+1] == '#'){
        Shown[i-1][j+1] = 48 + Board[i-1][j+1];
      }

      if (Board[i][j+1]== 0 && Bomb[i][j+1] != 1 && Shown[i][j+1] == '#'){
        open(i, j+1,Board, Bomb, Shown);
      }
      else if (Board[i][j+1] != 0 && Shown[i][j+1] == '#'){
        Shown[i][j+1] = 48 + Board[i][j+1];
      }

      if (Board[i+1][j] == 0 && Bomb[i+1][j] != 1 && Shown[i+1][j] == '#'){
        open(i+1, j,Board, Bomb, Shown);
      }
      else if (Board[i+1][j] != 0 && Shown[i+1][j] == '#'){
        Shown[i+1][j] = 48 + Board[i+1][j];
      }

      if (Board[i+1][j+1] == 0 && Bomb[i+1][j+1] != 1 && Shown[i+1][j+1] == '#'){
        open(i+1, j+1,Board, Bomb, Shown);
      }
      else if (Board[i+1][j+1] != 0 && Shown[i+1][j+1] == '#'){
        Shown[i+1][j+1] = 48 + Board[i+1][j+1];
      }

    }
    else if (j >= 1 && j <= 8){
      if (Board[i-1][j] == 0 && Bomb[i-1][j] != 1 && Shown[i-1][j] == '#'){
        open(i-1, j,Board, Bomb, Shown);
      }
      else if (Board[i-1][j] != 0 && Shown[i-1][j] == '#'){
        Shown[i-1][j] = 48 + Board[i-1][j];
      }

      if (Board[i-1][j+1] == 0 && Bomb[i-1][j+1] != 1 && Shown[i-1][j+1] == '#'){
        open(i-1, j+1,Board, Bomb, Shown);
      }
      else if (Board[i-1][j+1] != 0 && Shown[i-1][j+1] == '#'){
        Shown[i-1][j+1] = 48 + Board[i-1][j+1];
      }

      if (Board[i][j+1]== 0 && Bomb[i][j+1] != 1 && Shown[i][j+1] == '#'){
        open(i, j+1,Board, Bomb, Shown);
      }
      else if (Board[i][j+1] != 0 && Shown[i][j+1] == '#'){
        Shown[i][j+1] = 48 + Board[i][j+1];
      }

      if (Board[i+1][j] == 0 && Bomb[i+1][j] != 1 && Shown[i+1][j] == '#'){
        open(i+1, j,Board, Bomb, Shown);
      }
      else if (Board[i+1][j] != 0 && Shown[i+1][j] == '#'){
        Shown[i+1][j] = 48 + Board[i+1][j];
      }

      if (Board[i+1][j+1] == 0 && Bomb[i+1][j+1] != 1 && Shown[i+1][j+1] == '#'){
        open(i+1, j+1,Board, Bomb, Shown);
      }
      else if (Board[i+1][j+1] != 0 && Shown[i+1][j+1] == '#'){
        Shown[i+1][j+1] = 48 + Board[i+1][j+1];
      }

      if (Board[i-1][j-1] == 0 && Bomb[i-1][j-1] != 1 && Shown[i-1][j-1] == '#'){
        open(i-1, j-1,Board, Bomb, Shown);
      }
      else if (Board[i-1][j-1] != 0 && Shown[i-1][j-1] == '#'){
        Shown[i-1][j-1] = 48 + Board[i-1][j-1];
      }

      if (Board[i+1][j-1] == 0 && Bomb[i+1][j-1] != 1 && Shown[i+1][j-1] == '#'){
        open(i+1, j-1,Board, Bomb, Shown);
      }
      else if (Board[i+1][j-1] != 0 && Shown[i+1][j-1] == '#'){
        Shown[i+1][j-1] = 48 + Board[i+1][j-1];
      }

      if (Board[i][j-1] == 0 && Bomb[i][j-1] != 1 && Shown[i][j-1] == '#'){
        open(i, j-1,Board, Bomb, Shown);
      }
      else if (Board[i][j-1] != 0 && Shown[i][j-1] == '#'){
        Shown[i][j-1] = 48 + Board[i][j-1];
      }

    }
    else if (j == 9){
      if (Board[i-1][j] == 0 && Bomb[i-1][j] != 1 && Shown[i-1][j] == '#'){
        open(i-1, j,Board, Bomb, Shown);
      }
      else if (Board[i-1][j] != 0 && Shown[i-1][j] == '#'){
        Shown[i-1][j] = 48 + Board[i-1][j];
      }

      if (Board[i-1][j-1] == 0 && Bomb[i-1][j-1] != 1 && Shown[i-1][j-1] == '#'){
        open(i-1, j-1,Board, Bomb, Shown);
      }
      else if (Board[i-1][j-1] != 0 && Shown[i-1][j-1] == '#'){
        Shown[i-1][j-1] = 48 + Board[i-1][j-1];
      }

      if (Board[i][j-1] == 0 && Bomb[i][j-1] != 1 && Shown[i][j-1] == '#'){
        open(i, j-1,Board, Bomb, Shown);
      }
      else if (Board[i][j-1] != 0 && Shown[i][j-1] == '#'){
        Shown[i][j-1] = 48 + Board[i][j-1];
      }

      if (Board[i+1][j] == 0 && Bomb[i+1][j] != 1 && Shown[i+1][j] == '#'){
        open(i+1, j,Board, Bomb, Shown);
      }
      else if (Board[i+1][j] != 0 && Shown[i+1][j] == '#'){
        Shown[i+1][j] = 48 + Board[i+1][j];
      }

      if (Board[i+1][j-1] == 0 && Bomb[i+1][j-1] != 1 && Shown[i+1][j-1] == '#'){
        open(i+1, j-1,Board, Bomb, Shown);
      }
      else if (Board[i+1][j-1] != 0 && Shown[i+1][j-1] == '#'){
        Shown[i+1][j-1] = 48 + Board[i+1][j-1];
      }

    }
  }

  else if (i == 9){
    if (j == 0){
      if (Board[i-1][j] == 0 && Bomb[i-1][j] != 1 && Shown[i-1][j] == '#'){
        open(i-1, j,Board, Bomb, Shown);
      }
      else if (Board[i-1][j] != 0 && Shown[i-1][j] == '#'){
        Shown[i-1][j] = 48 + Board[i-1][j];
      }

      if (Board[i-1][j+1] == 0 && Bomb[i-1][j+1] != 1 && Shown[i-1][j+1] == '#'){
        open(i-1, j+1,Board, Bomb, Shown);
      }
      else if (Board[i-1][j+1] != 0 && Shown[i-1][j+1] == '#'){
        Shown[i-1][j+1] = 48 + Board[i-1][j+1];
      }

      if (Board[i][j+1]== 0 && Bomb[i][j+1] != 1 && Shown[i][j+1] == '#'){
        open(i, j+1,Board, Bomb, Shown);
      }
      else if (Board[i][j+1] != 0 && Shown[i][j+1] == '#'){
        Shown[i][j+1] = 48 + Board[i][j+1];
      }

    }
    else if (j >= 1 && j <= 8){

      if (Board[i-1][j] == 0 && Bomb[i-1][j] != 1 && Shown[i-1][j] == '#'){
        open(i-1, j,Board, Bomb, Shown);
      }
      else if (Board[i-1][j] != 0 && Shown[i-1][j] == '#'){
        Shown[i-1][j] = 48 + Board[i-1][j];
      }

      if (Board[i-1][j+1] == 0 && Bomb[i-1][j+1] != 1 && Shown[i-1][j+1] == '#'){
        open(i-1, j+1,Board, Bomb, Shown);
      }
      else if (Board[i-1][j+1] != 0 && Shown[i-1][j+1] == '#'){
        Shown[i-1][j+1] = 48 + Board[i-1][j+1];
      }

      if (Board[i][j+1]== 0 && Bomb[i][j+1] != 1 && Shown[i][j+1] == '#'){
        open(i, j+1,Board, Bomb, Shown);
      }
      else if (Board[i][j+1] != 0 && Shown[i][j+1] == '#'){
        Shown[i][j+1] = 48 + Board[i][j+1];
      }

      if (Board[i-1][j-1] == 0 && Bomb[i-1][j-1] != 1 && Shown[i-1][j-1] == '#'){
        open(i-1, j-1,Board, Bomb, Shown);
      }
      else if (Board[i-1][j-1] != 0 && Shown[i-1][j-1] == '#'){
        Shown[i-1][j-1] = 48 + Board[i-1][j-1];
      }

      if (Board[i][j-1] == 0 && Bomb[i][j-1] != 1 && Shown[i][j-1] == '#'){
        open(i, j-1,Board, Bomb, Shown);
      }
      else if (Board[i][j-1] != 0 && Shown[i][j-1] == '#'){
        Shown[i][j-1] = 48 + Board[i][j-1];
      }

    }
    else if (j == 9){
      if (Board[i][j-1] == 0 && Bomb[i][j-1] != 1 && Shown[i][j-1] == '#'){
        open(i, j-1,Board, Bomb, Shown);
      }
      else if (Board[i][j-1] != 0 && Shown[i][j-1] == '#'){
        Shown[i][j-1] = 48 + Board[i][j-1];
      }

      if (Board[i-1][j-1] == 0 && Bomb[i-1][j-1] != 1 && Shown[i-1][j-1] == '#'){
        open(i-1, j-1,Board, Bomb, Shown);
      }
      else if (Board[i-1][j-1] != 0 && Shown[i-1][j-1] == '#'){
        Shown[i-1][j-1] = 48 + Board[i-1][j-1];
      }

      if (Board[i-1][j] == 0 && Bomb[i-1][j] != 1 && Shown[i-1][j] == '#'){
        open(i-1, j,Board, Bomb, Shown);
      }
      else if (Board[i-1][j] != 0 && Shown[i-1][j] == '#'){
        Shown[i-1][j] = 48 + Board[i-1][j];
      }

    }
  }
}

//This function is used to dig the grid
//Input: integer x,y means the coordinate of the grid being digged,
//       integer win means whether the game is over
//       two integers Board,Bomb and one char array Shown
//Output: no output, the function is used to dig the grid
void digGrid(int x, int y, int &win, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]){
  if (x >= 0 && x < SIZE && y >= 0 && y < SIZE){
    if (Shown[x][y] == '#'){
      if (Bomb[x][y] == 1){ //the case that the grid be digged has a bomb
        win = 1;  //win = 1 means game over
        Shown[x][y] = '*';
      }
      else{
        if (Board[x][y] != 0){ //the case that the grid be digged has a number(there are bombs around it)
          Shown[x][y] = 48 + Board[x][y];
        }
        else{ //the case that the grid be digged is safe and has no bomb around it
          open(x, y, Board, Bomb, Shown);
        }
      }
    }
    else if (Shown[x][y] == '!'){
      cout << "The grid has been signed! Please input again!\n" << endl;
    }
    else {
      cout << "The grid has already been digged! Please input again!\n" << endl;
    }
  }
  else{
    cout << "Invalid input! Please input again!\n" << endl;
  }
  cout << endl;
}

//This function is used to sign a grid
//Input: int x,y means the coordinate of the grid be signed
//       two int arrays Board,Bomb and one char array Shown
//Output: no output, the function is used to sign a grid
void signGrid(int x, int y, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]){
  if (x >= 0 && x < SIZE && y >= 0 && y < SIZE){
    if (Shown[x][y] == '#'){
      Shown[x][y] = '!';
    }
    else{
      if (Shown[x][y] == '!'){
        cout << "The grid has already been signed!\n" << endl;
      }
      else{
        cout << "Digged grid can't be signed!\n" << endl;
      }
    }
  }
  else{
    cout << "Invalide input! Please input again!\n" << endl;
  }
}

//This function is used to remove a sign
//Input int x,y means the coordinate of the sign be removed
//       two int arrays Board,Bomb and one char array Shown
//Output: no ouotput, the function is used to remove a sign
void RemoveSign(int x, int y, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]){
  if (x >= 0 && x < SIZE && y >= 0 && y < SIZE){
    if (Shown[x][y] == '!'){
      Shown[x][y] = '#';
      cout << "The sign has been removed successfully!\n" << endl;
    }
    else{
      cout << "The grid can't be signed!\n" << endl;
    }
  }
  else{
    cout << "Invalide input! Please input again!\n" << endl;
  }
}

//This function is used to print an array
//Input: int array a
//Outpu: no output, the function is used to print an array
void print_array(int a[][SIZE]){
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      cout << a[i][j] << ' ';
    }
    cout << endl;
  }
}

//This function is used to print an array
//Input: char array a
//Outpu: no output, the function is used to print an array
void print_array1(char a[][SIZE]){
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      cout << a[i][j] << ' ';
    }
    cout << endl;
  }
}

//This function is used to return the choice being chosen
//no Input
//Output: the integer which means the choice being chosen
int Move(){
  int choice;
  cout << "Please select your next move:" << endl;
	cout << " 1. Dig a grid" << endl;
	cout << " 2. Sign a grid" << endl;
  cout << " 3. Remove a sign" << endl;
  cout << " 4. Tips(Sign the bombs in the surronding grids)" << endl;
	cout << " 0. Quit." << endl;

	cin >> choice;
  return choice;
}

//This function is used to decide whether the player wins
//Input: int bombnum, win
//       two int arrays Board, Bomb and one char array Shown
//Output: no output, the function is used to decide whether the player wins
void iswin(int bombnum, int &win, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]){
  int numOfCorrectSign = 0;
  int numOfSign = 0;

  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      if (Shown[i][j] == '!'){
        numOfSign++;    //record the number of signs
      }
    }
  }

  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      if (Bomb[i][j] == 1){
        if (Shown[i][j] == '!'){
          numOfCorrectSign++;   //record the number of correct signs
        }
      }
    }
  }
  //When the player signs all the grids correctly, he wins
  if (numOfCorrectSign == bombnum && numOfSign == numOfCorrectSign){
    win = 2;
  }
}

//This function is used to help the player sign the bomb around the input grid
//Input: integer x,y means the grid needs to be hinted
//       two int arrays Board,Bomb and one char array Shown
//Output: no output, the function is used to help the player sign the bomb around the input grid
void tip(int x, int y, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]){
  if (x - 1 >= 0){
    if (y - 1 >= 0){
      if (Bomb[x - 1][y - 1] == 1){
        Shown[x - 1][y - 1] = '!';
      }
    }

    if (y + 1 < SIZE){
      if (Bomb[x - 1][y + 1] == 1){
        Shown[x - 1][y + 1] = '!';
      }
    }

    if (Bomb[x - 1][y] == 1){
      Shown[x - 1][y] = '!';
    }
  }

  if (x + 1 < SIZE){
    if (y - 1 >= 0){
      if (Bomb[x + 1][y - 1] == 1){
        Shown[x + 1][y - 1] = '!';
      }
    }

    if (y + 1 < SIZE){
      if (Bomb[x + 1][y + 1] == 1){
        Shown[x + 1][y + 1] = '!';
      }
    }

    if (Bomb[x + 1][y] == 1){
      Shown[x + 1][y] = '!';
    }
  }

  if (y - 1 >= 0){
    if (Bomb[x][y - 1] == 1){
      Shown[x][y - 1] = '!';
    }
  }

  if (y + 1 < SIZE){
    if (Bomb[x][y + 1] == 1){
      Shown[x][y + 1] = '!';
    }
  }
}

//This function is the main program
//no Input
//no Output
void newgame(){
  int x, y;
  int bombnum;
  int win = 0;
  int *choice = new int, *opt = new int;
  int Bomb[SIZE][SIZE]; //the array which shows the coordinate of bombs
  int Board[SIZE][SIZE];  //the array which shows the number of bombs around each grid
  char Shown[SIZE][SIZE]; //the array which shows whether the grid being digged or signed

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

  bombnum = InitBomb(Bomb);
  InitBoard(Board, Bomb); //initalize the coordinate of bombs
  InitShown(Shown);       //initalize the number of bombs around each grids

  //following block of codes is used to debug when the program is not fully finished
  //Display_Bomb(Bomb);
  //cout << endl;
  //print_array(Board);

  DisplayGrids(Shown, bombnum); //display the start interface of the game
  *choice = Move();   //give choices to the player

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

    DisplayGrids(Shown, bombnum); //display the game board after one move
    iswin(bombnum, win, Board, Bomb, Shown);  //decide whether the game is over
    if (win == 2){    //the case when the player wins
      cout << "Congradulations! You find all the correct positions of the bombs!" << endl;
      cout << "Correct positions of the bombs are:" << endl;
      Display_Bomb(Bomb, Board);
      break;
    }
    else if (win == 1){   //the case when the player fails
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
      break;
    }
    *choice = Move();   //ask the player next move
  }

  if (*choice == 0){
    //ask the player whether he wants to save the game
    cout << "Do you want to save the game?" << endl;
    cout << " 1. Yes" << endl;
    cout << " 2. No" << endl;
    cin >> *opt;
    //saving game status
    if(*opt == 1)
    {
      ofstream fout;
      fout.open(s);
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
      cout << "The name of the file is " << s << endl;
    }
    else
      cout << "Quit successfully! Wellcome to try again! " << endl;
  }

  delete choice;
}
