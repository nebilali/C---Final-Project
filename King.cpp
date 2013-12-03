#include "King.h"

    King::King(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        if(color == "white"){
            name = "White King";
        }
        else{
            name = "Black King";
        }
    }