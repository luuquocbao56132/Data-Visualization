#include <Resource.hpp>

sf::Font& ResourceManager::getFont() {
    static sf::Font font;
    static bool loaded = false;

    if (!loaded) {
        if (!font.loadFromFile("consolas.ttf")) {
            // handle error
        }

        loaded = true;
    }

    return font;
}
