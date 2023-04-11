#ifndef Resource_hpp
#define Resource_hpp

#include <SFML/Graphics.hpp>

class ResourceManager {
public:
    static sf::Font& getFont();
};

#endif //Resource_hpp