#ifndef CHESS_KING_H
#define CHESS_KING_H


#include "Piece.h"

class King : public Piece{
public:
    King(const sf::Texture &texture, enum Piece::Type type, int position);

    std::vector<Piece::Move> getLegalMoves() const override;
};


#endif //CHESS_KING_H
