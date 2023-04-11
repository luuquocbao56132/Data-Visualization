#include <Game.hpp>

Game::Game(): mWindow (sf::VideoMode(1400,800), "Data Visualization"), mWorld{}{

}
    
void Game::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::milliseconds(8);
    while (mWindow.isOpen()){
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        update(TimePerFrame);
        render();
    }
}

void Game::processEvents(){
    sf::Event event;

    while (mWindow.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)); 
                    
                } 
                break;
            case sf::Event::MouseMoved:
                sf::Vector2f mousePos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
                mWorld.HoverCheck(mousePos);
                break;
        }
    }
}

void Game::update(sf::Time TimePerFrame){
    
}

void Game::render(){
    mWindow.clear(sf::Color::White);
    mWindow.draw(mWorld);
    mWindow.display();
}