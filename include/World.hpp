#ifndef World_hpp
#define World_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <set>
#include <vector>
class World: public sf::Drawable, private sf::NonCopyable {
public:
    Button LL;
    Button DLL;
    Button CLL;
    Button Stack;
    Button Queue;
    Button StaArr;
    Button DynArr;
    std::vector <Button*> BaseButton;

public:
    World();
    void HoverCheck(sf::Vector2f);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
};

#endif //World_hpp