#ifndef Queue_hpp
#define Queue_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>

class Queue: public DataTypes{
public:
    Queue();
    Queue(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );
    // bool isTurn;
};

#endif // Queue_hpp