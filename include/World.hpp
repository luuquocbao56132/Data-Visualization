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
    std::shared_ptr <LL> nLL;
    std::shared_ptr <DLL> nDLL;
    std::shared_ptr <CLL> nCLL;
    std::shared_ptr <DynArr> nDynArr;
    std::shared_ptr <StaArr> nStaArr;
    std::shared_ptr <Stack> nStack;
    std::shared_ptr <Queue> nQueue;
    std::shared_ptr <DataTypes> liveData;

public:
    World();
    void HoverCheck(sf::Vector2f);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void checkPress(sf::Vector2f);
};

#endif //World_hpp