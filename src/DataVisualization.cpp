#include <Game.hpp>
#include <BaseHeader.hpp>

float xtime = 1.f;
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

// #include <SFML/Graphics.hpp>
// #include <iostream>

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//     sf::Font font;
//     if (!font.loadFromFile("arial.ttf"))
//     {
//         std::cout << "Error loading font" << std::endl;
//         return -1;
//     }
//     sf::Text text;
//     text.setFont(font);
//     text.setCharacterSize(24);
//     text.setFillColor(sf::Color::Black);
//     text.setPosition(10, 10);
//     sf::RectangleShape cursor(sf::Vector2f(2.f, 24.f));
//     cursor.setFillColor(sf::Color::Black);
//     cursor.setPosition(10.f + text.getLocalBounds().width + 2.f, 10.f);
//     bool showCursor = true;
//     sf::Clock cursorTimer;
//     std::string input = "";
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//             else if (event.type == sf::Event::TextEntered)
//             {
//                 if (event.text.unicode >= '0' && event.text.unicode <= '9' && input.size() < 2)
//                     input += static_cast<char>(event.text.unicode);
//                 else if (event.text.unicode == '\b' && !input.empty())
//                     input.pop_back();
//             }
//         }
//         if (cursorTimer.getElapsedTime().asSeconds() > 0.5f)
//         {
//             showCursor = !showCursor;
//             cursorTimer.restart();
//         }
//         text.setString(input);
//         window.clear(sf::Color::White);
//         window.draw(text);
//         if (showCursor)
//             window.draw(cursor);
//         window.display();
//     }
//     return 0;
// }