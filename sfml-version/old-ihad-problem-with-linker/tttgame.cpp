#include "tttgame.h"

//
int tttgame::getRoundCounter()
{
    return roundCounter;
}

int tttgame::computerInitMove()
{
    //later can add some algorithms with priorities for first moves
    srand (time(NULL));
    int random_number = rand() % 9 + 1;
    int result_move = move(computerId,random_number);

    while(result_move==-1 && roundCounter<10)
    {
        cout << "[COMPUER MOVE INFO] the random cell were full, i'll try again find another cell." <<endl;
        random_number = rand() % 9 + 1;
        result_move = move(computerId,random_number);
    }
    return random_number;
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
    if(x[0] == x[1] && x[1] != 0 && x[2] == 0 && x[0] == computerId)    computerX.push(3);
    if(x[0] == x[2] && x[2] != 0 && x[1] == 0 && x[0] == computerId)    computerX.push(2);
    if(x[1] == x[2] && x[2] != 0 && x[0] == 0 && x[1] == computerId)    computerX.push(1);

    //own Y cells
    if(y[0] == y[1] && y[1] != 0 && y[2] == 0 && y[0] == computerId)    computerY.push(6);
    if(y[0] == y[2] && y[2] != 0 && y[1] == 0 && y[0] == computerId)    computerY.push(5);
    if(y[1] == y[2] && y[2] != 0 && y[0] == 0 && y[1] == computerId)    computerY.push(4);

    //own Z cells
    if(z[0] == z[1] && z[1] != 0 && z[2] == 0 && z[0] == computerId)    computerZ.push(9);
    if(z[0] == z[2] && z[2] != 0 && z[1] == 0 && z[0] == computerId)    computerZ.push(8);
    if(z[1] == z[2] && z[2] != 0 && z[0] == 0 && z[1] == computerId)    computerZ.push(7);

    //own XYZ1 cells
    if(x[0] == y[0] && y[0] != 0 && z[0] == 0 && x[0] == computerId)    computerZ.push(7);
    if(x[0] == z[0] && z[0] != 0 && y[0] == 0 && x[0] == computerId)    computerY.push(4);
    if(y[0] == z[0] && z[0] != 0 && x[0] == 0 && y[0] == computerId)    computerX.push(1);

    //own XYZ2 cells
    if(x[1] == y[1] && y[1] != 0 && z[1] == 0 && x[1] == computerId)    computerZ.push(8);
    if(x[1] == z[1] && z[1] != 0 && y[1] == 0 && x[1] == computerId)    computerY.push(5);
    if(y[1] == z[1] && z[1] != 0 && x[1] == 0 && y[1] == computerId)    computerX.push(2);

    //own XYZ3 cells
    if(x[2] == y[2] && y[2] != 0 && z[2] == 0 && x[2] == computerId)    computerZ.push(9);
    if(x[2] == z[2] && z[2] != 0 && y[2] == 0 && x[2] == computerId)    computerY.push(6);
    if(y[2] == z[2] && z[2] != 0 && x[2] == 0 && y[2] == computerId)    computerX.push(3);

    //own XYZ159 cells
    if(x[0] == y[1] && y[1] != 0 && z[2] == 0 && x[0] == computerId)    computerZ.push(9);
    if(x[0] == z[2] && z[2] != 0 && y[1] == 0 && x[0] == computerId)    computerY.push(5);
    if(y[1] == z[2] && z[2] != 0 && x[0] == 0 && y[1] == computerId)    computerX.push(1);

    //own XYZ357 cells
    if(x[2] == y[1] && y[1] != 0 && z[0] == 0 && x[2] == computerId)    computerZ.push(7);
    if(x[2] == z[0] && z[0] != 0 && y[1] == 0 && x[2] == computerId)    computerY.push(5);
    if(y[1] == z[0] && z[0] != 0 && x[2] == 0 && y[1] == computerId)    computerX.push(3);




    //enemy X cells
    if(x[0] == x[1] && x[1] != 0 && x[2] == 0 && x[0] == playerId)    playerX.push(3);
    if(x[0] == x[2] && x[2] != 0 && x[1] == 0 && x[0] == playerId)    playerX.push(2);
    if(x[1] == x[2] && x[2] != 0 && x[0] == 0 && x[1] == playerId)    playerX.push(1);

    //enemy Y cells
    if(y[0] == y[1] && y[1] != 0 && y[2] == 0 && y[0] == playerId)    playerY.push(6);
    if(y[0] == y[2] && y[2] != 0 && y[1] == 0 && y[0] == playerId)    playerY.push(5);
    if(y[1] == y[2] && y[2] != 0 && y[0] == 0 && y[1] == playerId)    playerY.push(4);

    //enemy Z cells
    if(z[0] == z[1] && z[1] != 0 && z[2] == 0 && z[0] == playerId)    playerZ.push(9);
    if(z[0] == z[2] && z[2] != 0 && z[1] == 0 && z[0] == playerId)    playerZ.push(8);
    if(z[1] == z[2] && z[2] != 0 && z[0] == 0 && z[1] == playerId)    playerZ.push(7);

    //enemy XYZ1 cells
    if(x[0] == y[0] && y[0] != 0 && z[0] == 0 && x[0] == playerId)    playerZ.push(7);
    if(x[0] == z[0] && z[0] != 0 && y[0] == 0 && x[0] == playerId)    playerY.push(4);
    if(y[0] == z[0] && z[0] != 0 && x[0] == 0 && y[0] == playerId)    playerX.push(1);

    //enemy XYZ2 cells
    if(x[1] == y[1] && y[1] != 0 && z[1] == 0 && x[1] == playerId)    playerZ.push(8);
    if(x[1] == z[1] && z[1] != 0 && y[1] == 0 && x[1] == playerId)    playerY.push(5);
    if(y[1] == z[1] && z[1] != 0 && x[1] == 0 && y[1] == playerId)    playerX.push(2);

    //enemy XYZ3 cells
    if(x[2] == y[2] && y[2] != 0 && z[2] == 0 && x[2] == playerId)    playerZ.push(9);
    if(x[2] == z[2] && z[2] != 0 && y[2] == 0 && x[2] == playerId)    playerY.push(6);
    if(y[2] == z[2] && z[2] != 0 && x[2] == 0 && y[2] == playerId)    playerX.push(3);

    //enemy XYZ159 cells
    if(x[0] == y[1] && y[1] != 0 && z[2] == 0 && x[0] == playerId)    playerZ.push(9);
    if(x[0] == z[2] && z[2] != 0 && y[1] == 0 && x[0] == playerId)    playerY.push(5);
    if(y[1] == z[2] && z[2] != 0 && x[0] == 0 && y[1] == playerId)    playerX.push(1);

    //enemy XYZ357 cells
    if(x[2] == y[1] && y[1] != 0 && z[0] == 0 && x[2] == playerId)    playerZ.push(7);
    if(x[2] == z[0] && z[0] != 0 && y[1] == 0 && x[2] == playerId)    playerY.push(5);
    if(y[1] == z[0] && z[0] != 0 && x[2] == 0 && y[1] == playerId)    playerX.push(3);
}


int tttgame::computerMove()
{
    computerCalculateMove();

    bool resultMove=1;

    if(computerX.empty() &&
       computerY.empty() &&
       computerZ.empty() &&
       playerX.empty() &&
       playerY.empty() &&
       playerZ.empty())
    {
        computerInitMove();
    }

    while(!computerX.empty() && resultMove==-1)
    {
            resultMove = move(computerId,computerX.front());
            computerX.pop();
    }

    while(!computerY.empty() && resultMove==-1)
    {
            resultMove = move(computerId,computerY.front());
            computerY.pop();
    }

    while(!computerZ.empty() && resultMove==-1)
    {
            resultMove = move(computerId,computerZ.front());
            computerZ.pop();
    }


    while(!playerX.empty() && resultMove==-1)
    {
            resultMove = move(computerId,playerX.front());
            playerX.pop();
    }

    while(!playerY.empty() && resultMove==-1)
    {
            resultMove = move(computerId,playerY.front());
            playerY.pop();
    }

    while(!playerZ.empty() && resultMove==-1)
    {
            resultMove = move(computerId,playerZ.front());
            playerZ.pop();
    }
    return resultMove; //for ui to know what was computer move
}

tttgame::tttgame(int playerid,int computerid)
{
    playerId = playerid;
    computerId = computerid;

    x[0] = x[1] = x[2] =
    y[0] = y[1] = y[2] =
    z[0] = z[1] = z[2] = 0;
}

int tttgame::move(int playerid,int cellid)
{
    //return -1 means error was occurapted else return cellId
    if(playerid>2 || playerid<1)
    {
        cout << "[INVALID INPUT] player id is invalid." << endl;
        return -1;
    }
    if(roundCounter>10)
    {
        cout << "[GAME INFO] Max rounds is 9, the game is end player " << playerid << " can't move cell " << cellid << "." << endl;
        return -1;
    }


    switch (cellid)
    {
            case 1:
            {
                if(!x[0]) x[0] = playerid;
                else { cout <<"[DUPLICATE INPUT] the x0 cell is full."<<endl; return -1; }
            }break;


            case 2:
            {
                if(!x[1]) x[1] = playerid;
                else { cout <<"[DUPLICATE INPUT] the x1 cell is full."<<endl; return -1; }
            }break;


            case 3:
            {
                if(!x[2]) x[2] = playerid;
                else { cout <<"[DUPLICATE INPUT] the x2 cell is full."<<endl; return -1; }
            }break;


            case 4:
            {
                if(!y[0]) y[0] = playerid;
                else { cout <<"[DUPLICATE INPUT] the y0 cell is full."<<endl; return -1; }
            }break;


            case 5:
            {
                if(!y[1]) y[1] = playerid;
                else { cout <<"[DUPLICATE INPUT] the y1 cell is full."<<endl; return -1; }
            }break;


            case 6:
            {
                if(!y[2]) y[2] = playerid;
                else { cout <<"[DUPLICATE INPUT] the y2 cell is full."<<endl; return -1; }
            }break;


            case 7:
            {
                if(!z[0]) z[0] = playerid;
                else { cout <<"[DUPLICATE INPUT] the z0 cell is full."<<endl; return -1; }
            }break;


            case 8:
            {
                if(!z[1]) z[1] = playerid;
                else { cout <<"[DUPLICATE INPUT] the z1 cell is full."<<endl; return -1; }
            }break;


            case 9:
            {
                if(!z[2]) z[2] = playerid;
                else { cout <<"[DUPLICATE INPUT] the z2 cell is full."<<endl; return -1; }
            }break;


            default:
            {
                cout <<"[INVALID INPUT] cell id " << cellid <<" is invalid."<<endl;
                return -1;
            }break;
    }

    consoleLog();

    int resultMove = gameResultCheck();
    if(!resultMove)
        roundCounter++;
    else
        roundCounter = 10;


    return cellid;
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
