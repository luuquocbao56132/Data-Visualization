#ifndef Graph_hpp
#define Graph_hpp

#include <BaseHeader.hpp>
#include <Node.hpp>

class Graph: public sf::Transformable, public sf::Drawable {
public:
    Graph();
    void init(int, std::vector <std::string> );
    void init(int );
    void init();
    void setNode();
    bool checkSameNum(int );
    std::shared_ptr <Node> randomNode(int );
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void removeNode(int );
    int getSize();
    std::shared_ptr <int> n;
private:
    int leftBound;
    std::vector <std::shared_ptr <Node>> listNode;
    std::set <int> setNumber;
};

#endif //Graph_hpp