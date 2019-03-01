/**
 *      @file  myf.c
 *      @brief  Programa Principal
 *
 * Descrição mais detalhada do ficheiro
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  30-Oct-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 ***************************************************
 */

#include "myf.h"
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "pcolor.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>
/**
 * @brief  This function Prints Game Board Othello
 *
 * @param  t[8][8] array with 8x8 dimension
 * @return none
 */
void PrintGameBoard(othello *jg)
{

								printf("     a   b   c   d   e   f   g   h  \n");
								printf("   +---+---+---+---+---+---+---+---+  \n");
								for (int i = 0; i < 8; i++)
								{
																printf(" %d |",i+1);
																for (int j = 0; j < 8; j++)
																{

																								if (jg->T[i][j]=='X')
																								{
																																textcolor(RESET, BLUE, WHITE);
																								}

																								if (jg->T[i][j]=='O')
																								{
																																textcolor(RESET, RED, WHITE);
																								}

																								printf(" %c ",jg->T[i][j]);
																								ResetTextColors();
																								printf("|");
																}
																printf(" %d \n",i+1);
																printf("   +---+---+---+---+---+---+---+---+  \n");
								}

								printf("     a   b   c   d   e   f   g   h    \n");
								printf("PLAYER->%d\n",jg->vez);


}

/**
 * @brief  This function
 *
 * @param  none
 * @return none
 */
int AskForGameMode() {
	char *gamemode;
	gamemode = malloc(sizeof(char));

	printf("Choosing Game Mode, press one of the following key and then press ENTER\n\n");
	printf("	 1 - Terminal Based Game, in this mode, you have to make your play in coordinates form\n");
	printf("	 2 - Window Based Game, in this mode you make your move clicking on the displayed Board\n");

	scanf("%s",gamemode);													//Waits for

	switch (gamemode[0]) {
		case '1': GAMEMODE_FLAG=1; break;						// Terminal Based Game
		case '2': GAMEMODE_FLAG=2; break;						// Window Based Game
		default : free(gamemode); return 1;
	}

free(gamemode);
return 0;

}


/**
 * @brief  This function fills Game
 *
 * @param  *jg
 * @return none
 */
void InitGame( othello *jg)    // todas as céluas a VAZIO exceto as 4 centrais
{

								for (int i = 0; i < 8; i++)
																for (int j = 0; j < 8; j++)
																								jg->T[i][j] = VAZIO;

								jg->T[3][3] = JOGADOR1;
								jg->T[4][4] = JOGADOR1;
								jg->T[3][4] = JOGADOR2;
								jg->T[4][3] = JOGADOR2;
}

/**
 * @brief  This function Prints Help
 *
 * @param  none
 * @return none
 */
void PrintHelp()
{
								printf("\nCommand List\n");
								printf("a1 until h8  -> Position Moves\n");
								printf("s  -> save (save the current game to a file with a default name)\n");
								printf("l  -> load (loads a pre-saved game into a file with a default name)\n");
								printf("z  -> jump move)\n");
								printf("\nPress ENTER to continue\n");

}

/**
 * @brief  This Gets Player move
 *
 * @param  none
 * @return move - Player decision
 */
int GetPlayerMove()
{
								char *str;
								str = malloc(sizeof(char));
								scanf("%s",str);
								printf("%s",str);
								char A[8]={'a','b','c','d','e','f','g','h'};
								char B[8]={'1','2','3','4','5','6','7','8'};
								int x=0;
								int y=0;

								for (int i = 0; i < 8; i++)
								{


																if (str[0] == A[i])
																{
																								x = i+1;
																}

																if (str[0] == B[i])
																{
																								y = i+1;
																}

																if (str[0] == 's')
																{
																								x = 10;
																								y = 0;
																}

																if (str[0] == 'l')
																{
																								x = 15;
																								y = 0;
																}

																if (str[0] == 'z')
																{
																								x = 20;
																								y = 0;
																}

																if (str[0] == 'p') {

																								x = 25;
																								y = 0;
																}

								}

								for (int j = 0; j < 8; j++) {
																if (str[1] == B[j])
																								y = j+1;
																else if (str[1] == A[j])
																								x = j+1;
								}

								int move = x*10+y;
								free(str);
								return move;

}

/**
 * @brief This Function saves game board data in File
 *
 * @param  jg - Game Board Data
 * @param  filename - file's name to save Game Board Data
 * @return
 */
int SaveGame(othello *jg, char *filename)
{


								FILE *fp = fopen(filename, "w");

								for(int l = 0; l<8; l++)
								{
																for(int c = 0; c<8; c++)
																{
																								if(c != 7) fprintf(fp, "%c,", jg->T[l][c]);
																								else fprintf(fp, "%c\n", jg->T[l][c]);
																}
								}

								fprintf(fp, "%d,\n", jg->vez);
								fclose(fp);
								return 1;
}

/**
 * @brief This Function loads game board data from file
 *
 * @param  jg - Game Board Data
 * @param  filename - file's name to load Game Board Data
 * @return
 */
int LoadGame( othello *game, char *filename)
{
								FILE *fp = fopen(filename, "r");
								if (!fp) return 2;

								int flag;
								char buffer[100];
								int lin = 0;

								while (fgets(buffer, 100, fp))

								{
																if (lin==8)
																								flag = 0;  // Fill game->vez
																else
																								flag = 1;  // Fill game->T

																FillOtelloStruct(buffer,game,lin,flag);
																lin++;

								}

								fclose(fp);
								return 1;
}

/**
 * @brief This function Fills the othello struct
 *
 * @param  othello - Game Board Data
 * @param
 * @return
 */
void FillOtelloStruct ( char *str, othello *jg, int lin,int flag)
{
								int col = 0;
								char *token = strtok(str, ",");

								while( token != NULL )
								{
																if (flag==0)
																{
																								jg->vez=*token-'0';
																								token = strtok( NULL, "," );
																								return;
																}
																else
																{
																								jg->T[lin][col]=*token;
																								col++;
																								token = strtok( NULL, "," );
																}
								}
								return;
}


/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
int CheckMove( othello *jg, int move, directions *dir)
{
								//directions *dir;
								//dir=malloc(sizeof(directions));
								//printf("%d\n",move);
								switch (move) {
								case 100:
												return 0;
								case 150:
												return 0;
								case 200:
												return 1;
								case 250:
												return 0;
								}

								NeighborOpponent(jg,move,dir);
								//printf("\tmove -> %d\tcheckmove flag -> %d \n ",move,dir->flag);

								if (dir->flag>0) {
																return 1;
								} else {
																return 0;
								}

}

/**
 * @brief  void
 *
 * @param  jg   game board
 * @param  jg   game board
 * @return none
 */
void PrintValidMoves(othello *jg,directions *dir,IplImage *tabuleiro) {
								othello gametemp=*jg;
								int move;
								for (int i = 0; i < 8; i++) {
																for (int j = 0; j < 8; j++) {
																								move=(j+1)*10+i+1;
																	//							printf("My move -> %d",move);
																								if (CheckMove(jg, move,dir) && jg->T[i][j]==' ')  {

																																gametemp.T[i][j]='~';
																																DrawPiece(tabuleiro, i+1, j+1, VALIDMOVE);
																		//printf("\n");

																			//						printf("\n");
																								}
																}
								}
								*jg=gametemp;
							PrintGameBoard(jg);

								memset(dir, 0, sizeof(directions));
}

/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
int WinGame(othello *jg){
	int count=0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
				if (jg->T[i][j]=='~'){
					count++;
				}
		}
	}
	if (jg->vez==2 && count == 0){
		skipcount[1]=1;																		// Computer skip play
		printf("Player 2 -- %d\n",skipcount[1]);
		if (skipcount[0]==1) {														// check if there are no more possible moves
				CheckWin(jg);
				return 1;
		}
		printf("Player 1 -- %d\n",skipcount[0]);
		return 0;
	}
	if (jg->vez==1 && count == 0){
		skipcount[0]=1;																		// User skip play
		printf("Player 1 -- %d\n",skipcount[0]);

		if (skipcount[1]==1) {					// check if there are no more possible moves
				CheckWin(jg);
				return 1;
		}
		printf("Player 2 -- %d\n",skipcount[1]);
		return 0;
	}
	return 0;
}

/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
void CheckWin(othello *jg) {
	int jogador1count=0;
	int jogador2count=0;
	printf("TOU NO CHECKWIN\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
				if (jg->T[i][j]==JOGADOR1) jogador1count++;
				if (jg->T[i][j]==JOGADOR2) jogador2count++;
		}
	}

	if (jogador1count>jogador2count){
		printf("USER WON\n");
	}

	if (jogador1count<jogador2count){
		printf("COMPUTER WON\n");
	}

	if (jogador1count==jogador2count){
		printf("DRAWWW\n");
	}
}

/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
int GenerateMove(othello *jg) {
	int move=0;
	int emptyspaces=0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (jg->T[i][j]=='~') move=(j+1)*10+i+1;
			if (jg->T[i][j]==VAZIO) emptyspaces++;
		}
	}

if (move!=0 && emptyspaces!=0) return move;			//return last possible move
else return 200;							//200 is a flag to pass the play
}

/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
void ClearValidMoves(othello *jg) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (jg->T[i][j]=='~'){jg->T[i][j]=' ';}
		}
	}
}
