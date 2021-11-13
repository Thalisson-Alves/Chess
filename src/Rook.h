#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "Piece.h"

class Rook : public Piece{
public:
    Rook(const sf::Texture &texture, enum Piece::Type type, int position);

    std::vector<Move> getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const override;
};


#endif //CHESS_ROOK_H
