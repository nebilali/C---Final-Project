/*	File: Piece.h
	Author: Nebil Ali
	Desc: header for basic piece functions
*/ 

#ifndef PIECE_H_
#define PIECE_H_ 

#include <strings>
#include <QImage>

class Piece {
protected: 
	int row; 
	int column; 
	bool hasMoved; 
	String name; 
	String color;

public: 
	String getName(); 
	int getRow(); 
	int getColumn(); 
	void setPosition(int r, int c); 
	String getColor(); 
	bool hasMoved(); 
	void sethasMoved(bool b); 
	void moved();	

};

#endif
