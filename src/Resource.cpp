#include <Resource.hpp>

sf::Font& ResourceManager::getFont() {
    static sf::Font font;
    static bool loaded = false;

    if (!loaded) {
        if (!font.loadFromFile("arial.ttf")) {
            // handle error
        }

        loaded = true;
    }

    return font;
}
