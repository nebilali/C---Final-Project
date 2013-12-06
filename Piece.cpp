#include "Piece.h" 

Piece::Piece(){

}

std::string Piece::getName(){
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

std::string Piece::getColor(){
	return color; 
}

bool Piece::getHasMoved(){
	return hasMoved;
} 

void Piece::sethasMoved(bool b){
	hasMoved = b; 
} 

void Piece::moved(){
	hasMoved = true; 
}   

QImage * Piece::getImage(){
    return image;
}
