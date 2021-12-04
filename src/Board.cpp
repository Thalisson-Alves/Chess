#include <cassert>
#include <memory>

#include "Board.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "NullPiece.h"
#include "Globals.h"

Board::Board(const sf::Texture &texture, const std::string &fen) : Turn(Piece::Type::White), SelectedPieceIndex(-1),
                                                                   Texture(texture),
                                                                   PromotionIndex(-1) {
    loadPiecesFromFen(texture, fen);
}

void Board::loadPiecesFromFen(const sf::Texture &texture, const std::string &fenString) {
    std::map<char, enum Piece::Type> piecesType = {
            {'k', Piece::Type::King},
            {'q', Piece::Type::Queen},
            {'b', Piece::Type::Bishop},
            {'n', Piece::Type::Knight},
            {'r', Piece::Type::Rook},
            {'p', Piece::Type::Pawn}
    };

    for (int i = 0, pos = 0; fenString[i] != '\0' && fenString[i] != ' '; i++) {
        if (isdigit(fenString[i])) {
            for (const int j = pos + (fenString[i] - '0'); pos < j; pos++)
                Pieces[pos] = std::make_unique<NullPiece>(texture, Piece::Type::None, pos);
        } else if (isalpha(fenString[i])) {
            char lowerChar = std::tolower(fenString[i]);
            auto pieceColor = isupper(fenString[i]) ? Piece::Type::White : Piece::Type::Black;
            auto pieceType = static_cast<enum Piece::Type>(piecesType[lowerChar] | pieceColor);
            switch (piecesType[lowerChar]) {
                case Piece::Type::King:
                    Pieces[pos] = std::make_unique<King>(texture, pieceType, pos);
                    break;
                case Piece::Type::Queen:
                    Pieces[pos] = std::make_unique<Queen>(texture, pieceType, pos);
                    break;
                case Piece::Type::Bishop:
                    Pieces[pos] = std::make_unique<Bishop>(texture, pieceType, pos);
                    break;
                case Piece::Type::Knight:
                    Pieces[pos] = std::make_unique<Knight>(texture, pieceType, pos);
                    break;
                case Piece::Type::Rook:
                    Pieces[pos] = std::make_unique<Rook>(texture, pieceType, pos);
                    break;
                case Piece::Type::Pawn:
                    Pieces[pos] = std::make_unique<Pawn>(texture, pieceType, pos);
                    break;
                default:
                    break;
            }
            pos++;
        }
    }

    Turn = (fenString[fenString.find(' ') + 1] == 'w' ? Piece::Type::White : Piece::Type::Black);
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    drawBackground(target, states);
    drawSelectedPieceMoves(target, states);
    drawPieces(target, states);
}

void Board::drawSelectedPieceMoves(sf::RenderTarget &target, const sf::RenderStates &states) const {
    if (not hasSelectedPiece())
        return;

    auto circle = sf::CircleShape(Config::getTileWidth() / 6.0f);
    const auto &circleBounds = circle.getLocalBounds();
    circle.setOrigin(circleBounds.width / 2.0f, circleBounds.height / 2.0f);
    circle.setFillColor(sf::Color(165, 167, 195, 200));

    auto rectangle = sf::RectangleShape(sf::Vector2f(Config::getTileHeight() - 3, Config::getTileHeight() - 3));
    const auto &rectangleBounds = rectangle.getLocalBounds();
    rectangle.setOrigin(rectangleBounds.width / 2.0f, rectangleBounds.height / 2.0f);
    rectangle.setFillColor(sf::Color(0, 0, 0, 0));
    rectangle.setOutlineColor(sf::Color(255, 0, 0, 100));
    rectangle.setOutlineThickness(3);

    for (auto move: Pieces[SelectedPieceIndex]->getLegalMoves(Pieces)) {
        int x = move.toPosition % 8;
        int y = move.toPosition / 8;
        auto position = sf::Vector2f(x * Config::getTileWidth() + Config::getTileWidth() / 2.0f,
                                     y * Config::getTileHeight() + Config::getTileWidth() / 2.0f);
        if (Pieces[move.toPosition]->getType() == Piece::None) {
            circle.setPosition(position);
            target.draw(circle, states);
        } else {
            rectangle.setPosition(position);
            target.draw(rectangle, states);
        }
    }
}

void Board::drawPieces(sf::RenderTarget &target, sf::RenderStates &states) const {
    for (const auto &piece: Pieces)
        piece->draw(target, states);
}

void Board::drawBackground(sf::RenderTarget &target, const sf::RenderStates &states) {
    auto rectangle = sf::RectangleShape(sf::Vector2f(Config::getTileWidth(), Config::getTileHeight()));
    for (int i = 0; i < Config::BoardSize; i++) {
        for (int j = 0; j < Config::BoardSize; j++) {
            rectangle.setPosition((float) j * rectangle.getSize().x, (float) i * rectangle.getSize().y);
            if (((i + j) & 1) == 0)
                rectangle.setFillColor(sf::Color(232, 235, 239));
            else
                rectangle.setFillColor(sf::Color(125, 135, 150));
            target.draw(rectangle, states);
        }
    }
}

void Board::selectPiece(int index) {
    assert(index >= 0 && index < Pieces.size());

    deselectPiece();

    // Select the piece only if is its turn
    SelectedPieceIndex = (Pieces[index]->getType() & Turn ? index : -1);
}

void Board::deselectPiece() {
    if (hasSelectedPiece())
        Pieces[SelectedPieceIndex]->resetSpritePosition();
    SelectedPieceIndex = -1;
}

void Board::update(const sf::Window &window) {
    if (not hasSelectedPiece())
        return;

    // The piece follow the mouse
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        auto mousePosition = sf::Mouse::getPosition(window);
        Pieces[SelectedPieceIndex]->setSpritePosition(mousePosition.x, mousePosition.y);
    }
}

bool Board::hasSelectedPiece() const {
    return SelectedPieceIndex >= 0;
}

void Board::movePieceToPosition(int positionIndex) {
    // TODO - limit pieces position if their king is in check
    if (not hasSelectedPiece() || positionIndex == SelectedPieceIndex)
        return;

    Piece::Move move{};
    for (auto possibleMove: Pieces[SelectedPieceIndex]->getLegalMoves(Pieces))
        if (possibleMove.toPosition == positionIndex)
            move = possibleMove;

    switch (move.type) {
        case Piece::Move::Type::None:
            break;
        case Piece::Move::Type::Normal:
            movePiece(move);
            updateTurn();
            break;
        case Piece::Move::Type::Attack:
            Pieces[move.toPosition] = std::make_unique<NullPiece>(Texture, Piece::Type::None, move.toPosition);
            movePiece(move);
            updateTurn();
            break;
        case Piece::Move::Type::EnPassant: {
            const auto toCaptureIndex = move.toPosition + 8 * (move.fromPosition < move.toPosition ? -1 : 1);
            Pieces[toCaptureIndex] = std::make_unique<NullPiece>(Texture, Piece::Type::None, move.fromPosition);
            movePiece(move);
            updateTurn();
            break;
        }
        case Piece::Move::Type::Castle: {
            int castleDirection = (move.toPosition < move.fromPosition ? -1 : 1);
            int rookPosition;
            if (move.fromPosition == 4 || move.fromPosition == 60)
                rookPosition = move.fromPosition + (castleDirection < 0 ? -4 : 3);
            else
                rookPosition = move.fromPosition + (castleDirection < 0 ? -3 : 4);
            movePiece({rookPosition, move.fromPosition + castleDirection, Piece::Move::Type::Normal});
            movePiece(move);
            updateTurn();
            break;
        }
    }

    if ((Pieces[move.toPosition]->getType() & Piece::Type::NoColor) == Piece::Type::Pawn
        && move.toPosition / Config::BoardSize == (move.toPosition < move.fromPosition ? 0 : Config::BoardSize - 1))
        PromotionIndex = move.toPosition;

    deselectPiece();
}

void Board::updateTurn() { Turn = (Turn == Piece::White ? Piece::Black : Piece::White); }

void Board::movePiece(Piece::Move move) {
    Pieces[move.fromPosition]->setPosition(move.toPosition);
    Pieces[move.toPosition]->setPosition(move.fromPosition);
    Pieces[move.fromPosition].swap(Pieces[move.toPosition]);
}

enum Piece::Type Board::getPromotionColor() const {
    if (PromotionIndex < 0)
        return Piece::Type::NoColor;
    return static_cast<enum Piece::Type>(Pieces[PromotionIndex]->getType() & ~Piece::Type::NoColor);
}

void Board::promoteTo(enum Piece::Type pieceType) {
    if (PromotionIndex < 0)
        return;

    auto promotionColor = Pieces[PromotionIndex]->getType() & ~Piece::Type::NoColor;
    pieceType = static_cast<enum Piece::Type>(pieceType | promotionColor);

    switch (pieceType & Piece::Type::NoColor) {
        case Piece::Type::Queen:
            Pieces[PromotionIndex] = std::make_unique<Queen>(Texture, pieceType, PromotionIndex);
            break;
        case Piece::Type::Bishop:
            Pieces[PromotionIndex] = std::make_unique<Bishop>(Texture, pieceType, PromotionIndex);
            break;
        case Piece::Type::Knight:
            Pieces[PromotionIndex] = std::make_unique<Knight>(Texture, pieceType, PromotionIndex);
            break;
        case Piece::Type::Rook:
            Pieces[PromotionIndex] = std::make_unique<Rook>(Texture, pieceType, PromotionIndex);
            break;
    }

    PromotionIndex = -1;
}
