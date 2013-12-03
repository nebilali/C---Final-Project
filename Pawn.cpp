#include "Pawn.h"

    Pawn::Pawn(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        if(color == "white"){
            name = "White Pawn";
        }
        else{
            name = "Black Pawn";
        }
    }