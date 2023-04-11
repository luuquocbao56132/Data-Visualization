#ifndef Button_hpp
#define Button_hpp

#include <BaseHeader.hpp>
#include <string>

class Button : public sf::Drawable, public sf::Transformable {
public:
    Button();
    Button(const sf::Vector2f& , const sf::Vector2f& ,
           const std::string& , const sf::Font& , unsigned int );

    void setFillColor(const sf::Color& ); 

    void setOutlineColor(const sf::Color& );

    void setOutlineThickness(float );

    void setPosition(const sf::Vector2f& );

    void setSize(const sf::Vector2f& ); 

    sf::Vector2f getSize() const ;

    bool isHovered() const ;

    void hover();

    void unhover();

    sf::FloatRect getGlobalBounds() const ;

// private:
    void centerOrigin(const sf::Vector2f& );

    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

    sf::Vector2f m_size;
    sf::RectangleShape m_rect;
    sf::Text m_text;
    bool m_isHovered;
};

#endif //Button_hpp