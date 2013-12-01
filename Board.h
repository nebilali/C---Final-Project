/*
	file: Board.h
*/

#include <QtGui>
#include <string>
#ifndef BOARD_SQUARE
#define BOARD_SQUARE

class Piece; 
class BoardSquare {
private: 
	int row; 
	int column; 
	int width; 
	int height; 
	string color; 
	
	Piece piece; 
	bool highlighted; 
public: 
	BoardSquare(int r, int c, String color);
	int getRow(); 	
	int getColumn();
	String getPieceName(); 
	Piece getPieceName();
	void setPiece(Piece p);
//	void draw(Graphics g);
	String getColor(); 
	void updatePrev(int turn);
	void resetPrev();
	void undo(int turn);
	void move(boardSquare S); 
	void highlight(boolean b);
};

#endif

#ifndef BOARD 
#define BOARD 

class Board: public QWidget{
Q_OBJECT
private: 
	int BOARDWIDTH; 	
	int BOARDHEIGHT; 
	
	BoardSquare *squares; 
	int turn; 
	bool check; 
	bool blackcheck; 
	bool whitecheck; 
	bool moving; 
public: 
	Board(QWidget *parent); 
	void newGame(); 
	void initialize(); 
	void reset(); 
	void resetPieces(); 
	void launchInstructions(); 
	void undo(); 
	void checkCheck() 
//	void paintComponent(Graphics g); 
//ect..
//need to finish
public slots:
	void newgamePressed();
	void undoPressed();

};

#endif
