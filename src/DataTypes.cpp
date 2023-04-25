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

void DataTypes::LetsSearch(int X){
    mainGraph = firstGraph;
    if (mainGraph.getSize() == 0)return;

    // std::cout << "List rad of search graph: \n";
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);
        // std::cout << mainGraph.listNode[i]->getRad() << " "; std::cout << '\n';

    // std::cout << "value to find: " << X << '\n';
    int flag = 100;
    // std::cout << "numFrame: " << numFrame << '\n';
    for (int vtx = 0; vtx < mainGraph.getSize(); ++vtx){
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }
        if (mainGraph.getValue(vtx) == X){flag = vtx; break;}
        
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }
    }
}

void DataTypes::LetsInsert(int vtx, int value){
    mainGraph = firstGraph;
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    if (vtx != mainGraph.getSize())
    for (int i = 0; i <= vtx; ++i){
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        } 
        if (i == vtx)break;   
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        }
    }
    if (vtx && vtx < mainGraph.getSize())
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setFoundNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }

    mainGraph.makeNewNode(vtx, value);

    if (vtx < mainGraph.getSize()){
        std::shared_ptr <Node> res = std::make_shared <Node> (CircleRad, std::to_string(value), ResourceManager::getFont(), 
                                    textSize, NewNodeColor,sf::Vector2f(mainGraph.newNode->getNodePosition().x, 350.f));
        mainGraph.newNode->nextNode = res; mainGraph.newNode->setArrow();

        for (int i = 1; i <= numFrame; ++i){
            res->setPosition(ResourceManager::changePosition(mainGraph.newNode->getNodePosition(), mainGraph.listNode[vtx]->getNodePosition(), i/numFrame));
            mainGraph.newNode->setArrow();
            gameGlobal->runBreak();
        }
        mainGraph.newNode->nextNode = mainGraph.listNode[vtx];
    }

    if (vtx-1 >= 0){
        std::shared_ptr <Node> res = std::make_shared <Node> (CircleRad, std::to_string(value), ResourceManager::getFont(), 
                                    textSize, NewNodeColor,sf::Vector2f(mainGraph.listNode[vtx-1]->getNodePosition()));
        mainGraph.listNode[vtx-1]->nextNode = res; mainGraph.listNode[vtx-1]->setArrow();

        for (int i = 1; i <= numFrame; ++i){
            res->setPosition(ResourceManager::changePosition(mainGraph.listNode[vtx-1]->getNodePosition(), mainGraph.newNode->getNodePosition(), i/numFrame));
            mainGraph.listNode[vtx-1]->setArrow();
            gameGlobal->runBreak();
        }
        mainGraph.listNode[vtx-1]->nextNode = mainGraph.newNode;
    }

    sf::Vector2f startPos = mainGraph.newNode->getNodePosition();
    sf::Vector2f endPos = sf::Vector2f(mainGraph.newNode->getNodePosition().x, 250.f);
    for (int i = 1; i <= numFrame; ++i){
        mainGraph.newNode->setPosition(ResourceManager::changePosition(startPos, endPos, i/numFrame));
        mainGraph.newNode->setArrow(); 
        if (vtx - 1 >= 0)mainGraph.listNode[vtx-1]->setArrow();
        gameGlobal->runBreak();
    }
}

void DataTypes::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    // if (!isTurn)return;
    target.draw(mainButton); target.draw(timeText);
    target.draw(upSpeed); target.draw(downSpeed);
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
    numFrame = 1.f/xtime * 60;
}

void DataTypes::checkKeyInput(sf::Event& event){
    for (auto i : inputBox)if (i->cursorOn)i->handleEvent(event);
}
