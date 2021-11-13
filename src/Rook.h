#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "Piece.h"

class Rook : public Piece{
public:
    Rook(const sf::Texture &texture, enum Piece::Type type, int position);

    std::vector<Piece::Move> getLegalMoves() const override;
};


#endif //CHESS_ROOK_H
