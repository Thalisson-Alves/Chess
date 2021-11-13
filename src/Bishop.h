#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H


#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(const sf::Texture &texture, enum Piece::Type type, int position);
};


#endif //CHESS_BISHOP_H
