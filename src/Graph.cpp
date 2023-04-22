#include <Graph.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

Graph::Graph(){
    n = std::make_shared <int> (ResourceManager::random(2,5));
    init(*n);
    setNode();
}

Graph& Graph::operator=(Graph& other) {
    if (this != &other) { 
        init(other.getSize());
        for (int i = 0; i < listNode.size(); ++i)
            listNode[i]->setText(std::to_string(other.getValue(i)));
    }
    return *this;
}

void Graph::init(){
    init(ResourceManager::random(2,6));
}

void Graph::init(int x){
    listNode.clear(); *n = x;
    leftBound = 800 - (100*x - 60 ) / 2;
    if (!x)return;
    listNode.push_back(randomNode(leftBound+10));
    for (int i = 1; i < x; ++i){
        listNode.push_back(randomNode(leftBound+10+100*i));
        listNode[i-1]->nextNode = listNode[i];
    }
    setNode();
}

void Graph::init(int x, std::vector <std::string> s){
    *n = x; listNode.clear();
    if (!n)return;
    leftBound = 800 - (100*(*n) - 60 ) / 2;
    listNode.push_back(std::make_shared <Node> (19.f, s[0], ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(leftBound + 10, 250.f)));
    for (int i = 1; i < s.size(); ++i){
        listNode.push_back(std::make_shared <Node> (19.f, s[i], ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(leftBound + 10 + 100*i, 250.f)));
        listNode[i-1]->nextNode = listNode[i];
    }        
    setNode();              
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

std::shared_ptr<Node> Graph::randomNode(int x){
    int t = ResourceManager::random(1, 99);
    while (checkSameNum(t))t = ResourceManager::random(1, 99);
    setNumber.insert(t);
    return std::make_shared <Node> (19.f, convertIntString(t), ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(x, 250.f));
}

int Graph::getSize(){
    return *n;
}

void Graph::setNode(){
    int nn = *n;
    if (!nn){listNode.clear(); return;}
    for (int i = 0; i < nn-1; ++i)listNode[i]->nextNode = listNode[i+1];
    listNode[nn-1]->nextNode = nullptr;
    for (int i = 0; i < nn; ++i){
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

void Graph::setArrowColor(int vtx){
    //if (listNode[vtx]->)
    listNode[vtx]->setPartialColor(100);
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

void Graph::setSearchingNode(int vtx){
    listNode[vtx]->setOutlineColor(SearchingNodeColor);
    listNode[vtx]->setNodeColor(SearchingNodeColor);
    listNode[vtx]->setTextColor(backgroundColor);
    gameGlobal->runBreak();
}

void Graph::removeSearchingNode(int vtx){
    listNode[vtx]->setOutlineColor(SearchingNodeColor);
    listNode[vtx]->setNodeColor(backgroundColor);
    listNode[vtx]->setTextColor(SearchingNodeColor);
    gameGlobal->runBreak();
}

void Graph::setFoundNode(int vtx){
    listNode[vtx]->setOutlineColor(FoundNodeColor);
    listNode[vtx]->setNodeColor(FoundNodeColor);
    listNode[vtx]->setTextColor(backgroundColor);
    gameGlobal->runBreak();
}

void Graph::removeFoundNode(int vtx){
    listNode[vtx]->setOutlineColor(FoundNodeColor);
    listNode[vtx]->setNodeColor(backgroundColor);
    listNode[vtx]->setTextColor(FoundNodeColor);
    gameGlobal->runBreak();
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (listNode.empty())return;
    for (int i = 0; i < *n; ++i)target.draw(*listNode[i]);
}