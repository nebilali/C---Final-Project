#include "Bishop.h"

    Bishop::Bishop(int r, int c, std::string color){
        setPosition(r, c);
        hasMoved = false;
        this->color = color;
        name = "bishop";
        if(color == "white"){
            image = new QImage("./resources/whiteBishop.png");
        }
        else{
            image = new QImage("./resources/blackBishop.png");
        }
    }