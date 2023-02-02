#ifndef GAURD_TTTGAME_H
#define GAURD_TTTGAME_H

#include "configs.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <stdlib.h>
#include <time.h>
#include <queue>

using namespace std;
using std::endl;
using std::cout;

static int roundCounter=0;

class tttgame
{
    private:
        int x[3],y[3],z[3];
        queue<int> computerX,computerY,computerZ;

        queue<int> playerX,playerY,playerZ;

    public:
        tttgame(int,int); //set computer & player id
        int move(int,int); //return -1 or cell id choosen
        int gameResultCheck();
        int getRoundCounter();

        int computerInitMove(); //return choosen cell id
        int computerMove(); //returns choosen cell id
        void computerCalculateMove();
        void computerClearCaculatedMoves();

        void consoleLog();
        void resetGame();
        void cleanQueue(std::queue<int>&);

        int computerScore =0;
        int playerScore =0;
        int player2Score=0;
};

#endif
