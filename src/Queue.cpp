#include <Queue.hpp>

Queue::Queue(){};

Queue::Queue(const sf::Vector2f& position, const sf::Vector2f& size,
           const std::string& text, const sf::Font& font, unsigned int characterSize):
        DataTypes(position, size, "Queue", ResourceManager::getFont(), characterSize,0){

            std::shared_ptr<Button> Create (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*1),
                            buttonSize, "Create", font, 20,0));
            std::shared_ptr<Button> Peek (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*2),
                            buttonSize, "Peek", font, 20,0));
            std::shared_ptr<Button> Push (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*3),
                            buttonSize, "Push", font, 20,1));
            std::shared_ptr<Button> Pop (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*4),
                            buttonSize, "Pop", font, 20,0));

            //BaseButton.push_back(std::make_shared<Button>(Create));
            BaseButton.push_back(Create);
            BaseButton.push_back(Peek);
            BaseButton.push_back(Push);
            BaseButton.push_back(Pop);

            Create->createMinButton({"Empty","Random","Random Sorted","Random Fixed Size","Custom"},
                                    {0,0,0,1,1});
            //std::cout << BaseButton[0]->minButton.size();
            Peek->createMinButton({"Front","Back"},{0,0});
            // isTurn = 0;
        }