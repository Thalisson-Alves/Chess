#include "King.h"

King::King(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> King::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    auto moves = std::vector<Piece::Move>();
    std::vector<std::pair<int, int>> directions{{1,  0},
                                                {-1, 0},
                                                {0,  1},
                                                {0,  -1},
                                                {1,  1},
                                                {1,  -1},
                                                {-1, 1},
                                                {-1, -1}};

    for (auto[xOffset, yOffset]: directions)
        pushMovesByDirection(pieces, moves, xOffset, yOffset, 1);

    return moves;
}
