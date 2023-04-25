#include <Graph.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

Graph::Graph(){
    n = std::make_shared <int> (ResourceManager::random(3,8));
    init(*n);
}

Graph::Graph(int state){
    stateGraph = state;
    n = std::make_shared <int> (ResourceManager::random(3,8));
    init(*n);
}

// check firstgraph co dung gia tri sau khi gan = chua

Graph& Graph::operator=(Graph& other) {
    if (this != &other) { 
        this->stateGraph = other.stateGraph;
        this->init(other.getSize());
        //kich co size text thay doi nen setText trong node se gap van de
        for (int i = 0; i < other.getSize(); ++i)
            this->listNode[i]->changeSizeNode(this->listNode[i]->getRad() - CircleRad),
            this->listNode[i]->setText(std::to_string(other.getValue(i))),
            this->listNode[i]->changeSizeNode(this->listNode[i]->getRad() - other.listNode[i]->getRad()),
            std::cout << std::to_string(other.getValue(i)) << " "; std::cout << '\n';
        this->setNumber = other.setNumber;
        this->newNode = other.newNode;
    }
    return *this;
}

void Graph::init(){
    init(ResourceManager::random(2,7));
}

void Graph::init(int x){
    std::vector <std::string> s; setNumber.clear();
    for (int i = 0; i < x; ++i)s.push_back(std::to_string(randomNodeValue()));
    init(x,s);
}

void Graph::init(int x, std::vector <std::string> s){
    *n = x; listNode.clear(); newNode = nullptr;
    if (!n)return;

    leftBound = 800 - (100*(*n) - arrowLength ) / 2;
    for (int i = 0; i < s.size(); ++i){
        listNode.push_back(std::make_shared <Node> (19.f, s[i], ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(leftBound + 10 + 100*i, 250.f)));
    }        
    // std::cout << 3 << '\n';
    setNode();              
    for (int i = 0; i < s.size(); ++i)listNode[i]->changeSizeNode(CircleRad / numFrame * (numFrame-1));
}

void Graph::setValue(int vtx, int value){
    if (vtx >= getSize())return;
    listNode[vtx]->setText(std::to_string(value));
}

bool Graph::checkSameNum(int x){
    if (setNumber.find(x) != setNumber.end())return 1;
    return 0;
}

std::string convertIntString(int x){
    std::string res = "";
    while (x){
        res = (char)(x%10 +'0') + res;
        x /= 10;
    }
    return res;
}

int Graph::randomNodeValue(){
    int t = ResourceManager::random(1,maxValue);
    while (checkSameNum(t))t = ResourceManager::random(1, 99);
    setNumber.insert(t);
    return t;
}

int Graph::getSize(){
    return *n;
}

void Graph::setNode(){
    int nn = *n;
    // std::cout << nn << '\n';
    if (!nn){listNode.clear(); return;}
    if (stateGraph != ARRAY){
        for (int i = 0; i < nn-1; ++i)listNode[i]->nextNode = listNode[i+1];
        listNode[nn-1]->nextNode = nullptr;
    }
    if (stateGraph == DOUBLYLINKEDLIST){
        for (int i = 1; i < nn; ++i)listNode[i]->prevNode = listNode[i-1];
        listNode[0]->prevNode = nullptr;
    }
    for (int i = 0; i < nn; ++i){
        listNode[i]->changeSizeNode(listNode[i]->getRad() - CircleRad);
        listNode[i]->setArrow();
        listNode[i]->setTextBot("");
        listNode[i]->setTextTop(std::to_string(i));
    }
    if (listNode.empty())return;
    listNode[nn-1]->setTextBot("tail");
    listNode[0]->setTextBot("head");
}

void Graph::setNodeColor(int vtx, sf::Color color){
    listNode[vtx]->setNodeColor(color);
}

int Graph::getValue(int vtx){return listNode[vtx]->getValue();}

void Graph::setArrowColor(int vtx, float ratio){
    //if (listNode[vtx]->)
    listNode[vtx]->setPartialColor(ratio);
}

void Graph::removeNode(int vtx){
    int nn = *n-1;
    int hieu = abs(leftBound - (800 - (100*nn - arrowLength ) / 2));
    leftBound = 800 - (100*nn - arrowLength ) / 2;
    std::vector <sf::Vector2f> startPos, endPos;
    for (int i = 0; i < vtx; ++i){
        startPos.push_back(listNode[i]->getNodePosition());
        endPos.push_back(sf::Vector2f(listNode[i]->getNodePosition().x + hieu, listNode[i]->getNodePosition().y));
    }
    for (int i = vtx+1; i < getSize(); ++i){
        startPos.push_back(listNode[i]->getNodePosition());
        endPos.push_back(sf::Vector2f(listNode[i]->getNodePosition().x - hieu, listNode[i]->getNodePosition().y));
    }

    if (!vtx){
        if (getSize() > 2)listNode[1]->setTextBot("head"), listNode[0]->setTextBot("tmp");
        gameGlobal->runBreak();
        for (int i = 1; i < numFrame; ++i){
            listNode[0]->changeSizeNode(CircleRad / numFrame);
            gameGlobal->runBreak();
        }
        for (int i = 0; i < nn; ++i)listNode[i] = listNode[i+1]; listNode[nn] = nullptr;
        *n = nn; setNode();
        for (int i = 1; i < numFrame; ++i){
            for (int j = 0; j < getSize(); ++j)listNode[j]->setPosition(ResourceManager::changePosition(startPos[j], endPos[j], ((float)i)/numFrame));
            setNode();
            gameGlobal->runBreak();
        }
        return;
    }

    sf::Vector2f startPosNew = listNode[vtx]->getNodePosition();
    sf::Vector2f endPosNew = sf::Vector2f(listNode[vtx]->getNodePosition().x, 350.f);

    //tmp = node[vtx].next;
    for (int i = 1; i <= numFrame; ++i){
        listNode[vtx]->setPosition(ResourceManager::changePosition(startPosNew, endPosNew, i/numFrame));
        setDelNode(vtx,i/numFrame);
        setNode();
        gameGlobal->runBreak();
    }
    listNode[vtx]->setTextBot("tmp");
    
    //node[vtx].next = tmp.next;
    std::shared_ptr <Node> res = std::make_shared <Node> (CircleRad, std::to_string(vtx), ResourceManager::getFont(), 
                                    textSize, NewNodeColor,sf::Vector2f(listNode[vtx]->getNodePosition()));
    listNode[vtx-1]->nextNode = res; listNode[vtx-1]->setArrow();
    startPosNew = listNode[vtx]->getNodePosition();
    if (vtx == nn)endPosNew = listNode[vtx-1]->getNodePosition(); 
        else endPosNew = listNode[vtx+1]->getNodePosition();
    for (int i = 1; i <= numFrame; ++i){
        res->setPosition(ResourceManager::changePosition(startPosNew, endPosNew, i/numFrame));
        listNode[vtx-1]->setArrow();
        gameGlobal->runBreak();
    }

    //del(tmp)
    newNode = listNode[vtx];
    for (int i = vtx; i < nn; ++i)listNode[i] = listNode[i+1]; listNode[nn] = nullptr;
    *n = nn; setNode();
    for (int i = 1; i < numFrame; ++i){
        for (int j = 0; j < getSize(); ++j)listNode[j]->setPosition(ResourceManager::changePosition(startPos[j], endPos[j], ((float)i)/numFrame));
        newNode->changeSizeNode(CircleRad/numFrame);        
        setNode();
        gameGlobal->runBreak();
    }
    newNode = nullptr;
    gameGlobal->runBreak();
    std::cout << 1 << '\n'; 
}

void Graph::makeNewNode(int vtx, int value){
    int nn = getSize()+1;
    int hieu = abs(leftBound - (800 - (100*nn - arrowLength ) / 2));
    leftBound = 800 - (100*nn - arrowLength ) / 2;
    newNode = std::make_shared <Node> (CircleRad, std::to_string(value), ResourceManager::getFont(), 
                                    textSize, NewNodeColor,sf::Vector2f(leftBound + 10 + 100*vtx, 350.f));
    newNode->setOutlineColor(NewNodeColor);
    newNode->changeSizeNode(CircleRad / numFrame * (numFrame-1));
    newNode->setTextColor(sf::Color::White);

    std::vector <sf::Vector2f> startPos, endPos;
    for (int i = 0; i < vtx; ++i){
        startPos.push_back(listNode[i]->getNodePosition());
        endPos.push_back(sf::Vector2f(listNode[i]->getNodePosition().x - hieu, listNode[i]->getNodePosition().y));
    }

    for (int i = vtx; i < getSize(); ++i){
        startPos.push_back(listNode[i]->getNodePosition());
        endPos.push_back(sf::Vector2f(listNode[i]->getNodePosition().x + hieu, listNode[i]->getNodePosition().y));
    }

    for (int i = 2; i < numFrame; ++i){
        for (int j = 0; j < getSize(); ++j)listNode[j]->setPosition(ResourceManager::changePosition(startPos[j], endPos[j], ((float)i)/numFrame));
        setNode();
        newNode->changeSizeNode(-CircleRad/numFrame);
        gameGlobal->runBreak();
    }

     if (vtx < getSize()){
        std::shared_ptr <Node> res = std::make_shared <Node> (CircleRad, std::to_string(value), ResourceManager::getFont(), 
                                    textSize, NewNodeColor,sf::Vector2f(newNode->getNodePosition().x, 350.f));
        newNode->nextNode = res; newNode->setArrow();

        for (int i = 1; i <= numFrame; ++i){
            res->setPosition(ResourceManager::changePosition(newNode->getNodePosition(), listNode[vtx]->getNodePosition(), i/numFrame));
            newNode->setArrow();
            gameGlobal->runBreak();
        }
        newNode->nextNode = listNode[vtx];
    }

    if (vtx-1 >= 0){
        std::shared_ptr <Node> res = std::make_shared <Node> (CircleRad, std::to_string(value), ResourceManager::getFont(), 
                                    textSize, NewNodeColor,sf::Vector2f(listNode[vtx-1]->getNodePosition()));
        listNode[vtx-1]->nextNode = res; listNode[vtx-1]->setArrow();

        for (int i = 1; i <= numFrame; ++i){
            res->setPosition(ResourceManager::changePosition(listNode[vtx-1]->getNodePosition(), newNode->getNodePosition(), i/numFrame));
            listNode[vtx-1]->setArrow();
            gameGlobal->runBreak();
        }
        listNode[vtx-1]->nextNode = newNode;
    }

    sf::Vector2f startPosNew = newNode->getNodePosition();
    sf::Vector2f endPosNew = sf::Vector2f(newNode->getNodePosition().x, 250.f);

    if (getSize() == listNode.size())listNode.push_back(std::make_shared <Node>());
    *n = nn;
    for (int i = getSize() - 1; i > vtx; --i)listNode[i] = listNode[i-1];
    listNode[vtx] = newNode;

    for (int i = 1; i <= numFrame; ++i){
        newNode->setPosition(ResourceManager::changePosition(startPosNew, endPosNew, i/numFrame));
        setNode();
        gameGlobal->runBreak();
    }
    newNode = nullptr;
}

void Graph::setSearchingNode(int vtx, float ratio){
    listNode[vtx]->setOutlineColor(ResourceManager::changeColor(sf::Color::Black, SearchingNodeColor, ratio));
    listNode[vtx]->setNodeColor(ResourceManager::changeColor(FirstNodeColor, SearchingNodeColor, ratio));
    listNode[vtx]->setTextColor(ResourceManager::changeColor(textColorStart, textColorEnd, ratio));
    if (vtx && stateGraph != ARRAY)setArrowColor(vtx-1, ratio);
}

void Graph::removeSearchingNode(int vtx, float ratio){
    listNode[vtx]->setNodeColor(ResourceManager::changeColor(SearchingNodeColor, FirstNodeColor, ratio));
    listNode[vtx]->setTextColor(ResourceManager::changeColor(textColorEnd, SearchingNodeColor, ratio));
}

void Graph::setFoundNode(int vtx, float ratio){
    listNode[vtx]->setOutlineColor(ResourceManager::changeColor(sf::Color::Black, FoundNodeColor, ratio));
    listNode[vtx]->setNodeColor(ResourceManager::changeColor(FirstNodeColor, FoundNodeColor, ratio));
    listNode[vtx]->setTextColor(ResourceManager::changeColor(textColorStart, textColorEnd, ratio));
}

void Graph::setDelNode(int vtx, float ratio){
    listNode[vtx]->setOutlineColor(ResourceManager::changeColor(sf::Color::Black, DelNodeColor, ratio));
    listNode[vtx]->setNodeColor(ResourceManager::changeColor(FirstNodeColor, DelNodeColor, ratio));
    listNode[vtx]->setTextColor(ResourceManager::changeColor(textColorStart, textColorEnd, ratio));
}

void Graph::removeFoundNode(int vtx, float ratio){
    listNode[vtx]->setOutlineColor(FoundNodeColor);
    listNode[vtx]->setNodeColor(backgroundColor);
    listNode[vtx]->setTextColor(FoundNodeColor);
    gameGlobal->runBreak();
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (newNode != nullptr)target.draw(*newNode);
    if (listNode.empty())return;
    for (int i = 0; i < *n; ++i)target.draw(*listNode[i]);
}