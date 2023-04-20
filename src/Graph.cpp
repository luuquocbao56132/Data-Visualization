#include <Graph.hpp>

Graph::Graph(){
    n = std::make_shared <int> (ResourceManager::random(2,5));
    init(*n);
    setNode();
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
    }
    if (listNode.empty())return;
    listNode[nn-1]->setTextBot("tail");
    listNode[0]->setTextBot("head");
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

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (listNode.empty())return;
    for (int i = 0; i < *n; ++i)target.draw(*listNode[i]);
}