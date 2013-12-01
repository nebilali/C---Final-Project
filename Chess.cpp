/*
	File: Chess.cpp
*/ 

#include "Chess.h" 
#include <QtGui>
#include "Board.h" 

Chess::Chess(){
	QVBoxLayout *layout = new QVBoxLayout(this); 
	setWindowTitle("Chess");
	board = new Board(this); 
	layout->addWidget(board);
	newgame = new QPushButton("New Game", this);
	undo = new QPushButton("Undo", this);
	layout->addWidget(newgame);
	layout->addWidget(undo);
	connect(newgame, SIGNAL(clicked()), board, SLOT(newgamePressed()));
	connect(undo, SIGNAL(clicked()), board, SLOT(undoPressed()));
}


void draw(){
	QPainter painter;
	painter.drawQRect();  
}


int main(){}
