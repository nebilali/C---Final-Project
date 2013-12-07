/*

*/


#include "Board.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

BoardSquare::BoardSquare(int r, int c, std::string color){
        row = r; 
        column = c; 
        this->color = color; 
        width = 50; 
        height = 50;  
        highlighted = false; 	
        piece = NULL;
}

int BoardSquare::getRow(){
        return row;
}   
int BoardSquare::getColumn(){
        return column;
}

void BoardSquare::undo(int turn){
        piece = undoMap[turn];
}

void BoardSquare::move(BoardSquare *s){
        s->setPiece(piece);
        piece->moved();
        piece = NULL;
}

bool BoardSquare::isHighlighted(){
        return highlighted;
}

void BoardSquare::updateMap(int turn){
        Piece * piececopy;
        if(piece != NULL){
                piececopy = new Piece(*piece);
        }
        else{
                piececopy = NULL;
        }
        undoMap[turn] = piececopy;
}

void BoardSquare::highlight(bool b){
        highlighted = b;
}

bool BoardSquare::canMove(int r, int c, BoardSquare *squares[8][8]){
        std::string n = piece->getName();
        BoardSquare *s = squares[r][c];
        if(n == "rook"){
                if(s->getPiece() == NULL){
                        if(r == row){
                                bool inbetween = false;
                                for(int i = std::min(c, column)+1;
                                                i < std::max(c, column); i++){
                                        if(squares[row][i]->getPiece() != NULL){
                                                inbetween = true;
                                        }
                                }
                                return !inbetween;
                        }
                        if(c == column){
                                bool inbetween = false;
                                for(int i = std::min(r, row)+1;
                                                i < std::max(r, row); i++){
                                        if(squares[i][column]->getPiece() != NULL){
                                                inbetween = true;
                                        }
                                }
                                return !inbetween;
                        }
                }
                return false;
        }
        else if(n == "knight"){
                if(s->getPiece() == NULL){                        
                        //L-shaped movement
                        if(std::abs(r - row) == 2 && std::abs(c - column) == 1){
                                return true;
                        }
                        if(std::abs(r - row) == 1 && std::abs(c - column) == 2){
                                return true;
                        }
                }
                return false;
        }
        else if(n == "bishop"){
                if(s->getPiece() == NULL){
                        //No piece already occupying square
                        if(std::abs(r - row) == std::abs(c - column)){
                                //Diagonal --> horiz and vert distance identical
                                bool inbetween = false;
                                //Nothing in between the bishop and target destination
                                if((r > row && c > column) || (r < row && c < column)){
                                        for(int i = 1; i < std::abs(r - row); i++){
                                                if (squares[std::min(r, row)+i][std::min(c,column)+i]->getPiece() != NULL){
                                                        inbetween = true;
                                                }
                                        }
                                }
                                else{
                                        for(int i = 1; i < std::abs(r-row); i++){
                                                if(squares[std::min(r,row) + i][std::max(c, column)-i]->getPiece() != NULL){
                                                        inbetween = true;
                                                }
                                        }
                                }
                                if(!inbetween){
                                        return true;
                                }
                        }
                }
                return false;
        }
        else if(n == "king"){
                if(s->getPiece() == NULL){
                        if(std::abs(r - row) < 2 && std::abs(c - column) < 2){
                                return true;
                        }
                        if(r == row && !piece->getHasMoved()){
                                //Castling
                                if(c == column - 2){
                                        if (squares[row][column - 4]->getPiece() != NULL &&
                                                        !squares[row][column - 4]->getPiece()->getHasMoved() && 
                                                        squares[row][column - 1]->getPiece() == NULL &&
                                                        squares[row][column - 3]->getPiece() == NULL){
                                                return true;
                                        }
                                }
                                if(c == column + 2){
                                        if(squares[row][column + 3]->getPiece() != NULL && 
                                                        !squares[row][column + 3]->getPiece()->getHasMoved() &&
                                                        squares[row][column + 1]->getPiece() == NULL){
                                                return true;
                                        }
                                }
                        }
                }
                return false;
        }
        else if(n == "queen"){
                bool rOrB = false;
                if(s->getPiece() == NULL){
                        if(r == row){
                                bool inbetween = false;
                                for(int i = std::min(c, column)+1;
                                                i < std::max(c, column); i++){
                                        if(squares[row][i]->getPiece() != NULL){
                                                inbetween = true;
                                        }
                                }
                                if(!inbetween){
                                        rOrB = true;
                                }
                        }
                        if(c == column){
                                bool inbetween = false;
                                for(int i = std::min(r, row)+1;
                                                i < std::max(r, row); i++){
                                        if(squares[i][column]->getPiece() != NULL){
                                                inbetween = true;
                                        }
                                }
                                if(!inbetween){
                                        rOrB = true;
                                }
                        }
                }

                if(s->getPiece() == NULL){
                        //No piece already occupying square
                        if(std::abs(r - row) == std::abs(c - column)){
                                //Diagonal --> horiz and vert distance identical
                                bool inbetween = false;
                                //Nothing in between the bishop and target destination
                                if((r > row && c > column) || (r < row && c < column)){
                                        for(int i = 1; i < std::abs(r - row); i++){
                                                if (squares[std::min(r, row)+i][std::min(c,column)+i]->getPiece() != NULL){
                                                        inbetween = true;
                                                }
                                        }
                                }
                                else{
                                        for(int i = 1; i < std::abs(r-row); i++){
                                                if(squares[std::min(r,row) + i][std::max(c, column)-i]->getPiece() != NULL){
                                                        inbetween = true;
                                                }
                                        }
                                }
                                if(!inbetween){
                                        rOrB = true;
                                }
                        }
                }

                return rOrB;
        }

        else if(n == "pawn"){
                if(s->getPiece() == NULL){
                        if(piece->getColor() == "black"){
                                if(c == column){
                                        if(r == row + 1){
                                                //only can move if 1 square ahead
                                                return true;
                                        }
                                        if(r == row + 2 && piece->getHasMoved() == false){
                                                //unless it hasn't moved yet, in which case it can move two, too
                                                if(squares[row + 1][c]->getPiece() != NULL){
                                                        return false;
                                                }
                                                return true;
                                        }
                                }
                        }
                        else{
                                if(c == column){
                                        if(r == row - 1){
                                                //only can move if 1 square ahead
                                                return true;
                                        }
                                        if(r == row - 2 && piece->getHasMoved() == false){
                                                //unless it hasn't moved yet, in which case it can move two, too
                                                if(squares[row - 1][c]->getPiece() != NULL){
                                                        return false;
                                                }
                                                return true;
                                        }
                                }
                        }
                }
                return false;
        }

        else{
                //THIS SHOULD NEVER HAPPEN WHAT?
                return false;
        }


}

bool BoardSquare::canTake(int r, int c, BoardSquare *squares[8][8]){
        //REMEMBER TO IMPLEMENT PAWN CASE!!!!!!!!!!!!!
        std::string otherColor;
        if(piece->getColor() == "white"){
                otherColor = "black";
        }
        else{
                otherColor = "white";
        }
        std::string n = piece->getName();
        BoardSquare *s = squares[r][c];
        if(n == "rook"){
                if(s->getPiece() != NULL && s->getPiece()->getColor() == otherColor){
                        if(r == row){
                                bool inbetween = false;
                                for(int i = std::min(c, column)+1;
                                                i < std::max(c, column); i++){
                                        if(squares[row][i]->getPiece() != NULL){
                                                inbetween = true;
                                        }
                                }
                                return !inbetween;
                        }
                        if(c == column){
                                bool inbetween = false;
                                for(int i = std::min(r, row)+1;
                                                i < std::max(r, row); i++){
                                        if(squares[i][column]->getPiece() != NULL){
                                                inbetween = true;
                                        }
                                }
                                return !inbetween;
                        }
                }
                return false;
        }
        else if(n == "knight"){
                if(s->getPiece() != NULL && s->getPiece()->getColor() == otherColor){                        
                        //L-shaped movement
                        if(std::abs(r - row) == 2 && std::abs(c - column) == 1){
                                return true;
                        }
                        if(std::abs(r - row) == 1 && std::abs(c - column) == 2){
                                return true;
                        }
                }
                return false;
        }
        else if(n == "bishop"){
                if(s->getPiece() != NULL && s->getPiece()->getColor() == otherColor){
                        //No piece already occupying square
                        if(std::abs(r - row) == std::abs(c - column)){
                                //Diagonal --> horiz and vert distance identical
                                bool inbetween = false;
                                //Nothing in between the bishop and target destination
                                if((r > row && c > column) || (r < row && c < column)){
                                        for(int i = 1; i < std::abs(r - row); i++){
                                                if (squares[std::min(r, row)+i][std::min(c,column)+i]->getPiece() != NULL){
                                                        inbetween = true;
                                                }
                                        }
                                }
                                else{
                                        for(int i = 1; i < std::abs(r-row); i++){
                                                if(squares[std::min(r,row) + i][std::max(c, column)-i]->getPiece() != NULL){
                                                        inbetween = true;
                                                }
                                        }
                                }
                                if(!inbetween){
                                        return true;
                                }
                        }
                }
                return false;
        }
        else if(n == "king"){
                if(s->getPiece() != NULL && s->getPiece()->getColor() == otherColor){
                        if(std::abs(r - row) < 2 && std::abs(c - column) < 2){
                                return true;
                        }
                        if(r == row && !piece->getHasMoved()){
                                //Castling
                                if(c == column - 2){
                                        if (squares[row][column - 4]->getPiece() != NULL &&
                                                        !squares[row][column - 4]->getPiece()->getHasMoved() && 
                                                        squares[row][column - 1]->getPiece() == NULL &&
                                                        squares[row][column - 3]->getPiece() == NULL){
                                                return true;
                                        }
                                }
                                if(c == column + 2){
                                        if(squares[row][column + 3]->getPiece() != NULL && 
                                                        !squares[row][column + 3]->getPiece()->getHasMoved() &&
                                                        squares[row][column + 1]->getPiece() == NULL){
                                                return true;
                                        }
                                }
                        }
                }
                return false;
        }
        else if(n == "queen"){
                bool rOrB = false;
                if(s->getPiece() != NULL && s->getPiece()->getColor() == otherColor){
                        if(r == row){
                                bool inbetween = false;
                                for(int i = std::min(c, column)+1;
                                                i < std::max(c, column); i++){
                                        if(squares[row][i]->getPiece() != NULL){
                                                inbetween = true;
                                        }
                                }
                                if(!inbetween){
                                        rOrB = true;
                                }
                        }
                        if(c == column){
                                bool inbetween = false;
                                for(int i = std::min(r, row)+1;
                                                i < std::max(r, row); i++){
                                        if(squares[i][column]->getPiece() != NULL){
                                                inbetween = true;
                                        }
                                }
                                if(!inbetween){
                                        rOrB = true;
                                }
                        }
                }

                if(s->getPiece() != NULL && s->getPiece()->getColor() == otherColor){
                        //No piece already occupying square
                        if(std::abs(r - row) == std::abs(c - column)){
                                //Diagonal --> horiz and vert distance identical
                                bool inbetween = false;
                                //Nothing in between the bishop and target destination
                                if((r > row && c > column) || (r < row && c < column)){
                                        for(int i = 1; i < std::abs(r - row); i++){
                                                if (squares[std::min(r, row)+i][std::min(c,column)+i]->getPiece() != NULL){
                                                        inbetween = true;
                                                }
                                        }
                                }
                                else{
                                        for(int i = 1; i < std::abs(r-row); i++){
                                                if(squares[std::min(r,row) + i][std::max(c, column)-i]->getPiece() != NULL){
                                                        inbetween = true;
                                                }
                                        }
                                }
                                if(!inbetween){
                                        rOrB = true;
                                }
                        }
                }

                return rOrB;
        }

        else if(n == "pawn"){
                if(s->getPiece() != NULL && s->getPiece()->getColor() == otherColor){
                        if(piece->getColor() == "black"){
                                if(r == row + 1 && (std::abs(c - column) == 1)){
                                        return true;
                                }
                        }
                        else{
                                if(r == row - 1 && (std::abs(c - column) == 1)){
                                        return true;  
                                }
                        }
                }
                return false;
        }

        else{
                //THIS SHOULD NEVER HAPPEN WHAT?
                return false;
        }
}

std::string BoardSquare::getColor(){
        return color;
}

void BoardSquare::setPiece(Piece *p){
        piece = p;
}

std::string BoardSquare::getPieceName(){
        if(piece == NULL){
                return "";
        }
        else{
                return piece->getName();
        }
}

Piece * BoardSquare::getPiece(){
        return piece;
}


Board::Board(QWidget *parent) : QWidget(parent){
        setFixedSize(400,400);
        initialize();
}

void Board::initialize(){
        for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                        if(i%2 == j%2){
                                squares[i][j] = new BoardSquare(i, j, "white");
                        }
                        else{
                                squares[i][j] = new BoardSquare(i, j, "black");

                        }
                }
        }
        reset();
}

void Board::reset(){
        check = false;
        blackcheck = false;
        whitecheck = false;
        moving = false;
        whitemove = true;
        pressR = -1;
        pressC = -1;
        movingR = -1;
        movingC = -1;

        turn = 1;

        resetPieces();
        update();
}

void Board::resetPieces(){

        squares[0][0]->setPiece(new Rook(0,0,"black"));
        squares[0][7]->setPiece(new Rook(0,7,"black"));
        squares[0][1]->setPiece(new Knight(0,1,"black"));
        squares[0][6]->setPiece(new Knight(0,6,"black"));
        squares[0][2]->setPiece(new Bishop(0,2,"black"));
        squares[0][5]->setPiece(new Bishop(0,5,"black"));
        squares[0][3]->setPiece(new Queen(0,3,"black"));
        squares[0][4]->setPiece(new King(0,4,"black"));
        for(int j = 0; j < 8; j++){
                squares[1][j]->setPiece(new Pawn(1,j,"black"));
        }

        bKR = 0;
        bKC = 4;

        //White pieces
        squares[7][0]->setPiece(new Rook(7,0,"white"));
        squares[7][7]->setPiece(new Rook(7,7,"white"));
        squares[7][1]->setPiece(new Knight(7,1,"white"));
        squares[7][6]->setPiece(new Knight(7,6,"white"));
        squares[7][2]->setPiece(new Bishop(7,2,"white"));
        squares[7][5]->setPiece(new Bishop(7,5,"white"));
        squares[7][3]->setPiece(new Queen(7,3,"white"));
        squares[7][4]->setPiece(new King(7,4,"white"));
        for(int j = 0; j < 8; j++){
                squares[6][j]->setPiece(new Pawn(6,j,"white"));
        }

        wKR = 7;
        wKC = 4;

        //Clearing the rest of the board
        for(int i = 2; i < 6; i++){
                for(int j = 0; j < 8; j++){
                        squares[i][j]->setPiece(NULL);
                }
        }

        for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                        squares[i][j]->updateMap(turn);
                        squares[i][j]->highlight(false);
                }
        }


}

void Board::paintEvent(QPaintEvent*){
        QPainter p(this);

        p.drawRect(0, 0, 399, 399);

        for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                        int squarey = 50 * i;
                        int squarex = 50 * j;
                        if(squares[i][j]->getColor() == "white"){
                                p.fillRect(squarex, squarey, 50, 50, Qt::white);
                        }
                        else{
                                p.fillRect(squarex, squarey, 50, 50, Qt::blue);
                        }
                        if(squares[i][j]->getPieceName() != ""){
                                QPointF point(squarex, squarey);
                                p.drawImage(point, *(squares[i][j]->getPiece()->getImage()));     
                        }
                        if(squares[i][j]->isHighlighted()){
                                p.fillRect(squarex, squarey, 50, 50, QBrush(QColor(80, 255, 80, 128)));
                        }
                }
        }

}



void Board::move(int startR, int startC, int finR, int finC){
        //casting needs to get handled
        if(squares[startR][startC]->getPiece()->getName() == "king"){
                if(startC == finC + 2){
                        squares[startR][startC - 4]->move(squares[startR][startC - 1]);
                }
                else if(startC == finC - 2){
                        squares[startR][startC + 3]->move(squares[startR][startC + 1]);
                }
                if(squares[startR][startC]->getPiece()->getColor() == "white"){
                        wKR = finR;
                        wKC = finC;
                }
                else{
                        bKR = finR;
                        bKC = finC;
                }
        }
        squares[startR][startC]->move(squares[finR][finC]);
        whitemove = !whitemove;
        turn++;
        for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                        squares[i][j]->updateMap(turn);
                }
        }
        checkCheck();
}

bool Board::canMove(int startR, int startC, int finR, int finC){
        BoardSquare *sqr = squares[startR][startC];
        if(sqr->canMove(finR, finC, squares) || sqr->canTake(finR, finC, squares)){
                bool willCheck = false;
                std::string tempColor = sqr->getPiece()->getColor();
                move(startR, startC, finR, finC);
                if(tempColor == "white"){
                        willCheck = whitecheck;
                }
                else{
                        willCheck = blackcheck;
                }
                undo();
                return !willCheck;
        }
        else{
                return false;
        }
}

void Board::mousePressEvent(QMouseEvent * event){

        int c = event->x()/50;
        int r = event->y()/50;

        if(c < 8 && r < 8){
                pressC = c;
                pressR = r;
        }

}

void Board::mouseReleaseEvent(QMouseEvent * event){
        int c = event->x()/50;
        int r = event->y()/50;

        if(r == pressR && c == pressC){
                if(moving){
                        if(canMove(movingR, movingC, r, c)){
                                move(movingR, movingC, r, c);
                                if(squares[r][c]->getPiece()->getName() == "pawn" && (r == 0 || r == 7)){
                                        QMessageBox msgBox;
                                        QPushButton *qButton = msgBox.addButton(tr("Queen"), QMessageBox::ActionRole);
                                        QPushButton *rButton = msgBox.addButton(tr("Rook"), QMessageBox::ActionRole);
                                        QPushButton *nButton = msgBox.addButton(tr("Knight"), QMessageBox::ActionRole);
                                        QPushButton *bButton = msgBox.addButton(tr("Bishop"), QMessageBox::ActionRole);
                                        msgBox.setText("Promote Pawn");
                                        msgBox.exec();
                                        std::string pawnColor = squares[r][c]->getPiece()->getColor();
                                        if (msgBox.clickedButton() == bButton){
                                                squares[r][c]->setPiece(new Bishop(r, c, pawnColor));
                                        }
                                        else if (msgBox.clickedButton() == rButton){
                                                squares[r][c]->setPiece(new Rook(r, c, pawnColor));
                                        }
                                        else if (msgBox.clickedButton() == nButton){
                                                squares[r][c]->setPiece(new Knight(r, c, pawnColor));
                                        }
                                        else if (msgBox.clickedButton() == qButton){
                                                squares[r][c]->setPiece(new Queen(r, c, pawnColor));
                                        }
                                        squares[r][c]->updateMap(turn);
                                }
                        }
                        for(int i = 0; i < 8; i++){
                                for(int j = 0; j < 8; j++){
                                        squares[i][j]->highlight(false);
                                }
                        }
                        if(checkCheckMate()){
                                QMessageBox msgBox;
                                QPushButton *ngButton = msgBox.addButton(tr("New Game"), QMessageBox::ActionRole);
                                QPushButton *uButton = msgBox.addButton(tr("Undo"), QMessageBox::ActionRole);
                                msgBox.setText("Checkmate!");
                                msgBox.exec();
                                if (msgBox.clickedButton() == ngButton){
                                        reset();
                                } 
                                else if (msgBox.clickedButton() == uButton){
                                        undo();
                                        update();
                                }

                        }
                        else if(check){
                                QMessageBox msgBox;
                                msgBox.setText("Check!");
                                msgBox.exec();
                        }
                        movingC = -1;
                        movingR = -1;
                        moving = false;

                        update();
                }
                else{
                        if(squares[r][c]->getPiece() != NULL){
                                if(((squares[r][c]->getPiece()->getColor() == "white") && whitemove) ||
                                        ((squares[r][c]->getPiece()->getColor() == "black") && !whitemove)){
                                        moving = true;
                                        movingC = c;
                                        movingR = r;
                                        squares[r][c]->highlight(true);
                                        for(int i = 0; i < 8; i++){
                                                for(int j = 0; j < 8; j++){
                                                        if(canMove(r, c, i, j)){
                                                                squares[i][j]->highlight(true);
                                                        }
                                                }
                                        }
                                        update();
                                }
                        }
                }
        }

        pressR = -1;
        pressC = -1;
}

void Board::checkCheck(){
        check = false;
        blackcheck = false;
        whitecheck = false;
        for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                        if(squares[i][j]->getPiece() != NULL){
                                if(squares[i][j]->canTake
                                                (bKR, bKC, squares)){
                                        check = true;
                                        blackcheck = true;
                                }
                                if(squares[i][j]->canTake
                                                (wKR, wKC, squares)){
                                        check = true;
                                        whitecheck = true;
                                }
                        }
                }
        }
}

bool Board::checkCheckMate(){
        if(check){
                int r;
                int c;

                int count = 0;

                if(whitecheck){
                        r = wKR;
                        c = wKC;
                }
                else{
                        r = bKR;
                        c = bKC;
                }


                for(int i = std::max(0, r-1);i<std::min(r+2,8); i++){
                        for(int j = std::max(0, c-1); j<std::min(8,c+2); j++){
                                if(canMove(r, c, i, j)){
                                        return false;
                                }
                        }
                }


                for(int i = 0; i < 8; i++){
                        for(int j = 0; j < 8; j++){
                                if(squares[i][j]->getPiece() != NULL && squares[i][j]->canTake(r, c, squares)){
                                        count++;
                                }
                        }
                }

                if(count == 1){
                        for(int i = 0; i < 8; i++){
                                for(int j = 0; j < 8; j++){
                                        std::string s1 = "";
                                        if (whitecheck){s1 = "white";}
                                        else{s1 = "black";}
                                        if(squares[i][j]->getPiece() != NULL &&
                                                        squares[i][j]->getPiece()->getColor() == s1){
                                                for(int k = 0; k < 8; k++){
                                                        for(int l = 0; l < 8; l++){
                                                                if (canMove(i, j, k, l)){
                                                                        return false;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                        return true;
                }
                else{
                        return true;
                }
        }
        else{
                return false;
        }
}

void Board::undo(){
        turn--;
        for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                        squares[i][j]->undo(turn);
                        squares[i][j]->updateMap(turn);
                        if(squares[i][j]->getPieceName() == "king"){
                                if(squares[i][j]->getPiece()->getColor() == "white"){
                                        wKR = i;
                                        wKC = j;
                                }
                                else{
                                        bKR = i;
                                        bKC = j;
                                }
                        }
                }
        }


        whitemove = !whitemove;
        checkCheck();
}

void Board::newgamePressed(){
        reset();
}

void Board::undoPressed(){
        if(turn != 1){
                undo();
                moving = false;
                movingR = -1;
                movingC = -1;
                for(int i = 0; i < 8; i++){
                        for(int j = 0; j < 8; j++){
                                squares[i][j]->highlight(false);
                        }
                }
                update();
        }
}
