#include <Graph.hpp>

Graph::Graph(){
    n = ResourceManager::random(2,5);
    init(n);
    setNode();
}

Graph::Graph(int x){
    n = x;
    init(n);
    setNode();
}

Graph::Graph(int x, std::vector <std::string> s){
    n = x;
    if (!n)return;
    leftBound = 800 - (100*n - 60 ) / 2;
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

void Graph::init(int x){
    listNode.clear();
    n = x;
    leftBound = 800 - (100*n - 60 ) / 2;
    if (!x)return;
    listNode.push_back(randomNode(leftBound+10));
    for (int i = 1; i < n; ++i){
        listNode.push_back(randomNode(leftBound+10+100*i));
        listNode[i-1]->nextNode = listNode[i];
    }
}

int Graph::getSize(){
    return n;
}

void Graph::setNode(){
    if (!n){listNode.clear(); return;}
    for (int i = 0; i < n-1; ++i)listNode[i]->nextNode = listNode[i+1];
    listNode[n-1]->nextNode = nullptr;
    for (int i = 0; i < n; ++i){
        listNode[i]->setArrow();
        listNode[i]->setTextBot("");
    }
    if (listNode.empty())return;
    listNode[n-1]->setTextBot("tail");
    listNode[0]->setTextBot("head");
}

void Graph::removeNode(int vt){
    if (!n)return;
    listNode[vt] = nullptr;
    for (int i = vt; i < n-1; ++i)listNode[i] = listNode[i+1];
    listNode[n-1] = nullptr;
    --n;
    setNode();
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (listNode.empty())return;
    for (int i = 0; i < n; ++i)target.draw(*listNode[i]);
}