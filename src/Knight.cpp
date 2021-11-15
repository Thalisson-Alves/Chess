#include "Knight.h"
#include "Globals.h"

Knight::Knight(const sf::Texture &texture, enum Piece::Type type, int position) :
        Piece(texture, type, position) {

}

std::vector<Piece::Move> Knight::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    std::vector<Piece::Move> moves;
    std::vector<std::pair<int, int>> directions{{2,  1},
                                                {1,  2},
                                                {-1, 2},
                                                {-2, 1},
                                                {-2, -1},
                                                {-1, -2},
                                                {1,  -2},
                                                {2,  -1}};
    for (auto[xOffset, yOffset]: directions) {
        int x = Position % 8 + xOffset, y = Position / 8 + yOffset;
        if (Utils::isInBoardRange(x, y) &&
            (pieces[x + 8 * y]->getType() == Piece::Type::None || isEnemy(pieces[x + 8 * y])))
            moves.push_back({Position, x + 8 * y, Piece::Move::Type::Attack});
    }

    return moves;
}
