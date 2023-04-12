#include <DataTypes.hpp>

DataTypes::DataTypes(){};

DataTypes::DataTypes(const sf::Vector2f& position, const sf::Vector2f& size,
           const std::string& text, const sf::Font& font, unsigned int characterSize, int numInput):
        mainButton(position, size, text, ResourceManager::getFont(), characterSize,0),
        buttonSize(sf::Vector2f(90.f, 50.f)), buttonSpacing(sf::Vector2f(0.f, 5.f)),
        buttonPosition(sf::Vector2f(10.f, 450.f)), buttonRange(buttonSize + buttonSpacing){
        }

void DataTypes::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    // if (!isTurn)return;
    target.draw(mainButton);
    for (auto res : BaseButton)target.draw(*res);
    for (auto res : functionButton)target.draw(*res);
    //drawgraph
}

void DataTypes::checkHover(sf::Vector2f mousePos){
    mainButton.checkHover(mousePos);
    for (auto res : BaseButton)res->checkHover(mousePos);
    for (auto res : functionButton)res->checkHover(mousePos);
}

void DataTypes::checkPress(sf::Vector2f mousePos){
    //if (LL_button.checkPress(mousePos))isTurn = 1;
    for (auto res : BaseButton)if (res->checkPress(mousePos)){
        functionButton.clear(); functionButton = res->minButton;
    }
}
