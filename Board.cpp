/*

*/


#include "Board.h"
/*
class Piece; 
class BoardSquare {
private: 
        int row; 
        int column; 
        int width; 
        int height; 
        string color; 
        
        Piece piece; 
        bool highlighted; 
public: 
        BoardSquare(int row, int column, Strng color);
        int getRow();   
        int getColumn();
        String getPieceName(); 
        Piece getPieceName();
        void setPiece(Piece p);
        void draw(Graphics g);
        String getColor; 
        void updatePrev(int turn);
        void resetPrev();
        void undo(int turn);
        void move(boardSquare S); 
        void highlight(boolean b);
};

#endif
*/
/* 
class Board: public QWidget{
Q_OBJECT
private: 
        int BOARDWIDTH;
        int BOARDHEIGHT;

        BoardSquare[8][8] squares;
        int turn; 
        bool check; 
        bool blackcheck; 
        bool whitecheck; 
        bool moving; 
public: 
        Board(); 
        void newGame(); 
        void initialize();
        void reset(); 
        void resetPieces();
        void launchInstructions();
        void undo(); 
        void checkCheck()
        void paintComponent(Graphics g);
//ect..
//need to finish
public slots:
        void newgamePressed();
        void undoPressed();

};

#endif
*/

BoardSquare::BoardSquare(int r, int c, std::string color){
        row = r; 
        column = c; 
        this->color = color; 
        width = 50; 
        height = 50;  
        highlighted = false; 	
        piece = NULL; 
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

        //Clearing the rest of the board
        for(int i = 2; i < 6; i++){
                for(int j = 0; j < 8; j++){
                        squares[i][j]->setPiece(NULL);
                }
        }
}

void Board::paintEvent(QPaintEvent*){
        QPainter p(this);

        //frame
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
                                QImage *image = new QImage;
                                std::string s = squares[i][j]->getPieceName();
                                if(s == "White Pawn"){
                                        image->load("./resources/whitePawn.png");
                                }
                                if(s == "White Rook"){
                                        image->load("./resources/whiteRook.png");
                                }
                                if(s == "White Knight"){
                                        image->load("./resources/whiteKnight.png");
                                }
                                if(s == "White Bishop"){
                                        image->load("./resources/whiteBishop.png");                                        
                                }
                                if(s == "White King"){
                                        image->load("./resources/whiteKing.png");                                        
                                }
                                if(s == "White Queen"){
                                        image->load("./resources/whiteQueen.png");
                                }
                                if(s == "Black Pawn"){
                                        image->load("./resources/blackPawn.png");
                                }
                                if(s == "Black Rook"){
                                        image->load("./resources/blackRook.png");
                                }
                                if(s == "Black Knight"){
                                        image->load("./resources/blackKnight.png");
                                }
                                if(s == "Black Bishop"){
                                        image->load("./resources/blackBishop.png");                                        
                                }
                                if(s == "Black King"){
                                        image->load("./resources/blackKing.png");                                        
                                }
                                if(s == "Black Queen"){
                                        image->load("./resources/blackQueen.png");
                                }
                                p.drawImage(point, *image);
                        }
                }
        }

}

void Board::newgamePressed(){

}

void Board::undoPressed(){

}
