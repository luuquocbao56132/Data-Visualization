// #include <Game.hpp>

// int main() {
//     Game game;
//     game.run();

//     return 0;
// }


#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "DynArrow.hpp"
#include <windows.h>
#include <string.h>
#include <Node.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Circular Node with Arrow Example", sf::Style::Default, sf::ContextSettings(0, 0, 20));
    sf::Font font;
    if (!font.loadFromFile("consolas.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    // Create the circular node
    // CircularNode node(50.f, {400.f, 300.f}, sf::Color::Green);
    // node.setText("Node", font, 16);
    // node.setPartialColor(0.5f, sf::Color::Yellow);
    // node.setArrowColor(sf::Color::Blue);
    // node.setArrowThickness(4.f);
    // node.setArrowLength(0.6f);

    // Create the arrow
    std::string t = "81";
    DynArrow arrow(60.f, sf::Color::Blue, sf::Vector2f(400.f,400.f), 0.f);
    Node node(19.f,t,font,19,sf::Color::Black,sf::Vector2f(400.f,400.f));
    t = "9";
    node.nextNode = std::make_shared <Node> (19.f,t,font,19,sf::Color::Black,sf::Vector2f(500.f,500.f));
    //arrow.setThickness(4.f);

    sf::Clock clock;
    float percent = 1.f/60, Percent = 1.f/60;  
    //window.setAntialiasing(8);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // if (Percent < 60)
        // arrow.setPartialColor(Percent),
        // Percent += percent,
        node.setArrow();
        if (node.getLengthArrow() > 40)node.changeSizeArrow(5);
        window.clear(sf::Color::White);
        window.draw(node);
        window.draw(*node.nextNode);
        //window.draw(arrow);
        window.display();
    }

    return 0;
}
