#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H


#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(const sf::Texture &texture, enum Piece::Type type, int position);
};


#endif //CHESS_PAWN_H
