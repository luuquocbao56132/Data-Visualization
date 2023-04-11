#include <Button.hpp>

Button::Button(){};

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,
           const std::string& text, const sf::Font& font, unsigned int characterSize):
    m_size(size),
    m_rect(size),
    m_text(text, font, characterSize),
    m_isHovered(false)
{
    m_rect.setFillColor(sf::Color::White);
    m_rect.setOutlineThickness(2.f);
    m_rect.setOutlineColor(sf::Color::Black);
    m_text.setFillColor(sf::Color::Black);
    setPosition(position);
}

void Button::centerOrigin(const sf::Vector2f& pos) {
        m_rect.setOrigin(pos);
        m_text.setOrigin(pos);
        //if (m_rect.getOrigin() == m_text.getOrigin())std::cout << 1;
    }

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_rect, states);
    target.draw(m_text, states);
    if (m_rect.getFillColor() == sf::Color(250,100,250)) std::cout << 3;
}

void Button::setFillColor(const sf::Color& color) {
    m_rect.setFillColor(color);
}

void Button::setOutlineColor(const sf::Color& color) {
    m_rect.setOutlineColor(color);
}

void Button::setOutlineThickness(float thickness) {
    m_rect.setOutlineThickness(thickness);
}

void Button::setPosition(const sf::Vector2f& pos) {
    sf::Transformable::setPosition(pos);
    m_rect.setPosition(pos);
    m_text.setPosition(pos);
    centerOrigin(pos);
}

void Button::setSize(const sf::Vector2f& size) {
    m_size = size;
    m_rect.setSize(m_size);
    //centerOrigin(pos);
}

sf::Vector2f Button::getSize() const {
    return m_size;
}

bool Button::isHovered() const {
    return m_isHovered;
}

void Button::hover() {
    m_isHovered = true;
    m_rect.setFillColor(sf::Color(220, 100, 220));
}

void Button::unhover() {
    m_isHovered = false;
    m_rect.setFillColor(sf::Color::White);
}

sf::FloatRect Button::getGlobalBounds() const {
    return getTransform().transformRect(m_rect.getGlobalBounds());
}