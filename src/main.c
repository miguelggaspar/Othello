/**
 *      @file  main.c
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
#define _MAIN_C_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "myf.h"
#define BUFFER_SIZE 100
/**
 * @brief
 * @param  argc - number of arguments
 * @param  argv - array containing arguments
 * @return
 */
int main(int argc, char const *argv[]) {
        othello jg;
        othello *game= &jg;
        game=malloc(sizeof(othello));

        int move;
        char *filename;
        filename = malloc(sizeof(char));
        game->vez=1;
        directions dir;

        IplImage *tabuleiro = cvCreateImage(cvSize(LA, ALT), IPL_DEPTH_8U, 3);
        cvZero(tabuleiro);      //force initial image to black, otherwise value unknown
        cvNamedWindow(NAME_IMG_TAB, CV_WINDOW_AUTOSIZE);
        char key;

        while (AskForGameMode()) ;            // Asks user to choose game play mode

        InitDisplay(tabuleiro);
        InitGame( game );
        PrintGameBoard(game);
        InitDisplay(tabuleiro);
        PrintHelp();

        //PrintValidMoves(game,&dir);
        PrintValidMoves(game,&dir,tabuleiro);

        cvSetMouseCallback(NAME_IMG_TAB, myActionOnMouseClick, (void *) tabuleiro);

        while(1)    //Create infinite loop for live viewing
        {
                cvShowImage(NAME_IMG_TAB, tabuleiro);
                key = cvWaitKey(5);



                do // loop for game
                {
                      //  PrintValidMoves(game,&dir,tabuleiro);
                        cvShowImage(NAME_IMG_TAB, tabuleiro);
                        key = cvWaitKey(5); //Capture Keyboard stroke
                        UpdateDisplay(game,tabuleiro);

                        do // loop until valid user play
                        {

                                cvShowImage(NAME_IMG_TAB, tabuleiro);
                                key = cvWaitKey(5); //Capture Keyboard stroke
                                UpdateDisplay(game,tabuleiro);

                                if (GAMEMODE_FLAG==1) newMove=GetPlayerMove();  // If terminal based game were choosen

                                if (LOAD_FLAG) {
                                        newMove=150;
                                        LOAD_FLAG=0; // Clear flag
                                }

                                if (SAVE_FLAG) {
                                        newMove=100;
                                        SAVE_FLAG=0; // Clear flag
                                }

                                if (SKIP_FLAG) {
                                        newMove=200;
                                        SKIP_FLAG=0; // Clear flag
                                }


                                switch (newMove) {
                                case 100:
                                        printf("\nType a file name to save: ");
                                        scanf("%s",filename);
                                        newMove=SaveGame(game,filename);
                                        break;
                                case 150:
                                        printf("\nType a file name to load: ");
                                        scanf("%s",filename);
                                        newMove=LoadGame(game,filename);
                                        ClearValidMoves(game);
                                        PrintValidMoves(game,&dir,tabuleiro);
                                        UpdateDisplay(game,tabuleiro);
                                        break;
                                case 250:
                                        PrintHelp();
                                        break;
                                case 200:
                                        skipcount[0]=1;
                                }

                                //  printf("\tmove -> %d\tcheckmove flag -> %d\tVez -> %d \n ",move,dir.flag,game->vez);
                                //printf("TOU AQUI\n" );
                        } while( !CheckMove( game, newMove, &dir));
                        printf("User Move -- %d\n",newMove);

                        key = cvWaitKey(5); //Capture Keyboard stroke

                        if (newMove!=200) {                          //condition to skip a play
                                ReversePieces(game,newMove,&dir);
                                skipcount[0]=0;
                                memset(&newMove, 0,sizeof(int));
                        } else {
                          skipcount[0]=1;
                          memset(&newMove, 0,sizeof(int));
                        }
                        UpdateDisplay(game,tabuleiro);
                        ClearValidMoves(game);                  // clear valid move's marks
                        game->vez=2;                            // change  player
                        memset(&dir, 0,sizeof(directions));
                        PrintValidMoves(game,&dir,tabuleiro);
                        //cvShowImage(NAME_IMG_TAB, tabuleiro);
                        if ( WinGame(game) ) break;  // break if user won

                        do // loop until valid computer play
                        {

                                move=GenerateMove(game);

                        } while( !CheckMove(game, move,&dir));
                        printf("computer Move -- %d\n",move);


                        if (move!=200) {                       //condition to skip a play
                                ReversePieces(game,move,&dir);
                                skipcount[1]=0;
                        }

                        ClearValidMoves(game);
                        game->vez=1;
                        memset(&dir, 0,sizeof(directions));
                        PrintValidMoves( game, &dir,tabuleiro);

                } while( !WinGame( game )); // break loop if computer won

                printf("TOU FORA DO JOGO\n");

                break;
        }
        printf("SAI DO LOOP WINDOW\n");
        cvReleaseImage(&tabuleiro);                            //Release image (free pointer when no longer used).
        cvDestroyWindow(NAME_IMG_TAB);
        PrintGameBoard(game);
        free(filename);
        free(game);

        return 0;

}
