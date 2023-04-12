#ifndef World_hpp
#define World_hpp

#include <BaseHeader.hpp>
#include <DataTypes.hpp>
#include <Button.hpp>
#include <set>
#include <vector>
#include <LL.hpp>
#include <DLL.hpp>
#include <CLL.hpp>
#include <DynArr.hpp>
#include <StaArr.hpp>
#include <Queue.hpp>
#include <Stack.hpp>

class World: public sf::Drawable, private sf::NonCopyable {
public:
    LL nLL;
    DLL nDLL;
    CLL nCLL;
    DynArr nDynArr;
    StaArr nStaArr;
    Stack nStack;
    Queue nQueue;
    std::unique_ptr <DataTypes> liveData;

public:
    World();
    void HoverCheck(sf::Vector2f);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void checkPress(sf::Vector2f);
};

#endif //World_hpp