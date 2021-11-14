#include "Pawn.h"
#include "Globals.h"

Pawn::Pawn(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> Pawn::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    int direction = (Type & Piece::Type::White ? -1 : 1);
    std::vector<Piece::Move> moves;

    pushForwardMoves(pieces, moves, direction);
    pushAttackingMoves(pieces, moves, direction);

    return moves;
}

void Pawn::pushAttackingMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves,
                              int direction) const {
    std::vector<std::vector<int>> diagonals{{-1, direction}, {1, direction}};
    for (auto dir : diagonals) {
        int x = Position % 8 + dir[0], y = Position / 8 + dir[1];
        if (Utils::isInBoardRange(x, y) && isEnemy(pieces[x + 8 * y]))
            moves.push_back({Position, x + 8 * y, Move::Type::Attack});
    }
}

void Pawn::pushForwardMoves(const std::array<Piece::Ptr, 64> &pieces,
                            std::vector<Piece::Move> &moves, int direction) const {
    std::vector<int> forward{8 * direction};
    if (not HasMoved)
        forward.push_back(16 * direction);
    for (auto dir: forward) {
        int pos = Position + dir;
        if (pos >= 0 && pos < 64 && pieces[pos]->getType() == None)
            moves.push_back({Position, pos, Move::Type::Normal});
    }
}
