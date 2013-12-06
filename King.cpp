#include "King.h"

    King::King(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        name = "king";
        if(color == "white"){
            image = new QImage("./resources/whiteKing.png");
        }
        else{
            image = new QImage("./resources/blackKing.png");
        }
    }