#include "Pawn.h"
#include "Globals.h"

Pawn::Pawn(const sf::Texture &texture, enum Piece::Type type, int position)
        : Piece(texture, type, position), Direction((position / Config::BoardSize) == 1 ? 1 : -1) {

}

std::vector<Piece::Move> Pawn::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    std::vector<Piece::Move> moves;

    pushForwardMoves(pieces, moves, Direction);
    pushAttackingMoves(pieces, moves, Direction);
    pushEnPassantMoves(pieces, moves, Direction);

    return moves;
}

void Pawn::pushAttackingMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves,
                              int direction) const {
    std::vector<std::pair<int, int>> diagonals{{-1, direction},
                                               {1,  direction}};
    for (auto[xOffset, yOffset]: diagonals) {
        int x = Position % 8 + xOffset, y = Position / 8 + yOffset;
        if (Utils::isInBoardRange(x, y) && isEnemy(pieces[x + 8 * y]))
            moves.push_back({Position, x + 8 * y, Move::Type::Attack});
    }
}

void Pawn::pushForwardMoves(const std::array<Piece::Ptr, 64> &pieces,
                            std::vector<Piece::Move> &moves, int direction) const {
    std::vector<int> forward{8 * direction};
    if (not MoveCount)
        forward.push_back(16 * direction);
    for (auto dir: forward) {
        int pos = Position + dir;
        if (pos >= 0 && pos < 64 && pieces[pos]->getType() == None)
            moves.push_back({Position, pos, Move::Type::Normal});
    }
}

void Pawn::pushEnPassantMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves,
                              int direction) const {
    int enemyPawnInitialRow = (direction == -1 ? 1 : 6);
    // Check if Pawn is in the right row
    if (Position / 8 != enemyPawnInitialRow - 2 * direction)
        return;

    std::vector<std::pair<int, int>> specials{{1,  0},
                                              {-1, 0}};
    for (auto[xOffset, yOffset]: specials) {
        int x = Position % 8 + xOffset, y = Position / 8 + yOffset;
        int newPos = x + 8 * y;
        if (isEnemy(pieces[newPos]) && (pieces[newPos]->getType() & Piece::Type::NoColor) == Piece::Type::Pawn &&
            pieces[newPos]->getMoveCount() == 1)
            moves.push_back({Position, x + 8 * (y + direction), Piece::Move::Type::EnPassant});
    }
}
