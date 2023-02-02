#ifndef TTTGAME_H
#define TTTGAME_H


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>

using namespace std;

class tttgame
{
    private:
//        int x[3],y[3],z[3];
//        queue<int> computerX,computerY,computerZ;
//        queue<int> playerX,playerY,playerZ;

    //new variables
    int x[3][3];
    queue<int>computerCal,playerCal; //playerX,y,z -> single queue also computerXYZ -> same

    public:
        tttgame(int,int); //set computer & player id
        int move(int,int);
        int gameResultCheck();
        int playerMove();
        int getRoundCounter();

        void computerInitMove();
        void computerMove();
        void computerCalculateMove();
        void computerClearCaculatedMoves();

        void consoleLog();

};


#endif // TTTGAME_H
