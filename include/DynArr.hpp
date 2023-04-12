#ifndef DynArr_hpp
#define DynArr_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>

class DynArr: public DataTypes{
public:
    DynArr();
    DynArr(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );
    // bool isTurn;
};

#endif // DynArr_hpp