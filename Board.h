/*
	file: Board.h
*/

#include <QtGui>
#include <string>
#include <map>
#include "Piece.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#ifndef BOARD_SQUARE
#define BOARD_SQUARE

//class Piece; 
class BoardSquare {
private: 
	int row; 
	int column; 
	int width; 
	int height; 
	std::string color;
	
	Piece *piece; 
	bool highlighted; 

	std::map<int, Piece*> undoMap;
public: 
	BoardSquare(int r, int c, std::string color);
	int getRow(); 	
	int getColumn();
	std::string getPieceName(); 
	Piece *getPiece();
	void setPiece(Piece *p);
	std::string getColor(); 
	void updatePrev(int turn);
	void resetPrev();
	void undo(int turn);
	void move(BoardSquare *s);
	void highlight(bool b);
	bool isHighlighted();

	void updateMap(int turn);

	bool canMove(int r, int c, BoardSquare* squares[8][8]);
	bool canTake(int r, int c, BoardSquare* squares[8][8]);
};

#endif

#ifndef BOARD 
#define BOARD 

class Board: public QWidget{
Q_OBJECT
private: 
	int BOARDWIDTH; 	
	int BOARDHEIGHT; 
	
	BoardSquare* squares[8][8]; 
	int turn; 
	bool check; 
	bool blackcheck; 
	bool whitecheck; 
	bool moving;
	bool whitemove;

	int wKR; //white king row
	int wKC;

	int bKR;
	int bKC;

	int movingR;
	int movingC;

	int pressR;
	int pressC;


public: 
	Board(QWidget *parent); 
	void newGame(); 
	void initialize(); 
	void reset(); 
	void resetPieces(); 
	void undo(); 
	void checkCheck();
	bool checkCheckMate();
	void move(int startR, int startC, int finR, int finC);
	bool canMove(int startR, int startC, int finR, int finC);
//	void paintComponent(Graphics g); 
//ect..
//need to finish
public slots:
	void newgamePressed();
	void undoPressed();

protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);

};

#endif
