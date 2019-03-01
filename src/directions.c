/**
 *      @file  directions.c
 *      @brief  Programa Principal
 *
 * Descrição mais detalhada do ficheiro
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  10-Nov-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 *************************************************** */

#include "myf.h"
#include <stdio.h>
#include <math.h>


/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
int CheckDirection(othello *jg, int place, directions *dir, int Direction){
								int c=floor(place/10)-1;
								int l=place%10-1;
								char Enemy,Mate,aux;
								int enemycount=0,matecount=0,flag=1;
								int dimensionflag=0;

								switch (jg->vez) {
								case 1: Enemy=JOGADOR2;          // if it's player 1 turn
																Mate=JOGADOR1;
																break;
								case 2: Enemy=JOGADOR1;         // if it's player 2 turn
																Mate=JOGADOR2;
																break;
								}

								for (int i = 1; i < 8; i++) {

																switch (Direction) {
																case 1:  aux = jg->T[l-i][c-i];       // upleft
																								if (l-i < 0 || c-i < 0) {dimensionflag++; }
																								break;
																case 2:  aux = jg->T[l][c-i];       // left
																								if (c-i < 0) {dimensionflag++; }
																								break;
																case 3:  aux = jg->T[l+i][c-i];    // downleft
																								if (l+i > 7 || c-i < 0) {dimensionflag++; }
																								break;
																case 4:  aux = jg->T[l-i][c];      // up
																								if (l-i < 0) {dimensionflag++; }
																								break;
																case 5:  aux = jg->T[l+i][c];       // down
																								if (l+i > 7) {dimensionflag++; }
																								break;
																case 6:  aux = jg->T[l-i][c+i];     // upright
																								if (l-i < 0  ||  c+i > 7) {dimensionflag++; }
																								break;
																case 7:  aux = jg->T[l][c+i];      // right
																								if ( c+i > 7) {dimensionflag++; }
																								break;
																case 8:  aux = jg->T[l+i][c+i];     // downright
																								if (l+i > 7  ||  c+i > 7) {dimensionflag++; }
																								break;
																}

																if (dimensionflag!=0) {return 0; }  // if it trys to reach out off bounds

																if (aux==Enemy) {
																								enemycount++;
																								continue;
																}
																if (aux==Mate) {
																								matecount++;
																								break;
																}
																if (aux==' ') {
																								flag=-1;
																								break;
																}
								}
								if (enemycount == 0 || flag == -1 || matecount==0) {   /* if there are no enemy in this range or there is a blank space */
																//printf("\tcount -> %d\tflag -> %d\t",enemycount,flag);
																return 0;                /* invalid direction */
								}
								switch (Direction) {       // Choosing direction to store count
								case 1: dir->upleft = enemycount; break;
								case 2: dir->left = enemycount; break;
								case 3: dir->downleft = enemycount; break;
								case 4: dir->up = enemycount; break;
								case 5: dir->down = enemycount; break;
								case 6: dir->upright = enemycount; break;
								case 7: dir->right = enemycount; break;
								case 8: dir->downright = enemycount; break;
								}
								//printf("\tcount -> %d\t",enemycount);
								return 1;
}



*/
void NeighborOpponent(othello *jg, int place, directions *dir){
								int c=floor(place/10)-1;
								int l=place%10-1;
								dir->flag=0;
								char Enemy,Mate;
								int x,y;
								int direction = 1;

								switch (jg->vez) {
								case 1: Enemy=JOGADOR2; // if it's player 1 turn
												Mate=JOGADOR1;
																break;
								case 2: Enemy=JOGADOR1; // if it's player 2 turn
												Mate=JOGADOR2;
																break;
								}

								for ( y = -1; y <= 1; y++) {
									for ( x = -1; x <= 1; x++) {
										if (!(x == 0 && y == 0)) {	// skip T[l][c]
											if(jg->T[l + x][ c + y] == Enemy && CheckDirection(jg,place, dir, direction)){
												dir->flag++;
											}
											direction++;
										}
									}
								}

								if (jg->T[l][c]==Mate) dir->flag=0;
							}



void ReversePieces(othello *jg,int move,directions *dir) {
								int c=floor(move/10)-1;
								int l=move%10-1;
								int i;
								char Mate;
								switch (jg->vez) {
								case 1: Mate=JOGADOR1;      // if it's player 1 turn
																break;
								case 2: Mate=JOGADOR2;     // if it's player 2 turn
																break;
								}

								jg->T[l][c]=Mate;

								i=1;
								if (dir->upleft>0) {
																do {
																								jg->T[l-i][c-i]=Mate;
																								i++;
																} while(i < (dir->upleft)+1);
								}

								i=1;
								if (dir->left>0) {
																do {
																								jg->T[l][c-i]=Mate;
																								i++;
																} while(i < (dir->left)+1);
								}

								i=1;
								if (dir->downleft>0) {
																do {
																								jg->T[l+i][c-i]=Mate;
																								i++;
																} while(i < (dir->downleft)+1);
								}

								i=1;
								if (dir->up>0) {
																do {
																								jg->T[l-i][c]=Mate;
																								i++;
																} while(i < (dir->up)+1);
								}

								i=1;
								if (dir->down>0) {
																do {
																								jg->T[l+i][c]=Mate;
																								i++;
																} while(i < (dir->down)+1);
								}

								i=1;
								if (dir->upright>0) {
																do {
																								jg->T[l-i][c+i]=Mate;
																								i++;
																} while(i < (dir->upright)+1);

								}

								i=1;
								if (dir->right>0) {
																do {
																								jg->T[l][c+i]=Mate;
																								i++;
																} while(i < (dir->right)+1);
								}

								i=1;
								if (dir->downright>0) {
																do {
																								jg->T[l+i][c+i]=Mate;
																								i++;
																} while(i < (dir->downright)+1);
								}
}
