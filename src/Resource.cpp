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

int ResourceManager::random(int l, int r){
    return rand()%(r-l + 1) + l;
}

int ResourceManager::StringtoInt(std::string s){
    int res = 0, t = 1;
    for (int i = s.size()-1; i >= 0; --i)res += t * (int)(s[i] - '0'), t *= 10;
    return res;
}
