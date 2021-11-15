#include "Bishop.h"

Bishop::Bishop(const sf::Texture &texture, enum Piece::Type type, int position) :
        Piece(texture, type, position) {}

std::vector<Piece::Move> Bishop::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    std::vector<Piece::Move> moves;
    std::vector<std::pair<int, int>> directions{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (auto [xOffset, yOffset] : directions)
        pushMovesByDirection(pieces, moves, xOffset, yOffset);

    return moves;
}
