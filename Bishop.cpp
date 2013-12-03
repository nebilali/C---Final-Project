#include "Bishop.h"

    Bishop::Bishop(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        if(color == "white"){
            name = "White Bishop";
        }
        else{
            name = "Black Bishop";
        }
    }