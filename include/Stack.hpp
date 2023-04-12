#ifndef Stack_hpp
#define Stack_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>

class Stack: public DataTypes{
public:
    Stack();
    Stack(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );
    // bool isTurn;
};

#endif // Stack_hpp