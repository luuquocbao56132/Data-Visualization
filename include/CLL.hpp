#ifndef CLL_hpp
#define CLL_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>

class CLL: public DataTypes{
public:
    CLL();
    CLL(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );
    // bool isTurn;
};

#endif // CLL_hpp