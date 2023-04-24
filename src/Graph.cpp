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
        for (int i = 0; i < other.listNode.size(); ++i)
            this->listNode[i]->changeSizeNode(this->listNode[i]->getRad() - CircleRad),
            this->listNode[i]->setText(std::to_string(other.getValue(i))),
            this->listNode[i]->changeSizeNode(this->listNode[i]->getRad() - other.listNode[i]->getRad()),
            std::cout << std::to_string(other.getValue(i)) << " "; std::cout << '\n';
        this->setNumber = other.setNumber;
    }
    return *this;
}

void Graph::init(){
    init(ResourceManager::random(2,6));
}

void Graph::init(int x){
    std::vector <std::string> s;
    for (int i = 0; i < x; ++i)s.push_back(std::to_string(randomNodeValue()));
    init(x,s);
}

void Graph::init(int x, std::vector <std::string> s){
    *n = x; listNode.clear();
    if (!n)return;

    leftBound = 800 - (100*(*n) - arrowLength ) / 2;
    for (int i = 0; i < s.size(); ++i){
        listNode.push_back(std::make_shared <Node> (19.f, s[i], ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(leftBound + 10 + 100*i, 250.f)));
    }        
    setNode();              
    for (int i = 0; i < s.size(); ++i)listNode[i]->changeSizeNode(CircleRad / numFrame * (numFrame-1));
}

void Graph::setValue(int vtx, int value){
    if (vtx >= listNode.size())return;
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

void Graph::removeNode(int vt){
    int nn = *n;
    if (!nn)return;
    listNode[vt] = nullptr;
    for (int i = vt; i < nn-1; ++i)listNode[i] = listNode[i+1];
    listNode[nn-1] = nullptr;
    --(*n);
    setNode();
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

void Graph::removeFoundNode(int vtx, float ratio){
    listNode[vtx]->setOutlineColor(FoundNodeColor);
    listNode[vtx]->setNodeColor(backgroundColor);
    listNode[vtx]->setTextColor(FoundNodeColor);
    gameGlobal->runBreak();
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (listNode.empty())return;
    for (int i = 0; i < *n; ++i)target.draw(*listNode[i]);
}