#include "tttgame.h"


int computerId=0;
int playerId=0;
int roundCounter=0;

int tttgame::getRoundCounter()
{
    return roundCounter;
}

int tttgame::playerMove()
{
    //return 0 means player move were successfully complete.
    cout << endl;

    cout << "Your turn: enter cell id between 1-9: ";
    int firstMove = 0;
    cin >> firstMove;

    while(firstMove == 0 || firstMove >= 10)
    {
        firstMove = 0;
        cout << "Your turn: enter cell id between 1-9: ";
        cin >> firstMove;
    }

    if(firstMove > 0 && firstMove <=9)
    {
        int resultMove = move(playerId,firstMove);
        while(resultMove)
        {
            cout << "Your turn: enter cell id: ";
            cin >> firstMove;
            if(firstMove > 0 && firstMove <=9)
                resultMove = move(playerId,firstMove);
        }
        return 0;
    }

    return 1;
}

void tttgame::computerInitMove()
{
    //later can add some algorithms with priorities for first moves
    srand (time(NULL));
    int random_number = rand() % 9 + 1;
    int result_move = move(computerId,random_number);

    while(result_move && roundCounter<10)
    {
        cout << "[COMPUER MOVE INFO] the random cell were full, i'll try again find another cell." <<endl;
        int random_number2 = rand() % 9 + 1;
        result_move = move(computerId,random_number2);
    }
}


void tttgame::computerCalculateMove()
{

    /*these numbers pushing to array X , Y , Z  are like
     * tic tac teo cells
     * [1,2,3]
     * [4,5,6]
     * [7,8,9]
     * then this function check arrays and push number of array is possible to win or lose
     * the priority is win then lose/draw.
     *
     * also 'own' means computer Cells and 'enemy' means player.
     */


      //own X cells
      for(int i=0; i<=3; i++)
      {
          //a -> cell 0
          //b -> cell 1
          //c -> cell 2

           int a,b,c,d,e,f;
               a=b=c=d=e=f=0;


          if(x[a] == x[b] && x[b] != 0 && x[c] == 0 && x[a] == computerCal)    .push(3);
              if(x[a] == x[c] && x[c] != 0 && x[b] == 0 && x[a] == computerCal)    computerX.push(2);
              if(x[1] == x[c] && x[c] != 0 && x[a] == 0 && x[b] == computerCal)    computerX.push(1);
      }


}


void tttgame::computerMove()
{
    computerCalculateMove();



    if(playerCal.empty())
    {
        computerInitMove();
    }
    else
    {

    }


}

tttgame::tttgame(int playerid,int computerid)
{
    playerId = playerid;
    computerId = computerid;

//    x[0] = x[1] = x[2] =
//    y[0] = y[1] = y[2] =
//    z[0] = z[1] = z[2] = 0;
    for(int j=0;j<=2;j++)
    {
        for(int a=0;a<=j+3;a++)
        {
            x[a][j] = j;
        }

    }

}

int tttgame::move(int playerid,int cellid)
{
    //return 1 means error was occurapted
    if(playerid>2 || playerid<1)
    {
        cout << "[INVALID INPUT] player id is invalid." << endl;
        return 1;
    }
    if(roundCounter>10)
    {
        cout << "[GAME INFO] Max rounds is 9, the game is end player " << playerid << " can't move cell " << cellid << "." << endl;
        return 1;
    }

    for(int j=0;j<=2;j++)
    {
        for(int a=0;a<=j+3;a++)
        {
          if(x[a][j] == playerid)
            cout << "[dublicate input] the cell " << x[a][j] << " is full." << endl;
        }
    }

    consoleLog();

    int resultMove = gameResultCheck();
    if(!resultMove)
        roundCounter++;
    else
        roundCounter = 10;


    return 0;
}

int tttgame::gameResultCheck()
{
    /*returns:
        0 means continue.
        1 means player one won.
        2 means player two won.
        3 means game is draw.
    */

    //three horizontals
    if(x[0] == x[1] && x[1] == x[2] && x[2] !=0)
        { cout<<"player "<< x[0] <<" won by raw x"<<endl; return x[0]; }

    else if(y[0] == y[1] && y[1] == y[2] && y[2] !=0)
        { cout<<"player "<< y[0] <<" won by raw y"<<endl; return y[0]; }

    else if(z[0] == z[1] && z[1] == z[2] && z[2] !=0)
        { cout<<"player "<< z[0] <<" won by raw z"<<endl; return z[0]; }


    //three verticals
    else if(x[0] == y[0] && y[0] == z[0] && z[0] !=0)
        { cout<<"player "<< x[0] <<" won by raw xyz 0"<<endl; return x[0]; }

    else if(x[1] == y[1] && y[1] == z[1] && z[1] !=0)
        { cout<<"player "<< x[1] <<" won by raw xyz 1"<<endl; return x[1]; }

    else if(x[2] == y[2] && y[2] == z[2] && z[2] !=0)
        { cout<<"player "<< x[2] <<" won by raw xyz 2"<<endl; return x[2]; }


    //two X
    else if(x[0] == y[1] && y[1] == z[2] && z[2] !=0)
        { cout<<"player "<< x[0] <<" won by raw xyz 159"<<endl; return x[0]; }

    else if(x[2] == y[1] && y[1] == z[0] && z[0] !=0)
        { cout<<"player "<< x[2] <<" won by raw xyz 357"<<endl; return x[2]; }


    //game equal
    else if(x[0] && x[1] && x[2] &&
            y[0] && y[1] && y[2] &&
            z[0] && z[1] && z[2] !=0)
    {
        cout << "[GAME END] game is draw." <<endl;
        return 3;
    }

    else
        cout <<"game is continue"<<endl;
    return 0;
}

void tttgame::consoleLog()
{
    cout << endl;
    cout << "- - - - - - - - - - Game Status - - - - - - - - - -" << endl;
    cout << "x = ["<< x[0] << "," << x[1] << "," << x[2] << "]" <<endl;
    cout << "y = ["<< y[0] << "," << y[1] << "," << y[2] << "]" <<endl;
    cout << "z = ["<< z[0] << "," << z[1] << "," << z[2] << "]" <<endl;

    /*NOTES:
        * these blow codes used for knows how          COMPUTER ANALYSIS         the game for debug.
        * also enemy means player , own means computer.

        * fetch private queues assign to new queue becuse there is need to print all queues for print as log and if use main queues the values
        inside main queue will be clean it's will be made problem.
    */

  /*queue<int>
    own2x(computerX),own2y(computerY),own2z(computerZ),enemy2x(playerX),enemy2y(playerY),enemy2z(playerZ);
    cout << "own2x:"; while(!own2x.empty()) { cout<<" "<<own2x.front(); own2x.pop(); } cout <<endl;
    cout << "own2y:"; while(!own2y.empty()) { cout<<" "<<own2y.front(); own2y.pop(); } cout <<endl;
    cout << "own2z:"; while(!own2z.empty()) { cout<<" "<<own2z.front(); own2z.pop(); } cout <<endl;
    cout << "enemy2x:"; while(!enemy2x.empty()) { cout<<" "<<enemy2x.front(); enemy2x.pop(); } cout <<endl;
    cout << "enemy2y:"; while(!enemy2y.empty()) { cout<<" "<<enemy2y.front(); enemy2y.pop(); } cout <<endl;
    cout << "enemy2z:"; while(!enemy2z.empty()) { cout<<" "<<enemy2z.front(); enemy2z.pop(); } cout << endl;*/
}
