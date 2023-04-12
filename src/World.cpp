#include <World.hpp>

World::World(){   
    // set the button size and character size
    sf::Vector2f buttonSize(120.f, 65.f);
    unsigned int characterSize = 30;
    
    // calculate the button positions
    sf::Vector2f position(10.f, 10.f);
    nLL = LL (position, buttonSize, "LL", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nDLL = DLL (position, buttonSize, "DLL", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nCLL = CLL (position, buttonSize, "CLL", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nStack = Stack (position, buttonSize, "Stack", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nQueue = Queue (position, buttonSize, "Queue", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nStaArr = StaArr (position, buttonSize, "StaArr", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nDynArr = DynArr (position, buttonSize, "DynArr", ResourceManager::getFont(), characterSize);
    
    liveData = std::make_unique <LL>(nLL);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // // Draw the buttons
    // liveData->draw(window, sf::RenderStates::Default);
    target.draw(nLL.mainButton);
    target.draw(nDLL.mainButton);
    target.draw(nCLL.mainButton);
    target.draw(nStack.mainButton);
    target.draw(nQueue.mainButton);
    target.draw(nStaArr.mainButton);
    target.draw(nDynArr.mainButton);
    target.draw(*liveData);
}

void World::HoverCheck(sf::Vector2f mousePos){
    nLL.mainButton.checkHover(mousePos);
    nDLL.mainButton.checkHover(mousePos);
    nCLL.mainButton.checkHover(mousePos);
    nDynArr.mainButton.checkHover(mousePos);
    nStaArr.mainButton.checkHover(mousePos);
    nStack.mainButton.checkHover(mousePos);
    nQueue.mainButton.checkHover(mousePos);
    liveData->checkHover(mousePos);
}

void World::checkPress(sf::Vector2f mousePos){
    liveData->checkPress(mousePos);
    if (nLL.mainButton.checkPress(mousePos))liveData = std::make_unique <LL>(nLL);
    if (nDLL.mainButton.checkPress(mousePos))liveData = std::make_unique <DLL>(nDLL);
    if (nCLL.mainButton.checkPress(mousePos))liveData = std::make_unique <CLL>(nCLL);
    if (nQueue.mainButton.checkPress(mousePos))liveData = std::make_unique <Queue>(nQueue);
    if (nStack.mainButton.checkPress(mousePos))liveData = std::make_unique <Stack>(nStack);
    if (nDynArr.mainButton.checkPress(mousePos))liveData = std::make_unique <DynArr>(nDynArr);
    if (nStaArr.mainButton.checkPress(mousePos))liveData = std::make_unique <StaArr>(nStaArr);
}