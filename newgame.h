#ifndef NEWGAME_H
#define NEWGAME_H

#define SIZE 10

int InitBomb(int Bomb[SIZE][SIZE]);

void Display_Bomb(int Bomb[SIZE][SIZE], int Board[SIZE][SIZE]);

void InitBoard(int Board[SIZE][SIZE], int Bomb[SIZE][SIZE]);

void InitShown(char Shown[SIZE][SIZE]);

void DisplayGrids(char Shown[SIZE][SIZE], int bombnum);

void open(int i, int j, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]);

void digGrid(int x, int y, int &win, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]);

void signGrid(int x, int y, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]);

void RemoveSign(int x, int y, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]);

int Move();

void iswin(int bombnum, int &win, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]);

void tip(int x, int y, int Board[SIZE][SIZE], int Bomb[SIZE][SIZE] ,char Shown[SIZE][SIZE]);

void newgame();

#endif
