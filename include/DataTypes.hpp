#ifndef DataTypes_hpp
#define DataTypes_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>

class DataTypes: public sf::Drawable{
public:
    DataTypes();
    DataTypes(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int ,int );
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void checkHover(sf::Vector2f);
    void checkPress(sf::Vector2f);
    std::vector <std::shared_ptr<Button>> BaseButton, functionButton;
    Button mainButton;
    //Graph xyz
    sf::Vector2f buttonSize, buttonSpacing, buttonPosition, buttonRange;
};

#endif // DataTypes_hpp