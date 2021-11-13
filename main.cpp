#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/Board.h"
#include "src/Globals.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(Config::WindowWidth, Config::WindowHeight), "Chess");

    sf::Texture texture;
    texture.loadFromFile("../Images/pieceSprites.png");

//    const char *fen = "Q7/8/8/8/8/8/8/8 w KQkq - 0 1";
    Board board(texture);
    window.draw(board);
    window.display();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        auto mousePosition = sf::Mouse::getPosition(window);
                        auto pieceIndex = mousePosition.y / 80 * 8 + mousePosition.x / 80;
                        // TODO - Solve resize
                        if (pieceIndex >= 64 || pieceIndex < 0) {
                            std::cout << pieceIndex << '\n';
                            continue;
                        }
                        auto &piece = board.getPiece(pieceIndex);
                        if (piece->getType() & board.getTurn()) {
                            sf::Sprite &sprite = piece->getSprite();
                            sprite.setPosition(mousePosition.x, mousePosition.y);
                        }
                    }
                    break;
            }

            window.clear();
            window.draw(board);
            window.display();
        }
    }

    return 0;
}
