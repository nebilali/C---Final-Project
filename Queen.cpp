#include "Queen.h"

    Queen::Queen(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        name = "queen";
        if(color == "white"){
            image = new QImage("./resources/whiteQueen.png");
        }
        else{
            image = new QImage("./resources/blackQueen.png");
        }
    }