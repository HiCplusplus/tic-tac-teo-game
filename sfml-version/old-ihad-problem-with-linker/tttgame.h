#ifndef TTTGAME_H
#define TTTGAME_H




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

};
#endif
