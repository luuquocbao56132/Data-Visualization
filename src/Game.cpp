#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

Game::Game(): mWindow(sf::VideoMode(1600,800), "Data Visualization", sf::Style::Default, sf::ContextSettings(0, 0, 15)), mWorld{}{
    
}

void Game::run(){
    std::cout << "Game pointer: " << gameGlobal << '\n';
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

void Game::runBreak(){
    std::cout << "Game pointer: " << gameGlobal << '\n';
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
        break; 
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
                    mWorld.checkPress(mousePos);
                } 
                break;
            case sf::Event::MouseMoved:
                sf::Vector2f mousePos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
                mWorld.HoverCheck(mousePos);
                break;
        }
        if (event.type == sf::Event::KeyPressed){
                mWorld.liveData->checkKeyInput(event);
        }
        // std::cout << "event" << '\n';
    }
}

void Game::update(sf::Time TimePerFrame){
    
}

void Game::render(){
    mWindow.clear(sf::Color(238,238,238));
    mWindow.draw(mWorld);
    mWindow.display();
}

void Game::render(int x){
    std::cout << x << '\n';
    mWindow.clear(sf::Color(238,238,238));
    mWindow.draw(mWorld);
    mWindow.display();
}