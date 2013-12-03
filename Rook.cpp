#include "Rook.h"

    Rook::Rook(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        if(color == "white"){
            name = "White Rook";
        }
        else{
            name = "Black Rook";
        }
    }