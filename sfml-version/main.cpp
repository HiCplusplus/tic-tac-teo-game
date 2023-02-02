// #include "tttgame.h"
#include "/home/mrx/Documents/github/tic-tac-teo-terminal-game/sfml-version/sfml/sf251/include/SFML/Graphics.hpp"
#define appGlobalPath "/home/mrx/Documents/github/tic-tac-teo-terminal-game/sfml-version/"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>

using namespace std;
using std::endl;
using std::cout;

int computerId=1; //def = 9
int playerId=2; //def = 0
int roundCounter=0;


//flag for debug prints
#define ENABLE_DEBUG
// #define ENABLE_FUNCTION_CALLS



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
};

void tttgame::cleanQueue(std::queue<int>&q)
{
    std::queue<int> emptyQ;
    swap(emptyQ,q);
}

void tttgame::resetGame()
{
    cleanQueue(computerX); cleanQueue(computerY); cleanQueue(computerZ);
    cleanQueue(playerX); cleanQueue(playerY); cleanQueue(playerZ);
    x[0] = x[1] = x[2] = y[0] = y[1] = y[2] = z[0] = z[1] = z[2] = 0;
}

int tttgame::getRoundCounter()
{
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\t int tttgame::getRoundCounter()\t";
  #endif
    return roundCounter;
}

int tttgame::computerInitMove()
{
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\t int tttgame::computerInitMove()\t";
  #endif
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
    cout << "computer init move = " << random_number << endl;
    return random_number;
}


void tttgame::computerCalculateMove()
{
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\t void tttgame::computerCalculateMove()\t";
  #endif
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
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\t int tttgame::computerMove()\t";
  #endif
    computerCalculateMove();

    int resultMove=-1;

    if(computerX.empty() &&
       computerY.empty() &&
       computerZ.empty() &&
       playerX.empty() &&
       playerY.empty() &&
       playerZ.empty())
    {
        resultMove = computerInitMove();
        return resultMove;
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
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\ttttgame::tttgame(int playerid,int computerid)\t";
  #endif
    playerId = playerid;
    computerId = computerid;

    x[0] = x[1] = x[2] =
    y[0] = y[1] = y[2] =
    z[0] = z[1] = z[2] = 0;
}

int tttgame::move(int playerid,int cellid)
{
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\tint tttgame::move(int playerid,int cellid)\t";
  #endif
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
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\tint tttgame::gameResultCheck()\t";
  #endif
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
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\tvoid tttgame::consoleLog()\t";
  #endif
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



#define TEXTURESIZE 100
#define HALFTEXTURE TEXTURESIZE/2

//for easy controll 2x for loop (default value is 9)
#define CELLCOUNT 9


enum screenPosition
{
  minY = 0,
  maxY = 600,
  minX = 0,
  maxX = 600,
  centerX = maxX/2,
  centerY = maxY/2

/*cell style
  [ 1 , 2 , 3 ]
  [ 4 , 5 , 6 ]
  [ 7 , 8 , 9 ]
  minX,                                       minY = 1
  centerX-HALFTEXTURE,                        minY =  2
  maxX-TEXTURESIZE,                           minY =  3
  minX,                                       centerY-HALFTEXTURE = 4
  centerX-HALFTEXTURE,                        centerY-HALFTEXTURE = 5
  maxX-TEXTURESIZE,                           centerY-HALFTEXTURE = 6
  minX,                                       maxY-TEXTURESIZE = 7
  centerX-HALFTEXTURE,                        maxY-TEXTURESIZE = 8
  maxX-TEXTURESIZE,                           maxY-TEXTURESIZE = 9
*/
};


//create window
sf::Vector2f viewSize(maxX,maxY);
sf::VideoMode vm(viewSize.x+250, viewSize.y);
sf::RenderWindow window(vm, "Play Tic Tac Toe versus computer", sf::Style::Default);


//texture and sprites
sf::Texture tictactoeTextures[9];
sf::Sprite tictactoeSprites[9];

sf::Texture bgTexture;
sf::Sprite bgSprite;

//for mouse clickes check
sf::FloatRect bounds[9];
sf::FloatRect buttonBound;



//for manage game by user
sf::Font scoreFont;
sf::Text scoreText;

sf::Font scoreLabelFont;
sf::Text scoreLabelText;

sf::Text labelGameStatusText;

sf::Sprite buttonGame;
sf::Texture buttonGameTexture;

sf::Text labelButton;

void initLabels()
{
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\tvoid initLabels()\t";
  #endif

    bgTexture.loadFromFile( appGlobalPath "assets/board.png");
    bgSprite.setTexture(bgTexture);


  	scoreLabelFont.loadFromFile(appGlobalPath "assets/fonts/SnackerComic.ttf");
    scoreLabelText.setFont(scoreLabelFont);
    scoreLabelText.setString("Score:");
    scoreLabelText.setCharacterSize(50);
    scoreLabelText.setFillColor(sf::Color::Red);
    scoreLabelText.setPosition(sf::Vector2f(maxX +75 , minY));



    scoreFont.loadFromFile(appGlobalPath "assets/fonts/arial.ttf");
    scoreText.setFont(scoreFont);
    scoreText.setString("Pc : 0 PL : 0");
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(sf::Color::Blue);
    scoreText.setPosition(sf::Vector2f(maxX +35 , minY+50));



    labelGameStatusText.setFont(scoreFont);
    labelGameStatusText.setString("Game");
    labelGameStatusText.setCharacterSize(30);
    labelGameStatusText.setFillColor(sf::Color::Yellow);
    labelGameStatusText.setPosition(sf::Vector2f(maxX+70 , maxY-185));


    buttonGameTexture.loadFromFile( appGlobalPath "assets/icon-button.png");
    buttonGame.setTexture(buttonGameTexture);
    buttonGame.setPosition(sf::Vector2f(maxX+75 , maxY-100));

    labelButton.setFont(scoreLabelFont);
    labelButton.setString("Play");
    labelButton.setCharacterSize(45);
    labelButton.setFillColor(sf::Color::Cyan);
    labelButton.setPosition(sf::Vector2f(maxX+90 , maxY-80));
}

void init()
{
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\tvoid init()\t";
  #endif
  #ifdef ENABLE_DEBUG
  std::cout << "maxY=" << maxY  << " maxX=" << maxX << "\nTEXTURESIZE=" << TEXTURESIZE <<  " HALFTEXTURE="<<HALFTEXTURE << "\n\n\n";
  #endif


  for(int i=0; i<CELLCOUNT; i++)
  {
      tictactoeTextures[i].loadFromFile(appGlobalPath "assets/icon-question.png");


      #ifdef ENABLE_DEBUG
      sf::Vector2u sizePeice = tictactoeTextures[0].getSize();
      std::cout << "sizePeice.x= " << sizePeice.x << " sizePeice.y= " << sizePeice.y << std::endl;
      #endif

      tictactoeSprites[i].setTexture(tictactoeTextures[i]);
      switch (i)
      {
        case 0: tictactoeSprites[i].setPosition(minX,minY);break;
        case 1: tictactoeSprites[i].setPosition(centerX-HALFTEXTURE,minY);break;
        case 2: tictactoeSprites[i].setPosition(maxX-TEXTURESIZE,minY);break;
        case 3: tictactoeSprites[i].setPosition(minX,centerY-HALFTEXTURE);break;
        case 4: tictactoeSprites[i].setPosition(centerX-HALFTEXTURE,centerY-HALFTEXTURE);break;
        case 5: tictactoeSprites[i].setPosition(maxX-TEXTURESIZE,centerY-HALFTEXTURE);break;
        case 6: tictactoeSprites[i].setPosition(minX,maxY-TEXTURESIZE);break;
        case 7: tictactoeSprites[i].setPosition(centerX-HALFTEXTURE,maxY-TEXTURESIZE);break;
        case 8: tictactoeSprites[i].setPosition(maxX-TEXTURESIZE,maxY-TEXTURESIZE);break;
        defualt: std::cout << "invalid value (i) set position to sprite\n"; break;
      }

      #ifdef ENABLE_DEBUG
      sf::Vector2f temp_pos = tictactoeSprites[i].getPosition();
      std::cout << "i=" << i << " pos.x=" << temp_pos.x << " pos.y=" << temp_pos.y << std::endl;
      #endif
  }

  initLabels();

}

void draw()
{
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\tvoid draw()\t";
  #endif
  window.draw(bgSprite);
  window.draw(buttonGame);

  //LABELS
  window.draw(scoreLabelText);
  window.draw(scoreText);
  window.draw(labelGameStatusText);
  window.draw(labelButton);


  for(int i=0; i<CELLCOUNT; i++)
      window.draw(tictactoeSprites[i]);

}


int inputs() //return -1 means nothing clicked. else return the cell/sprite clicked.
{
  // #ifdef ENABLE_FUNCTION_CALLS
  // cout <<"(in)";
  // #endif
  sf::Event event;
  while(window.pollEvent(event))
  {
    if(event.type == sf::Event::MouseButtonPressed )
    {
      sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

      for(int i=0; i<CELLCOUNT; i++)
      {
        bounds[i] = tictactoeSprites[i].getGlobalBounds();
        if(bounds[i].contains(mousePosition))
        {
          std::cout<<"\t\tmouse is clicked on sprite i=" << i <<  "+1"<< std::endl;
          return i+1; //becase of the game.move() recive value in range 1 to 9
        }

      }

      #ifdef  ENABLE_DEBUG
      std::cout << "Mouse Left Button Pressed\n";
      std::cout << "mouse pos  =" << mousePosition.x  << " y=" << mousePosition.y << "\n";
      #endif
    }
  }
  return -1;

}

void resetGame(bool&gmEnd,tttgame &obj)//bool&pTurn,bool&cTurn,
{
  // pTurn=false;
  // cTurn=true;
  gmEnd=false;
  roundCounter=0;//global variable


  //reset textures
  for(int i=0; i<CELLCOUNT; i++)
  {
      tictactoeTextures[i].loadFromFile(appGlobalPath "assets/icon-question.png");
      tictactoeSprites[i].setTexture(tictactoeTextures[i]);
  }

  obj.resetGame();
  labelGameStatusText.setString("Game");
}

int main()
{
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\t int main()\t";
  #endif
  window.setFramerateLimit(60);
	init();

  tttgame game(playerId,computerId); //set ids , set def value to x,y,z rows
  bool playerTurn = false , computerTurn = true;
  bool gameEnd = false;

  while(window.isOpen())
  	{
      //--- BELOW CODES ARE COMMENTED AND RIGHT NOW COMPUTER IS FIRST PLAYER LATER CHANGE THIS CODE WITH AN EVENT FROM UI
      /*
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
      */
      if(!gameEnd)
      {
              cout << "\n\n\n"<<endl;
              if(game.getRoundCounter()<=9)
              {
                  if(playerTurn && !computerTurn)
                  {
                      std::cout<<"player turn to move.\n";
                      // labelGameStatusText.setString("Player Turn");
                      // game.playerMove();
                      int temp_playerMoveCell = inputs();
                      #ifdef ENABLE_DEBUG
                      // cout << "temp_playerMoveCell = " << temp_playerMoveCell << endl;
                      #endif
                      while(temp_playerMoveCell==-1)
                      {
                        // cout << "no/invalid place choosen by player\n";
                        temp_playerMoveCell = inputs();
                        #ifdef ENABLE_DEBUG
                        // cout << "**temp_playerMoveCell = " << temp_playerMoveCell << endl;
                        #endif
                      }


                      if(game.move(playerId,temp_playerMoveCell)==-1)
                      {
                          cout << "PLAYER MOVE REJECTED.\n";
                      }
                      else
                      {
                        //player move accpeted apply into Graphics
                        //temp_playerMoveCell minus one because of position ui isnt match with matrixes
                        tictactoeTextures[temp_playerMoveCell-1].loadFromFile(appGlobalPath "assets/icon-x.png");
                        tictactoeSprites[temp_playerMoveCell-1].setTexture(tictactoeTextures[temp_playerMoveCell-1]);
                        cout << "player move applied to ui cellid-1=" << temp_playerMoveCell-1 << endl;
                        #ifdef ENABLE_DEBUG
                        cout << "temp_playerMoveCell-1 = " << temp_playerMoveCell-1 << endl;
                        #endif
                      }
                      playerTurn = false;
                      computerTurn = true;
                  }
                  else if(computerTurn && !playerTurn)
                  {
                      std::cout<<"computer turn to move.\n";
                      // labelGameStatusText.setString("Computer Turn");
                      const int temp_computerMoveCell = game.computerMove();
                      #ifdef ENABLE_DEBUG
                      cout << "temp_computerMoveCell-1 = " << temp_computerMoveCell-1 << endl;
                      #endif
                      if(temp_computerMoveCell==-1)
                      {
                        cout << "COMPUTER MOVE REJECTED/HAS PROBLEM.\n";
                      }
                      else
                      {
                        //computer move accpeted apply into Graphics
                        //temp_playerMoveCell minus one because of position ui isnt match with matrixes
                        tictactoeTextures[temp_computerMoveCell-1].loadFromFile(appGlobalPath "assets/icon-o.png");
                        tictactoeSprites[temp_computerMoveCell-1].setTexture(tictactoeTextures[temp_computerMoveCell-1]);
                        cout << "computer move applied to ui cellid-1=" << temp_computerMoveCell-1 << endl;
                        #ifdef ENABLE_DEBUG
                        cout << "temp_computerMoveCell-1 = " << temp_computerMoveCell-1 << endl;
                        #endif
                      }
                      computerTurn = false;
                      playerTurn = true;
                  }
                  else
                      cout << "problem in manage turns with flags." << endl;
              }
              else
              {
                  cout <<"game end?" << endl;
                  gameEnd =true;
                  const int gameRes = game.gameResultCheck();
                  if(gameRes==playerId)
                  {
                    labelGameStatusText.setString("Player\nWon");
                    game.playerScore++;
                  }

                  else if(gameRes==computerId)
                  {
                    labelGameStatusText.setString("Computer\nWon");
                    game.computerScore++;
                  }

                  else
                  {
                    labelGameStatusText.setString("Draw");
                    cout << "unknown game status.. result code = " << gameRes << endl;
                  }


                  //update scoreboard
                  scoreText.setString("Pc : " + to_string(game.computerScore) + " PL : "+ to_string(game.playerScore));


              }

      }
      else
      {

        sf::Event event;
        while(window.pollEvent(event))
        {
          if(event.type == sf::Event::MouseButtonPressed )
          {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

              buttonBound = buttonGame.getGlobalBounds();
              if(buttonBound.contains(mousePosition) && gameEnd)
              {
                std::cout<<"START AGAIN . mouse is clicked on button game when game is end."<< std::endl;
                resetGame(gameEnd,game);
              }

          }
        }

      }


  		//render things
  		window.clear(sf::Color::Black);
  		draw();
  		window.display();
  	}

  return 0;
}
