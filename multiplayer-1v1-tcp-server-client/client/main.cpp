#include "tttgame.h"
bool pvpMode= false;

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


    if(pvpMode)
      scoreText.setString("p1(x) : 0\np2(o) : 0");
    else
      scoreText.setString("Pc(o) : 0\nPL(x) : 0");

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

void createMainManuButton(sf::Texture &texture,sf::Sprite &sprite,sf::Text &text,sf::Font &allFont,std::string buttonText,sf::Color textColor,sf::Vector2f pos,int chsize=30)
{

  sprite.setTexture(texture);
  sprite.setPosition(pos);

  //make pos to a bit center of button
  pos.x += 25;
  pos.y += 25;
  text.setFont(allFont);
  text.setString(buttonText);
  text.setCharacterSize(30);
  text.setFillColor(textColor);
  text.setPosition(pos);
}

int mainMenu()//return 0 means exit. 1 means pvc. 2 means pvp
{
  //load bg
  sf::Sprite bgMainMenuSprite;
  sf::Texture bgMainMenuTexture;
  bgMainMenuTexture.loadFromFile(appGlobalPath "assets/background-main-menu.jpeg");
  bgMainMenuSprite.setTexture(bgMainMenuTexture);


  //style for all buttons
  sf::Texture buttonStyleTexture;
  buttonStyleTexture.loadFromFile( appGlobalPath "assets/icon-button.png");
  sf::Font labelsFont;
  labelsFont.loadFromFile(appGlobalPath "assets/fonts/arial.ttf");



  //button pvp
  sf::FloatRect buttonPvpBound;
  sf::Text labelButtonPvp;
  sf::Sprite buttonPvpSprite;
  createMainManuButton(buttonStyleTexture,buttonPvpSprite,labelButtonPvp,labelsFont,"PvP",sf::Color::Yellow,sf::Vector2f(centerX+80 , centerY-80),35);


  //button pvc
  sf::FloatRect buttonPvcBound;
  sf::Text labelButtonPvc;
  sf::Sprite buttonPvcSprite;
  createMainManuButton(buttonStyleTexture,buttonPvcSprite,labelButtonPvc,labelsFont,"PvC",sf::Color::Green,sf::Vector2f(centerX+80 , centerY),35);


  //button quit
  sf::FloatRect buttonQuitBound;
  sf::Text labelButtonQuit;
  sf::Sprite buttonQuitSprite;
  createMainManuButton(buttonStyleTexture,buttonQuitSprite,labelButtonQuit,labelsFont,"Quit",sf::Color::Red,sf::Vector2f(centerX+80 , centerY+80),35);


  while(window.isOpen())
  {

    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::MouseButtonPressed )
      {
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

          buttonQuitBound = buttonQuitSprite.getGlobalBounds();
          if(buttonQuitBound.contains(mousePosition))
          {
            std::cout<<"quit the game."<< std::endl;
            return 0;
          }

          buttonPvcBound = buttonPvcSprite.getGlobalBounds();
          if(buttonPvcBound.contains(mousePosition))
          {
            std::cout<<"pvc clicked."<< std::endl;
            return 1;
          }

          buttonPvpBound = buttonPvpSprite.getGlobalBounds();
          if(buttonPvpBound.contains(mousePosition))
          {
            std::cout<<"pvp clicked."<< std::endl;
            return 2;
          }


      }
    }
    //clear
    window.clear(sf::Color::Black);

    //draw background main menu
    window.draw(bgMainMenuSprite);

    //draw menu buttons
    window.draw(buttonPvpSprite);
    window.draw(labelButtonPvp);

    window.draw(buttonPvcSprite);
    window.draw(labelButtonPvc);

    window.draw(buttonQuitSprite);
    window.draw(labelButtonQuit);



    //display
    window.display();
  }


  // init(); //init labels and game board things
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
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\t resetGame(bool&gmEnd,tttgame &obj)\t";
  #endif
  gmEnd=false;

  //reset textures
  for(int i=0; i<CELLCOUNT; i++)
  {
      tictactoeTextures[i].loadFromFile(appGlobalPath "assets/icon-question.png");
      tictactoeSprites[i].setTexture(tictactoeTextures[i]);
  }

  obj.resetGame();
  labelGameStatusText.setString("Game\nrestarted");
}



void pvc(tttgame &game,bool &playerTurn,bool &computerTurn,bool &gameEnd) //player versus computer
{

    while(window.isOpen())
    	{
        //--- BELOW CODES ARE COMMENTED AND RIGHT NOW COMPUTER IS FIRST PLAYER LATER CHANGE THIS CODE WITH AN EVENT FROM UI
        /*
        cout << "do you want player first? y/n: ";
        char wannaPlayFirst;
        cin >> wannaPlayFirst;
        if(wannaPlayFirst == 'y' || wannaPlayFirst == 'Y')
        {
            PLAYER_ID=1;
            COMPUTER_ID=2;
            playerTurn = true;
            computerTurn = false;
        }
        */
        if(!gameEnd)
        {
                cout << "\n\n\n game!end"<<endl;
                if(game.getRoundCounter()<=9)
                {
                    if(playerTurn && !computerTurn)
                    {
                        std::cout<<"player turn to move.\n";
                        // labelGameStatusText.setString("Player Turn");
                        // game.playerMove();
                        int temp_playerMoveCell = inputs();
                        #ifdef ENABLE_DEBUG
                        cout << "temp_playerMoveCell = " << temp_playerMoveCell << endl;
                        #endif
                        while(temp_playerMoveCell==-1)
                        {
                          // cout << "no/invalid place choosen by player\n";
                          temp_playerMoveCell = inputs();
                          #ifdef ENABLE_DEBUG
                          cout << "**temp_playerMoveCell = " << temp_playerMoveCell << endl;
                          #endif
                        }


                        if(game.move(PLAYER_ID,temp_playerMoveCell)==-1)
                        {
                            cout << "PLAYER MOVE REJECTED.\n";
                            cout << "player please enter aviable cell. ur turn again..."<<endl;
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
                          playerTurn = false;
                          computerTurn = true;
                        }

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
                    cout <<"game end? but sounds like cells are full." << endl;
                    gameEnd =true;
                    const int gameRes = game.gameResultCheck();
                    cout << "gameRes=  " << gameRes << endl;
                    cout << "playerid = " << PLAYER_ID << endl;
                    cout << "computerID= " << COMPUTER_ID << endl;

                    switch(gameRes)
                    {
                      case PLAYER_ID:
                      {
                        labelGameStatusText.setString("Player\nWowwwwwwwwwwwwn");
                        game.playerScore++;
                      }break;
                      case COMPUTER_ID:
                      {
                        labelGameStatusText.setString("Computer\nWonwwwwwwwwwwwwww");
                        game.computerScore++;
                      }break;
                      default:
                      {
                        labelGameStatusText.setString("Draw?");
                        cout << "result code = " << gameRes  << " = (game is draw)"<< endl;
                      }break;
                    }


                    //update scoreboard
                    scoreText.setString("Pc(o): " + to_string(game.computerScore) + "\nPL(x) : "+ to_string(game.playerScore));
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
                  // game.
                }

            }
          }

        }


    		//render things
    		window.clear(sf::Color::Black);
    		draw();
    		window.display();
    	}
}



void pvp(tttgame &game,bool &playerTurn,bool &player2Turn,bool &gameEnd) //player versus player
{

    while(window.isOpen())
    	{
        if(!gameEnd)
        {
                cout << "\n\n\n game is not end."<<endl;
                if(game.getRoundCounter()<=9)
                {
                    if(playerTurn && !player2Turn)
                    {
                        std::cout<<"player1 (x) turn to move.\n";
                        labelGameStatusText.setString("p1 (x) Turns");
                        // game.playerMove();
                        int temp_playerMoveCell = inputs();

                        #ifdef ENABLE_DEBUG
                        cout << "temp_playerMoveCell = " << temp_playerMoveCell << endl;
                        #endif


                        if(game.move(PLAYER_ID,temp_playerMoveCell)==-1)
                        {
                            cout << "player1 MOVE REJECTED.\n";
                            cout << "player1 please enter aviable cell. ur turn again..."<<endl;
                        }
                        else
                        {
                          //player move accpeted apply into Graphics and console game
                          //temp_playerMoveCell minus one because of position ui isnt match with matrixes
                          tictactoeTextures[temp_playerMoveCell-1].loadFromFile(appGlobalPath "assets/icon-x.png");
                          tictactoeSprites[temp_playerMoveCell-1].setTexture(tictactoeTextures[temp_playerMoveCell-1]);
                          cout << "player1 move applied to ui cellid-1=" << temp_playerMoveCell-1 << endl;


                          #ifdef ENABLE_DEBUG
                          cout << "temp_playerMoveCell-1 = " << temp_playerMoveCell-1 << endl;
                          #endif


                          playerTurn = false;
                          player2Turn = true;
                        }

                    }
                    else if(player2Turn && !playerTurn)
                    {
                        std::cout<<"player2 (o) turn to move.\n";
                        labelGameStatusText.setString("p2 (o) Turns");
                        int temp_player2MoveCell = inputs();


                        #ifdef ENABLE_DEBUG
                        cout << "temp_player2MoveCell-1 = " << temp_player2MoveCell-1 << endl;
                        #endif



                        if(game.move(PLAYER2_ID,temp_player2MoveCell)==-1)
                        {
                          cout << "player2 MOVE REJECTED/HAS PROBLEM.\n";
                        }
                        else
                        {
                          //player move accpeted apply into Graphics and console game
                          //temp_playerMoveCell minus one because of position ui isnt match with matrixes
                          tictactoeTextures[temp_player2MoveCell-1].loadFromFile(appGlobalPath "assets/icon-o.png");
                          tictactoeSprites[temp_player2MoveCell-1].setTexture(tictactoeTextures[temp_player2MoveCell-1]);
                          cout << "player2 move applied to ui cellid-1=" << temp_player2MoveCell-1 << endl;


                          #ifdef ENABLE_DEBUG
                          cout << "temp_player2MoveCell-1 = " << temp_player2MoveCell-1 << endl;
                          #endif


                          player2Turn = false;
                          playerTurn = true;
                        }

                    }
                    else
                        cout << "problem in manage turns with flags." << endl;
                }
                else
                {
                    cout <<"sounds like cells are full, game end." << endl;
                    gameEnd =true;
                    const int gameRes = game.gameResultCheck();
                    cout << "gameRes code= " << gameRes << endl;
                    switch(gameRes)
                    {
                      case PLAYER_ID:
                      {
                        labelGameStatusText.setString("P1 (x)\nWon");
                        game.playerScore++;
                      }break;
                      case PLAYER2_ID:
                      {
                        labelGameStatusText.setString("p2 (o)\nWon");
                        game.player2Score++;
                      }break;
                      default:
                      {
                        labelGameStatusText.setString("Draw");
                        cout << "result code = " << gameRes  << " = (game is draw)"<< endl;
                      }break;
                    }

                    //restart the game.
                    // resetGame(gameEnd,game);

                    //update scoreboard
                    scoreText.setString("P1(x) : " + to_string(game.playerScore) + "\nP2(o) : "+ to_string(game.player2Score));
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
                  // game.
                }

            }
          }

        }


    		//render things
    		window.clear(sf::Color::Black);
    		draw();
    		window.display();
    	}
}





int main()
{
  #ifdef ENABLE_FUNCTION_CALLS
  cout <<"\t\t\t int main()\t";
  #endif
  window.setFramerateLimit(60);
  const short int resultMenu = mainMenu(); //return 1 means pvc. 2 -> pvp, 0 -> exit
  cout << "res menu = " << resultMenu << endl;
  bool gameEnd = false;

  switch(resultMenu)
  {
    case 0:
      return 0; //same exit(0)
    case 1:
    {
      //player versus computer
      pvpMode=false;//must be top of init();, in init we use this pvpMode
      init();
      cout << "pvp is off" << endl;
      tttgame game(PLAYER_ID,COMPUTER_ID); //set ids , set def value to x,y,z rows
      bool playerTurn = false , computerTurn = true;
      pvc(game,playerTurn,computerTurn,gameEnd);
    }break;
    case 2:
    {
      //player versus player
      pvpMode=true;//must be top of init();, in init we use this pvpMode
      init();
      cout<< "pvp is on" << endl;
      tttgame game(PLAYER_ID,PLAYER2_ID);
      bool playerTurn = true , player2Turn = false;
      pvp(game,playerTurn,player2Turn,gameEnd);
    }break;

    default:
      cout << "unknown result code for manu so lets play game as defualt settings." << endl;
      break;
  }





  return 0;
}
