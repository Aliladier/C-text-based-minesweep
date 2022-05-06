# Group-58

Team members: Chen Huixiang, Zhu Lingxiao

Game: MineSweeper

Game Rules: Before the start of the game, the player will be asked whether he wants to play a new game or continue the last game. If he wants to play a new game, there will be three difficulty levels for him to choose. Then the game board will be printed and there will be five choices for him to choose for his next move. The choices include 1.dig a grid 2. sign a grid 3. remove a sign 4. ask for a tip and 0. quit. Except the last choice(quit), the player will be asked for inputting a coordinate of the grid of the move. If he choooses to quit the game, he can choose either to save the game or to leave. The saved game will be named as (the time when the player started the game).txt in the same directory of the game. If he wants to continue his last game, he will be asked which game he wants to continue. After the inputting of the name of the last game, he can continue his last play.

1.Generation of random game sets or events: The position of land mine will be produced randomly.

2.Data structures for storing game status: 2D arrays and different types of variables are used to store the game status.

3.File input/output (e.g., for loading/saving game status): The status of the game will be stored as a file if the player quit the game.

4.Program codes in multiple files: The program is put in multiple files so self-defined functions can be used directly in the main function without difining.

5.Dynamic memory management: In the main function, only dynamic variables are used and deleted after the program is finished.

Two libraries are created named as "newgame.h" and "loadgame.h". (We are not sure if these are included in the non-standard libraries and if not, there are not any external non-standard libraries used)

We used academy 11 server for testing.

When executing is needed, turn to the directory that all files in the repo are in in terminal, and then input the following commands:
make minesweep
./minesweep
The game can then be played.
