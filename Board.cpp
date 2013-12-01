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

BoardSquare::BoardSquare(int r, int c, String color){
	row = r; 
	column = c; 
	this.color = color; 
	width = 50; 
	height = 50;  
	highlighted = false; 	
	piece = NULL; 
}

Board::Board(QWidget *parent){
	turn = 1;
	check = false; 
	blackcheck = false; 
	whitecheck = false; 
	moving = false; 
	BoardSquare squares = new BoardSquare[8][8];
	newGame();	
}

void Board::newGame(){
}

draw(){
}
