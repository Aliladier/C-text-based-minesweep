//Author: Zhu Lingxiao, Chen Huixiang
//Group project: Mine sweeping
#include <iostream>
#include "newgame.h"
#include "loadgame.h"
using namespace std;

int main(){
  cout << "\t\t---- Wellcome to MineSweep! ----" << endl;
  int *opt = new int;

  cout << "Do you want to continue to play the last game or play a new game?" << endl;
  cout << " 1. I want to continue the last game." << endl;
  cout << " 2. I want to play a new game." << endl;
  cin >> *opt;

  if(*opt == 2){
    newgame();
  }
  else if(*opt == 1){
    loadgame();
  }

  delete opt;
}
