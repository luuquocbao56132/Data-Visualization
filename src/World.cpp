#include <World.hpp>

World::World(){   
    // set the button size and character size
    sf::Vector2f buttonSize(120.f, 65.f);
    unsigned int characterSize = 30;
    
    // calculate the button positions
    sf::Vector2f position(10.f, 10.f);
    //position.x = buttonSize.x; // center the buttons horizontally
    
    // create the buttons and set their properties
    LL = Button (position, buttonSize, "LL", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x; BaseButton.push_back(&LL);
    DLL = Button (position, buttonSize, "DLL", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x; BaseButton.push_back(&DLL);
    CLL = Button (position, buttonSize, "CLL", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x; BaseButton.push_back(&CLL);
    Stack = Button (position, buttonSize, "Stack", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x; BaseButton.push_back(&Stack);
    Queue = Button (position, buttonSize, "Queue", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x; BaseButton.push_back(&Queue);
    StaArr = Button (position, buttonSize, "StaArr", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x; BaseButton.push_back(&StaArr);
    DynArr = Button (position, buttonSize, "DynArr", ResourceManager::getFont(), characterSize);
    BaseButton.push_back(&DynArr);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the buttons
    target.draw(LL);
    target.draw(DLL);
    target.draw(CLL);
    target.draw(Stack);
    target.draw(Queue);
    target.draw(StaArr);
    target.draw(DynArr);
}

void World::HoverCheck(sf::Vector2f mousePos){
    for (Button* res : BaseButton)
        if (res->getGlobalBounds().contains(mousePos)) res->hover(); 
            else res->unhover();
}