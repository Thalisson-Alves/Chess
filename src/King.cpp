#include <iostream>
#include "King.h"
#include "Globals.h"

King::King(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> King::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    auto moves = std::vector<Piece::Move>();
    pushNormalMoves(pieces, moves);
    pushCastleMoves(pieces, moves);

    return moves;
}

void King::pushNormalMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves) const {
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
}

void King::pushCastleMoves(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves) const {
    if (MoveCount)
        return;

    int rook_position = Position - 1;
    /* Castle to left */

    // Check if all pieces up the left most corner are NullPieces
    for (; (rook_position % Config::BoardSize) && not pieces[rook_position]->getType(); rook_position--);
    // If the last piece is a rook, and it has not moved yet, can castle
    if ((pieces[rook_position]->getType() & Piece::Type::NoColor) == Piece::Type::Rook &&
        not pieces[rook_position]->getMoveCount())
        moves.push_back({Position, Position - 2, Piece::Move::Type::Castle});

    /* Castle to right */

    // Check if all pieces up the left most corner are NullPieces
    for (rook_position = Position + 1; (rook_position % Config::BoardSize) < (Config::BoardSize - 1)
                                       && not pieces[rook_position]->getType(); rook_position++);
    // If the last piece is a rook, and it has not moved yet, can castle
    if ((pieces[rook_position]->getType() & Piece::Type::NoColor) == Piece::Type::Rook &&
        not pieces[rook_position]->getMoveCount())
        moves.push_back({Position, Position + 2, Piece::Move::Type::Castle});
}
