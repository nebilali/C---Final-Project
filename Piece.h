/*	File: Piece.h
	Author: Nebil Ali
	Desc: header for basic piece functions
*/ 

#ifndef PIECE_H_
#define PIECE_H_ 

#include <string>
#include <QImage>

class Piece {
protected: 
	int row; 
	int column; 
	bool hasMoved; 
	std::string name; 
	std::string color;

public: 
	Piece();
	std::string getName(); 
	int getRow(); 
	int getColumn(); 
	void setPosition(int r, int c); 
	std::string getColor(); 
	bool getHasMoved(); 
	void sethasMoved(bool b); 
	void moved();	

};

#endif
