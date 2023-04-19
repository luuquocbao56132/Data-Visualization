#ifndef Resource_hpp
#define Resource_hpp

#include <SFML/Graphics.hpp>

class ResourceManager {
public:
    static sf::Font& getFont();
    static int random(int, int);
    static int StringtoInt(std::string);
};

#endif //Resource_hpp