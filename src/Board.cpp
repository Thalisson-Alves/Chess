#include "Board.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "NullPiece.h"
#include "Globals.h"

Board::Board(const sf::Texture &texture, const std::string &fen) : Turn(Piece::Type::White) {
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

    for (const auto &piece: Pieces)
        if (piece)
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

Piece::Ptr &Board::getPiece(int index) {
    return Pieces[index];
}

const enum Piece::Type &Board::getTurn() const {
    return Turn;
}
