#include "tttgame.h"


int main()
{
    int playerId = 2 , computerId = 1;
    bool playerTurn = false , computerTurn = true;

    cout << "do you want player first? y/n: ";
    char wannaPlayFirst;
    cin >> wannaPlayFirst;

    if(wannaPlayFirst == 'y' || wannaPlayFirst == 'Y')
    {
        playerId=1;
        computerId=2;
        playerTurn = true;
        computerTurn = false;
    }

    tttgame game(playerId,computerId); //set ids , set def value to x,y,z rows
    for(int i=1;i<=9;i++)
    {
            if(game.getRoundCounter()<=9)
            {
                if(playerTurn && !computerTurn)
                {
                    game.playerMove();
                    playerTurn = false;
                    computerTurn = true;
                }
                else if(computerTurn && !playerTurn)
                {
                    game.computerMove();
                    computerTurn = false;
                    playerTurn = true;
                }
                else
                    cout << "problem in manage turns with flags." << endl;
            }
            else
                break;
    }
}
