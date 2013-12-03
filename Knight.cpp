#include "Knight.h"

    Knight::Knight(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        if(color == "white"){
            name = "White Knight";
        }
        else{
            name = "Black Knight";
        }
    }