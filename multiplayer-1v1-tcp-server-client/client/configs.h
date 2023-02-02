#ifndef GAURD_CONFIGS_H
#define GAURD_CONFIGS_H

#define appGlobalPath "/home/mrx/Documents/tic-tac-teo-game/multiplayer-1v1-tcp-server-client/client/"

//flag for debug prints
// #define ENABLE_DEBUG


#define ENABLE_FUNCTION_CALLS
#define TEXTURESIZE 100
#define HALFTEXTURE TEXTURESIZE/2

//for easy controll 2x for loop (default value is 9)
#define CELLCOUNT 9

#define PLAYER_ID 1 //will use alawys
#define PLAYER2_ID 2 //will use when ifdef pvp_on


/*will use when ifndef pvp_on, computer id is not 3 bc of bug, i must be 4 not 3
in main.cpp -> pvc -> when chekcing output gameResultCheck() , that function will reutnr code 3 when
game is draw and computer id = 3 so it will make the computer winner even when game is draw*/
#define COMPUTER_ID 4




#endif
