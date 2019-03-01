/**
 *      @file  display.c
 *      @brief  Programa Principal
 *
 * Descrição mais detalhada do ficheiro
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  27-Sep-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 ***************************************************
 */
 #include "myf.h"
 #include <stdio.h>

/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
void InitDisplay(IplImage *tabuleiro) {


        for(int l = 0; l < 400; l += 400 / 8) {
                cvLine(tabuleiro, cvPoint(0, l), cvPoint(400,l),CV_RGB(255, 255, 255), 1, 8, 0);
                cvLine(tabuleiro, cvPoint(l,0), cvPoint(l,400),CV_RGB(255, 255, 255), 1, 8, 0);


        }
        cvLine(tabuleiro, cvPoint(0,400), cvPoint(400,400),CV_RGB(255, 255, 255), 1, 8, 0);
        cvLine(tabuleiro, cvPoint(400,0), cvPoint(400,400),CV_RGB(255, 255, 255), 1, 8, 0);
        cvLine(tabuleiro, cvPoint(400,400), cvPoint(400,450),CV_RGB(255, 255, 255), 1, 8, 0);

        cvLine(tabuleiro, cvPoint(400,250), cvPoint(550,250),CV_RGB(255, 255, 255), 1, 8, 0);    //rectangle for load button
        cvLine(tabuleiro, cvPoint(400,350), cvPoint(550,350),CV_RGB(255, 255, 255), 1, 8, 0);

        cvLine(tabuleiro, cvPoint(400,50), cvPoint(550,50),CV_RGB(255, 255, 255), 1, 8, 0);    //rectanglue for save button
        cvLine(tabuleiro, cvPoint(400,150), cvPoint(550,150),CV_RGB(255, 255, 255), 1, 8, 0);


        PutText(tabuleiro);

        DrawPiece(tabuleiro, 4, 4, JOGADOR1);
        DrawPiece(tabuleiro, 5, 4, JOGADOR2);
        DrawPiece(tabuleiro, 4, 5, JOGADOR2);
        DrawPiece(tabuleiro, 5, 5, JOGADOR1);
}



void DrawPiece(IplImage * img, int col, int lin, char player)
{
        CvScalar p;                     //a scalar to define a color
        int w = 400/8;           //width of a Cell
        int h = 400/8;                //hight of a cell
        int x = w / 2 + (col - 1) * w;  // center x coordinate of cell
        int y = h / 2 + (lin - 1) * h;                // center y coordinate of cell

        switch (player)
        {
        case JOGADOR1:     //player 1 - RED
                p = CV_RGB(255, 0, 0);
                break;
        case JOGADOR2:     //player 2 - BLUE
                p = CV_RGB(0, 0, 255);
                break;
        case 3:    //player 3 - GREEN
                p = CV_RGB(0, 255, 0);
                break;
        case 4:    //player 4 - YELLOW
                p = CV_RGB(255, 255, 0);
                break;
        case VALIDMOVE:    //player 5 - WHITE
                p = CV_RGB(255, 255, 255);
                break;
        case VAZIO:    //player 5 - BLACK
                p = CV_RGB(0, 0, 0);
                break;

        default:
                return;
        }

        int radius=23;

        if(player==VALIDMOVE) {
                radius=5;
        }

        cvCircle(img, cvPoint(x, y), radius, p, -1, 8, 0);
        //check manual for the argument meanings: http://docs.opencv.org/modules/core/doc/drawing_functions.html
}

/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
void myActionOnMouseClick(int event, int x, int y, int flags, void * param){

        IplImage *img=(IplImage *)param;


        int col =(int)((double)x/400*8)+1;                 //cálculo do pixel da coluna
        int lin =(int)((double)y/400*8)+1;                 //cálculo do pixel da coluna

        if ((flags & CV_EVENT_RBUTTONDOWN) || (flags & CV_EVENT_LBUTTONDOWN)) {
                printf("X - %d  Y - %d col - %d  lin - %d\n",x,y,col,lin);
                newMove = col*10+lin;

                if(col>=9 && col<=11 && lin >= 6 && lin <=7) LOAD_FLAG=1;
                if(col>=9 && col<=11 && lin >= 2 && lin <=3) SAVE_FLAG=1;
                if(col>=1 && col<=8 && lin == 9 ) SKIP_FLAG=1;
        }

        if (col>8 || col<1 || lin>8 || lin<1  ) {
                MOVE_FLAG=1;
        }


        cvShowImage(NAME_IMG_TAB, img); // porquê?
        cvWaitKey(5);
}



/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
void UpdateDisplay(othello *jg, IplImage *tabuleiro) {
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        DrawPiece(tabuleiro,j+1,i+1,VAZIO);
                        DrawPiece(tabuleiro,j+1,i+1,jg->T[i][j]);
                }
        }
}

void PutText(IplImage *tabuleiro) {
        static CvFont font1;
        static double hscale = 2.0;

        static double vscale = 1.0;
        static double shear  = 0.0;
        static int thickness = 4;
        static int line_type = 8;
        cvInitFont(&font1, CV_FONT_HERSHEY_COMPLEX, hscale, vscale, shear, thickness, line_type);
        char str[10];   //string to put the counter to be printed with openCV
        char str1[10];
        char str2[10];
        sprintf(str,"PASS");                                              //Convert count to str
        sprintf(str1,"LOAD");                                              //Convert count to str
        sprintf(str2,"SAVE");                                              //Convert count to str

        cvPutText(tabuleiro, str, cvPoint(140,440), &font1, CV_RGB(207,181,59));   //put text in image
        cvPutText(tabuleiro, str1, cvPoint(420,310), &font1, CV_RGB(207,181,59));   //put text in image
        cvPutText(tabuleiro, str2, cvPoint(420,110), &font1, CV_RGB(207,181,59));   //put text in image


        cvShowImage(NAME_IMG_TAB, tabuleiro);                                   //show updated image in window

}
