#include <Button.hpp>

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,
           const std::string& text, const sf::Font& font, unsigned int characterSize)
        : sf::Text(text, font, characterSize), m_shape(size){
    setPosition(position);
    setFillColor(sf::Color::White);
    setOutlineThickness(2.f);
    setOutlineColor(sf::Color::Black);

    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color::White);
    m_shape.setOutlineThickness(2.f);
    m_shape.setOutlineColor(sf::Color::Black);
}

bool Button::contains(const sf::Vector2f& point){
    sf::FloatRect bounds = getGlobalBounds();
    return bounds.contains(point);
}