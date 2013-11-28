#include "Piece.h" 


String Piece::getName(){
	return name; 
} 

int Piece::getRow(){
	return row;
} 

int Piece::getColumn(){
	return column;
} 

void Piece::setPosition(int r, int c){
	row = r; 
	column = c; 
} 

String Piece::getColor(){
	return color; 
}

bool Piece::hasMoved(){
	return hasMoved;
} 

void Piece::sethasMoved(bool b){
	hasMoved = b; 
} 

void Piece::moved(){
	hasMoved = true; 
}   
