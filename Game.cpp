#include <SFML/Graphics.hpp>

#include "src/Globals.h"

#include "Game.h"

void Game::Run() {
    // TODO - window resize in runtime is not working!
    sf::RenderWindow window(sf::VideoMode(Config::WindowWidth, Config::WindowHeight), "Chess", sf::Style::Close);

    sf::Texture texture;
    texture.loadFromFile("../Images/pieceSprites.png");

    Board board(texture);
    window.draw(board);
    window.display();

    while (window.isOpen()) {
        sf::Event event{};
        if (window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        auto mousePosition = sf::Mouse::getPosition(window);
                        auto tileWidth = static_cast<int>(Config::getTileWidth());
                        auto tileHeight = static_cast<int>(Config::getTileHeight());
                        auto index = mousePosition.y / tileHeight * Config::BoardSize + mousePosition.x / tileWidth;

                        if (handlePromotion(board, index)) break;
                        if (board.hasSelectedPiece())
                            board.movePieceToPosition(index);
                        board.selectPiece(index);
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        auto mousePosition = sf::Mouse::getPosition(window);
                        auto tileWidth = static_cast<int>(Config::getTileWidth());
                        auto tileHeight = static_cast<int>(Config::getTileHeight());
                        auto index = mousePosition.y / tileHeight * Config::BoardSize + mousePosition.x / tileWidth;

                        if (handlePromotion(board, index)) break;
                        board.movePieceToPosition(index);
                    }
                    break;
                default:
                    continue;
            }
        }

        window.clear();
        window.draw(board);
        drawPromotionPieces(texture, board.getPromotionColor(), window);
        window.display();
    }
}

void Game::drawPromotionPieces(const sf::Texture &texture, const enum Piece::Type &promotionColor, sf::RenderWindow &window) {
    if (promotionColor == Piece::Type::NoColor)
        return;

    sf::RectangleShape rectangleShape({Config::getTileWidth() * PossiblePromotions.size(), Config::getTileHeight()});
    rectangleShape.setFillColor(sf::Color::Green);
    window.draw(rectangleShape);

    for (int i = 0; i < PossiblePromotions.size(); i++) {
        sf::Sprite promotionSprite(texture, Utils::getSpriteRect(
                static_cast<enum Piece::Type>(PossiblePromotions[i] | promotionColor)));

        promotionSprite.setScale(0.45, 0.45);
        promotionSprite.setPosition(i * Config::getTileWidth(), 0);
        window.draw(promotionSprite);
    }
}

bool Game::handlePromotion(Board &board, int selectedIndex) {
    if (board.getPromotionColor() == Piece::Type::NoColor)
        return false;

    if (selectedIndex < PossiblePromotions.size())
        board.promoteTo(PossiblePromotions[selectedIndex]);
    return true;
}
