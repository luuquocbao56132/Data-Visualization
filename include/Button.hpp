#ifndef Button_hpp
#define Button_hpp

#include <SFML/Graphics.hpp>
#include <string>

class Button: public sf::Text {
public:
    Button(const sf::Vector2f& , const sf::Vector2f& ,
           const std::string& , const sf::Font&, unsigned int);
    bool contains(const sf::Vector2f&) ;

private:
    sf::RectangleShape m_shape;
};

#endif //Button_hpp