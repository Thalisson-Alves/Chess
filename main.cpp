#include <SFML/Graphics.hpp>
#include "src/Board.h"
#include "src/Globals.h"

int main() {
    // TODO - window resize in runtime is not working!
    sf::RenderWindow window(sf::VideoMode(Config::WindowWidth, Config::WindowHeight), "Chess", sf::Style::Close);
    // Initialize the global Window, so we can get the mouse position relative to it.
    ConfigMouse::Window = &window;

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
                        board.selectPiece(ConfigMouse::getMouseIndex());
                    }
                    break;
            }
        }

        window.clear();
        window.draw(board);
        window.display();
    }

    return 0;
}
