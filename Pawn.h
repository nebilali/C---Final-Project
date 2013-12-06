#include "Piece.h"

    class Pawn : public Piece{
    public:
        Pawn(int r, int c, std::string color);
    private:
        bool left;
        bool right;
    };