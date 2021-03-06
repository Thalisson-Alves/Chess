#ifndef CHESS_KING_H
#define CHESS_KING_H


#include "Piece.h"

class King : public Piece {
public:
    King(const sf::Texture &texture, enum Piece::Type type, int position);

    std::vector<Move> getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const override;

    void pushNormalMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves) const;

    void pushCastleMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves) const;
};


#endif //CHESS_KING_H
