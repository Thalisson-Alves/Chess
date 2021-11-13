#ifndef CHESS_KING_H
#define CHESS_KING_H


#include "Piece.h"

class King : public Piece{
public:
    King(const sf::Texture &texture, enum Piece::Type type, int position);
};


#endif //CHESS_KING_H
