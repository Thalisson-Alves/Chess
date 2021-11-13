#include "Pawn.h"

Pawn::Pawn(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> Pawn::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    int direction = (Type & Piece::Type::White ? -1 : 1);
    std::vector<Piece::Move> moves;
    std::vector<int> forward{8 * direction};
    if (not hasMoved)
        forward.push_back(16 * direction);
    for (auto dir : forward) {
        int pos = Position + dir;
        if (pos >= 0 && pos < 64 && pieces[pos]->getType() == Piece::Type::None)
            moves.push_back({Position, pos, Move::Type::Normal});
    }
    return moves;
}
