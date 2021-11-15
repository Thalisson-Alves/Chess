#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H


#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(const sf::Texture &texture, enum Piece::Type type, int position);

    std::vector<Move> getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const override;

private:
    void
    pushForwardMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves, int direction) const;

    void
    pushAttackingMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves, int direction) const;

    void
    pushEnPassantMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves, int direction) const;
};


#endif //CHESS_PAWN_H
