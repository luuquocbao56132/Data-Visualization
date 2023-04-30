#ifndef Node_hpp
#define Node_hpp

#include <BaseHeader.hpp>
#include <DynArrow.hpp>
#include <CircleArrow.hpp>

class Node;

class Node : public sf::Drawable, public sf::Transformable{
public:
    Node();
    Node(float radius, const std::string& , const sf::Font& , float , const sf::Color& , const sf::Vector2f& , bool);

    void setColor(const sf::Color& );

    void setText(const std::string& );
    void setTextBot(std::string );
    void setTextTop(std::string );

    void setArrow();
    void setNodeColor(sf::Color );
    void setOutlineColor(sf::Color );
    void setTextColor(sf::Color );

    void setDirectionColor(const sf::Color& , unsigned int );

    void setPosition(sf::Vector2f );

    void setPartialColor(float );

    void rotateNextArrow(float );
    void rotatePrevArrow(float );

    void changeSizeArrow(float );

    void changeSizeNode(float);

    float getLengthArrow();

    float getRad();

    sf::Vector2f getNodePosition();

    bool getString(int);

    int getValue();

    void changeText(Direction, std::string );

    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

    std::shared_ptr <Node> nextNode, prevNode;

    DynArrow nextArrow, prevArrow;

    sf::Text m_text_directions[4];
    void updateCircle();
    void setCircle(bool);
    int numArrow;
    bool stateCircle;
    CircleArrow circle;
private:
    bool typeNode;
    sf::CircleShape m_circle;
    sf::RectangleShape m_rectangle;
    sf::Color m_color;
    sf::Vector2f m_position;
    sf::Text m_text;
    float m_radius;
};

#endif // Node_hpp