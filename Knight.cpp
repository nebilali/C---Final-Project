#include "Knight.h"

    Knight::Knight(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        name = "knight";
        if(color == "white"){
            image = new QImage("./resources/whiteKnight.png");
        }
        else{
            image = new QImage("./resources/blackKnight.png");
        }
    }