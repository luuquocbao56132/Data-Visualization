#ifndef DataTypes_hpp
#define DataTypes_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <InputBox.hpp>
#include <Graph.hpp>

class DataTypes: public sf::Drawable, public sf::Transformable{
public:
    DataTypes();
    DataTypes(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int ,int , int);
    virtual void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void checkHover(sf::Vector2f);
    void checkKeyInput(sf::Event& );
    virtual void checkPress(sf::Vector2f);
    virtual void resetAll();
    std::vector <std::shared_ptr<Button>> BaseButton, functionButton;
    std::vector <std::shared_ptr<InputBox>> inputBox;
    Button mainButton, upSpeed, downSpeed;
    sf::Text timeText;
    // InputBox inpBox;
    int buttonState;
    Graph firstGraph, mainGraph;
    //Graph xyz
    sf::Vector2f buttonSize, buttonSpacing, buttonPosition, buttonRange;
};

#endif // DataTypes_hpp