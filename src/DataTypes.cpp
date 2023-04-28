#include <DataTypes.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

DataTypes::DataTypes(){};

DataTypes::DataTypes(const sf::Vector2f& position, const sf::Vector2f& size,
           const std::string& text, const sf::Font& font, unsigned int characterSize, int numInput, int graphType):
        mainButton(position, size, text, ResourceManager::getFont(), characterSize,0),
        buttonSize(sf::Vector2f(90.f, 50.f)), buttonSpacing(sf::Vector2f(0.f, 5.f)),
        buttonPosition(sf::Vector2f(10.f, 450.f)), buttonRange(buttonSize + buttonSpacing),
        buttonState(-1),
        mainGraph(graphType), typeGraph(graphType){
            upSpeed = Button(sf::Vector2f(980,10), sf::Vector2f(mainButton.getSize().y/2,mainButton.getSize().y/2), 
                            "U", ResourceManager::getFont(), 15, 0);
            downSpeed = Button(sf::Vector2f(980,10+mainButton.getSize().y/2), sf::Vector2f(mainButton.getSize().y/2,mainButton.getSize().y/2), 
                            "D", ResourceManager::getFont(), 15, 0);
            timeText = sf::Text(std::to_string((int)xtime) + "x", ResourceManager::getFont(), 25);
            timeText.setPosition(sf::Vector2f(upSpeed.getPosition().x - 50,mainButton.getSize().y/2-10));
            timeText.setFillColor(sf::Color::Black);

            previousButton = Button(sf::Vector2f(1050,15), sf::Vector2f(85,50),"Previous", ResourceManager::getFont(), 19, 0);
            nextButton = Button(sf::Vector2f(1150,15), sf::Vector2f(85,50),"Next", ResourceManager::getFont(), 19, 0);

            newNode = nullptr;
        }

void DataTypes::resetAll(){
    buttonState = -1;
    xtime = 1.f; numFrame = 60;
    inputBox.clear();
    Graph newGraph = Graph(typeGraph);
    mainGraph = newGraph;
    // std::cout << "size node of mainGraph: \n";
    // for (int i = 0; i < mainGraph.listNode.size(); ++i)
    //     std::cout << mainGraph.listNode[i]->getRad() << " "; std::cout << '\n';
    
    firstGraph = mainGraph;
    for (int i = 0; i < firstGraph.listNode.size(); ++i)
        firstGraph.listNode[i]->changeSizeNode(firstGraph.listNode[i]->getRad() - CircleRad);
    // for (int i = 0; i < firstGraph.listNode.size(); ++i)
    //     std::cout << firstGraph.listNode[i]->getValue() << " "; std::cout << '\n';
}

void DataTypes::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    // if (!isTurn)return;
    target.draw(mainButton); target.draw(timeText);
    target.draw(upSpeed); target.draw(downSpeed);
    target.draw(previousButton); target.draw(nextButton);
    for (auto res : BaseButton)target.draw(*res);
    if (buttonState != -1){
        for (auto res : (BaseButton[buttonState]->minButton))target.draw(*res);
    }
    for (auto i : inputBox)target.draw(*i);
    //drawgraph
}

void DataTypes::checkHover(sf::Vector2f mousePos){
    mainButton.checkHover(mousePos);
    upSpeed.checkHover(mousePos);
    downSpeed.checkHover(mousePos);
    previousButton.checkHover(mousePos);
    nextButton.checkHover(mousePos);
    for (auto res : BaseButton)res->checkHover(mousePos);
    if (buttonState != -1)
        for (auto res : (BaseButton[buttonState]->minButton))res->checkHover(mousePos);
}

void DataTypes::checkPress(sf::Vector2f mousePos){
    //if (LL_button.checkPress(mousePos))isTurn = 1;
    for (int i = 0; i < BaseButton.size(); ++i)if (BaseButton[i]->checkPress(mousePos))
        buttonState = i, inputBox.clear(); 
    if (upSpeed.checkPress(mousePos))xtime = std::min(xtime + 1, 10.f), timeText.setString(std::to_string((int)xtime)+"x");
    if (downSpeed.checkPress(mousePos))xtime = std::max(xtime - 1, 1.f), timeText.setString(std::to_string((int)xtime) + "x");
    if (previousButton.checkPress(mousePos))mainGraph.getStep(-1);
    if (nextButton.checkPress(mousePos))mainGraph.getStep(1);
    numFrame = 1.f/xtime * 60;
}

void DataTypes::checkKeyInput(sf::Event& event){
    for (auto i : inputBox)if (i->cursorOn)i->handleEvent(event);
}
