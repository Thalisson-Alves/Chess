#ifndef CHESS_NULLPIECE_H
#define CHESS_NULLPIECE_H


#include "Piece.h"

class NullPiece : public Piece {
public:
    NullPiece(const sf::Texture &texture, enum Piece::Type type, int position);

    std::vector<Piece::Move> getLegalMoves() const override;
};


#endif //CHESS_NULLPIECE_H
