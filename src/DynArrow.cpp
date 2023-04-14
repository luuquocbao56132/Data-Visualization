#include <DynArrow.hpp>

DynArrow::DynArrow(float length, float thickness, sf::Color color, sf::Vector2f position, float angle):
    m_length(length),
    m_thickness(thickness),
    m_color(color),
    m_position(position),
    m_angle(angle)
{
    m_body.setFillColor(color);
    m_body.setSize(sf::Vector2f(length,3.f));

    m_head.setPointCount(3);
    m_head.setFillColor(color);
    m_head.setPoint(0, sf::Vector2f(length, 1.5));
    m_head.setPoint(1, sf::Vector2f(length-12, -4.5));
    m_head.setPoint(2, sf::Vector2f(length-12, 7.5));
    m_head.setOrigin(length-12.f, 1.5f);

    m_particle.setFillColor(sf::Color::Yellow);
    m_particle.setSize(sf::Vector2f(0.f,3.f));
    setPosition(position);
}

void DynArrow::setColor(const sf::Color& color){
    m_color = color;
    m_body.setFillColor(color);
    m_head.setFillColor(color);
}

void DynArrow::setRotation(float degrees){
    m_body.setRotation(degrees);
    m_head.setRotation(degrees);
    m_particle.setRotation(degrees);
}

void DynArrow::setPosition(sf::Vector2f position){
    m_body.setPosition(position);
    m_particle.setPosition(position);
    m_head.setPosition(sf::Vector2f(position.x+m_length-12,position.y+1.5f));
}

void DynArrow::setPartialColor(float percentage){
    float length = m_length * percentage / 100.f;
    m_particle.setSize(sf::Vector2f(length, 3.f));
}

void DynArrow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(m_body, states);
    target.draw(m_head, states);
    if (m_particle.getSize().y > 0)target.draw(m_particle, states);
}


