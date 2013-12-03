#include "Queen.h"

    Queen::Queen(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        if(color == "white"){
            name = "White Queen";
        }
        else{
            name = "Black Queen";
        }
    }