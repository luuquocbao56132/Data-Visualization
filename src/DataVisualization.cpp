#include <Game.hpp>
#include <BaseHeader.hpp>

float xtime = 1.f;
float numFrame = 60.f;
std::shared_ptr <Game> gameGlobal = std::make_shared<Game>();

int main() {
    srand(time(NULL));
    // gameGlobal = std::make_shared <Game> ();
    std::cout << "Game pointer: " << gameGlobal << '\n';
    // gameGlobal = game;
    // std::cout << "Game pointer: " << game << " " << gameGlobal << '\n';
    gameGlobal->run();

    return 0;
}
