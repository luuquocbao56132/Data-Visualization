#ifndef LL_hpp
#define LL_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>

class LL: public DataTypes{
public:
    LL();
    LL(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );

    // bool isTurn;
};

#endif // LL_hpp