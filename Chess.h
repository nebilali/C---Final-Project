/*
	File: Chess.h 
*/


#ifndef CHESS_H_  
#define CHESS_H_
#include <QtGui>

class Board;

class Chess: public widget {
Q_OBJECT
private:
	Board *board;
	QPushButton *newgame, *undo;  
public:
	Chess();

};

#endif
