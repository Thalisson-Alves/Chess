#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H


#include "Piece.h"

class Queen : public Piece {
public:
    Queen(const sf::Texture &texture, enum Piece::Type type, int position);

    std::vector<Move> getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const override;
};


#endif //CHESS_QUEEN_H
