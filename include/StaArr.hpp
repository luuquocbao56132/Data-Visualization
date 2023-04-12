#ifndef StaArr_hpp
#define StaArr_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>

class StaArr: public DataTypes{
public:
    StaArr();
    StaArr(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );
    // bool isTurn;
};

#endif // StaArr_hpp