#ifndef DLL_hpp
#define DLL_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>

class DLL: public DataTypes{
public:
    DLL();
    DLL(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );
    // bool isTurn;
};

#endif // DLL_hpp