/*File generated automatically in K56CB by miguel on seg jan 21 16:49:40 WET 2019*/
#ifdef __cplusplus
extern "C" {
#endif
/* myf.c */
int AskForGameMode ();
int CheckMove (othello * jg, int move, directions * dir);
void CheckWin (othello * jg);
void ClearValidMoves (othello * jg);
void FillOtelloStruct (char *str, othello * jg, int lin, int flag);
int GenerateMove (othello * jg);
int GetPlayerMove ();
void InitGame (othello * jg);
int LoadGame (othello * game, char *filename);
void PrintGameBoard (othello * jg);
void PrintHelp ();
void PrintValidMoves (othello * jg, directions * dir, IplImage * tabuleiro);
int SaveGame (othello * jg, char *filename);
int WinGame (othello * jg);
/* directions.c */
int CheckDirection (othello * jg, int place, directions * dir, int Direction);
void NeighborOpponent (othello * jg, int place, directions * dir);
void ReversePieces (othello * jg, int move, directions * dir);
/* pcolor.c */
void HighLightText (void);
void PrintGreenLine (void);
void PrintRedLine (void);
void ResetTextColors (void);
void TextColorRed (void);
void textcolor (int attr, int fg, int bg);
/* display.c */
void DrawPiece (IplImage * img, int col, int lin, char player);
void InitDisplay (IplImage * tabuleiro);
void PutText (IplImage * tabuleiro);
void UpdateDisplay (othello * jg, IplImage * tabuleiro);
void myActionOnMouseClick (int event, int x, int y, int flags, void *param);
/* main.c */
int main (int argc, char const *argv[]);
#ifdef __cplusplus
}
#endif
