#ifndef Node_hpp
#define Node_hpp

#include <BaseHeader.hpp>
#include <DynArrow.hpp>

class Node;

class Node : public sf::Drawable, public sf::Transformable{
public:
    Node(float radius, const std::string& , const sf::Font& , float , const sf::Color& , const sf::Vector2f& );

    void setColor(const sf::Color& );

    void setText(const std::string& );

    void setArrow();

    void setDirectionColor(const sf::Color& , unsigned int );

    void setPartialColor(float );

    void rotateArrow(float );

    void changeSizeArrow(float );

    float getLengthArrow();

    sf::Vector2f getNodePosition();

    bool getString(int);

    void changeText(Direction, std::string );

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::shared_ptr <Node> nextNode;

private:
    sf::CircleShape m_circle;
    sf::Color m_color;
    sf::Vector2f m_position;
    sf::Text m_text;
    float m_radius;
    sf::Text m_text_directions[4];
    DynArrow m_arrow;
};

#endif // Node_hpp