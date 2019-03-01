/**
 *      @file  myf.h
 *      @brief  Programa Principal
 *
 * Descrição mais detalhada do ficheiro
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  26-Oct-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 ***************************************************
 */
 #include <cv.h>
 #include <highgui.h>

#define YES 1
#define NO 0
//#include <curses.h>
#define VAZIO ' '
#define JOGADOR1 'O'
#define JOGADOR2 'X'
#define VALIDMOVE '~'
#define LA 550
#define ALT 450

typedef char celula;
typedef struct {
        celula T[8][8];  // Array bidimensional [8][8] com o estado das células
        int vez;         // inteiro que designa quem é a vez do próximo a jogar (1-jogador1, 2-jogador2)
        int terminado;   // inteiro que indica se o jogo está terminado (1 se sim , 0 se não )
        } othello;

typedef struct{
        int up;
        int down;
        int left;
        int right;
        int upright;
        int upleft;
        int downright;
        int downleft;
        int flag;
} directions;

#ifdef _MAIN_C_
int skipcount[2]={0,0};
IplImage *src_imageG = 0, *dst_imageG = 0;
int escapeG = 0;
int newMove=0;
int MOVE_FLAG=0;
int LOAD_FLAG=0;
int SAVE_FLAG=0;
int SKIP_FLAG=0;
int GAMEMODE_FLAG=0;
#else
extern int MOVE_FLAG;
extern int LOAD_FLAG;
extern int SAVE_FLAG;
extern int SKIP_FLAG;
extern int GAMEMODE_FLAG;
extern IplImage *src_imageG, *dst_imageG;
extern int escapeG;
extern int skipcount[2];
extern int newMove;
#endif

#define NAME_IMG_TAB "Othello - Reversi"

#include "prototypes.h"
