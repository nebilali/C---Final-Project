#include "Pawn.h"

    Pawn::Pawn(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        left = false;
        right = false;
        this->color = color;
        name = "pawn";
        if(color == "white"){
            image = new QImage("./resources/whitePawn.png");
        }
        else{
            image = new QImage("./resources/blackPawn.png");
        }
    }