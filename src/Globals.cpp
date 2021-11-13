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
