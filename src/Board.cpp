#include <cassert>
#include "Board.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "NullPiece.h"
#include "Globals.h"

Board::Board(const sf::Texture &texture, const std::string &fen) : Turn(Piece::Type::White), SelectedPieceIndex(-1) {
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
    const auto &localBounds = circle.getLocalBounds();
    circle.setOrigin(localBounds.width / 2.0f, localBounds.height / 2.0f);
    circle.setFillColor(sf::Color(165, 167, 195, 200));

    auto rectangle = sf::RectangleShape(sf::Vector2f(Config::getTileHeight() - 3, Config::getTileHeight() - 3));
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

    // Deselect the current selected piece
    if (hasSelectedPiece())
        Pieces[SelectedPieceIndex]->resetSpritePosition();

    // Select the piece only if is its turn
    SelectedPieceIndex = (Pieces[index]->getType() & Turn ? index : -1);
}

void Board::update(const sf::Window &window) {
    if (not hasSelectedPiece())
        return;

    // Do the piece follow the mouse
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        auto mousePosition = sf::Mouse::getPosition(window);
        Pieces[SelectedPieceIndex]->setSpritePosition(mousePosition.x, mousePosition.y);
    }
}

bool Board::hasSelectedPiece() const {
    return SelectedPieceIndex >= 0;
}
