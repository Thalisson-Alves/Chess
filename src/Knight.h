#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "Piece.h"

class Knight : public Piece{
public:
    Knight(const sf::Texture &texture, enum Piece::Type type, int position);
};


#endif //CHESS_KNIGHT_H
