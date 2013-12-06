/*
	file: Board.h
*/

#include <QtGui>
#include <string>
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

	bool canMove(int r, int c, BoardSquare*** squares);
	bool canTake(int r, int c, BoardSquare*** squares);
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
	void launchInstructions(); 
	void undo(); 
	void checkCheck();
	void draw();
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
