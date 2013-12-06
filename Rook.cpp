#include "Rook.h"

    Rook::Rook(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        name = "rook";
        if(color == "white"){
            image = new QImage("./resources/whiteRook.png");
        }
        else{
            image = new QImage("./resources/blackRook.png");
        }

    }
