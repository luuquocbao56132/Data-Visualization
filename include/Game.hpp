#ifndef Game_hpp
#define Game_hpp

#include <BaseHeader.hpp>
#include <World.hpp>
#include <Button.hpp>

class Game{
    sf::RenderWindow mWindow;
    World mWorld;

    void processEvents();
    void update(sf::Time);
    void render();

    public:
    Game();
    void run();
};

#endif //Game_hpp