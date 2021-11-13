#include <SFML/Window/Mouse.hpp>
#include <cassert>
#include "Globals.h"

const int Config::BoardSize = 8;
const int Config::WindowWidth = 640;
const int Config::WindowHeight = 640;

float Config::getTileWidth() {
    return static_cast<float>(WindowWidth) / static_cast<float>(BoardSize);
}

float Config::getTileHeight() {
    return static_cast<float>(WindowHeight) / static_cast<float>(BoardSize);
}

sf::RenderWindow *ConfigMouse::Window = nullptr;

int ConfigMouse::getMouseIndex() {
    assert(Window);

    auto mousePosition = sf::Mouse::getPosition(*Window);
    auto tileWidth = static_cast<int>(Config::getTileWidth());
    auto tileHeight = static_cast<int>(Config::getTileHeight());
    return mousePosition.y / tileHeight * Config::BoardSize + mousePosition.x / tileWidth;
}
