#include <World.hpp>

World::World(){   
    // set the button size and character size
    sf::Vector2f buttonSize(120.f, 65.f);
    unsigned int characterSize = 30;
    
    // calculate the button positions
    sf::Vector2f position(10.f, 10.f);
    nLL = std::make_shared <LL> (position, buttonSize, "LL", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nDLL = std::make_shared <DLL> (position, buttonSize, "DLL", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nCLL = std::make_shared <CLL> (position, buttonSize, "CLL", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nStack = std::make_shared <Stack> (position, buttonSize, "Stack", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nQueue = std::make_shared <Queue> (position, buttonSize, "Queue", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nStaArr = std::make_shared <StaArr> (position, buttonSize, "StaArr", ResourceManager::getFont(), characterSize);
    position.x += buttonSize.x + 10; 
    nDynArr = std::make_shared <DynArr> (position, buttonSize, "DynArr", ResourceManager::getFont(), characterSize);
    
    liveData = nLL;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // // Draw the buttons
    // liveData->draw(window, sf::RenderStates::Default);
    target.draw(nLL->mainButton);
    target.draw(nDLL->mainButton);
    target.draw(nCLL->mainButton);
    target.draw(nStack->mainButton);
    target.draw(nQueue->mainButton);
    target.draw(nStaArr->mainButton);
    target.draw(nDynArr->mainButton);
    target.draw(*liveData);
}

void World::HoverCheck(sf::Vector2f mousePos){
    nLL->mainButton.checkHover(mousePos);
    nDLL->mainButton.checkHover(mousePos);
    nCLL->mainButton.checkHover(mousePos);
    nDynArr->mainButton.checkHover(mousePos);
    nStaArr->mainButton.checkHover(mousePos);
    nStack->mainButton.checkHover(mousePos);
    nQueue->mainButton.checkHover(mousePos);
    liveData->checkHover(mousePos);
}

void World::checkPress(sf::Vector2f mousePos){
    liveData->checkPress(mousePos);
    if (nLL->mainButton.checkPress(mousePos))liveData = nLL, nLL->resetAll();
    if (nDLL->mainButton.checkPress(mousePos))liveData = nDLL, nDLL->resetAll();
    if (nCLL->mainButton.checkPress(mousePos))liveData = nCLL, nCLL->resetAll();
    if (nQueue->mainButton.checkPress(mousePos))liveData = nQueue, nQueue->resetAll();
    if (nStack->mainButton.checkPress(mousePos))liveData = nStack, nStack->resetAll();
    if (nDynArr->mainButton.checkPress(mousePos))liveData = nDynArr, nDynArr->resetAll();
    if (nStaArr->mainButton.checkPress(mousePos))liveData = nStaArr, nStaArr->resetAll();
}

void World::checkText(char c){
    
}