#include <Node.hpp>

Node::Node(float radius, const std::string& text, const sf::Font& font, float text_size, const sf::Color& color, const sf::Vector2f& position) :
    m_radius(radius),
    m_color(color),
    m_position(position),
    m_text(text, font, text_size),
    m_text_directions {sf::Text("", font, text_size), sf::Text("",font,text_size), sf::Text("",font,text_size), sf::Text("",font,text_size)}
{
        // Set the position and color of the circle shape
    m_circle.setRadius(radius);
    m_circle.setOrigin(sf::Vector2f(radius,radius));
    m_circle.setPosition(position);
    m_circle.setOutlineColor(sf::Color::Black);
    m_circle.setOutlineThickness(3.f);
    m_circle.setFillColor(color);

      // Set the position and color of the text
    m_text.setFillColor(sf::Color::Black);
    setText(text);

    m_text_directions[TOP].setString("");
    m_text_directions[TOP].setOrigin(m_text_directions[TOP].getLocalBounds().width / 2.f, m_text_directions[TOP].getLocalBounds().height);
    m_text_directions[TOP].setPosition(sf::Vector2f(position.x, position.y - radius - text_size));
    setDirectionColor(sf::Color::Black,TOP);
    // east text
    m_text_directions[RIGHT].setString("");
    m_text_directions[RIGHT].setPosition(sf::Vector2f(position.x + radius + text_size, position.y));
    // south text
    m_text_directions[BOT].setString("");
    m_text_directions[BOT].setStyle(sf::Text::Bold);
    m_text_directions[BOT].setOrigin(m_text_directions[BOT].getLocalBounds().width / 2.f, m_text_directions[BOT].getLocalBounds().height);
    m_text_directions[BOT].setPosition(sf::Vector2f(position.x, position.y + radius + text_size));
    setDirectionColor(sf::Color::Red,BOT);
    // west text
    m_text_directions[LEFT].setString("");
    m_text_directions[LEFT].setOrigin(m_text_directions[LEFT].getLocalBounds().width / 2.f, m_text_directions[LEFT].getLocalBounds().height);
    m_text_directions[LEFT].setPosition(sf::Vector2f(position.x - radius - text_size, position.y));

    m_arrow = DynArrow(60, sf::Color::Black, sf::Vector2f(position.x + radius, position.y), 0.f);
    nextNode = nullptr;
}

sf::Color Node::changeColor(sf::Color startColor, sf::Color endColor, float transitionTime, int time){
    float dr = time*(float)((int)endColor.r - (int)startColor.r) / (transitionTime * 60);
    float dg = time*(float)((int)endColor.g - (int)startColor.g) / (transitionTime * 60);
    float db = time*(float)((int)endColor.b - (int)startColor.b) / (transitionTime * 60);

    sf::Color currentColor = sf::Color((int)startColor.r + (int)dr, (int)startColor.g + (int)dg, (int)startColor.b + (int)db);
    return currentColor;
}

void Node::setColor(const sf::Color& color){
    m_color = color;
    m_circle.setFillColor(color);
    m_arrow.setColor(color);
}

float Node::getRad(){
    return m_circle.getRadius();
}

float dist2Node(sf::Vector2f x, sf::Vector2f y){
    float height = x.y - y.y, width = x.x - y.x;
    return sqrt(height*height + width*width) - CircleRad*2;
}

float rad2Node(sf::Vector2f x, sf::Vector2f y){
    float height = y.y - x.y, width = y.x - x.x;
    float angle = atan2(1,1 / (height / width)) * 180 / M_PI;
    if (angle < 0)angle += 180;
    if (height < 0)angle += 180; 
    return angle;
}

void Node::changeSizeNode(float rad){
    float rate = (m_radius-rad) / m_radius;
    sf::Vector2f position = m_circle.getPosition();
    m_circle.setRadius(m_radius - rad);
    m_radius -= rad;
    m_circle.setOrigin(sf::Vector2f(m_radius, m_radius));
    m_circle.setPosition(position);
    std::cout << rate << '\n';

    m_text.setCharacterSize(m_text.getCharacterSize()*rate);
    m_text.setPosition(position);
    for (int i = 0; i < 4; ++i)m_text_directions[i].setCharacterSize(m_text_directions[i].getCharacterSize()*rate);
    
    m_arrow.minimizeArrow(m_arrow.getLength() - m_arrow.getLength()*rate); 
}

void Node::setArrow(){
    if (nextNode == nullptr)return;

    float length = dist2Node(getNodePosition(), nextNode->getNodePosition());
    
    rotateArrow(rad2Node(getNodePosition(), nextNode->getNodePosition()));
    m_arrow.minimizeArrow(m_arrow.getLength() - length);

}

void Node::changeText(Direction i, std::string text){
    m_text_directions[i].setString(text);
}

void Node::setText(const std::string& text){
    m_text.setString(text);
    m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height);
    m_text.setPosition(m_position);
}

void Node::setTextBot(std::string text){
    m_text_directions[BOT].setString(text);
    m_text_directions[BOT].setOrigin(m_text_directions[BOT].getLocalBounds().width / 2.f, m_text_directions[BOT].getLocalBounds().height);
    m_text_directions[BOT].setPosition(sf::Vector2f(m_position.x, m_position.y + m_radius + textSize));
}
void Node::setTextTop(std::string text){
    m_text_directions[TOP].setString(text);
    m_text_directions[TOP].setOrigin(m_text_directions[TOP].getLocalBounds().width / 2.f, m_text_directions[TOP].getLocalBounds().height);
    m_text_directions[TOP].setPosition(sf::Vector2f(m_position.x, m_position.y - m_radius - textSize));
}

void Node::setDirectionColor(const sf::Color& color, unsigned int direction){
    m_text_directions[direction].setFillColor(color);
}

void Node::setPartialColor(float percentage){
    m_arrow.setPartialColor(percentage);
}

void Node::rotateArrow(float degrees){
    m_arrow.setRotation(degrees);
    m_arrow.setPosition(sf::Vector2f(m_position.x + m_radius * std::cos(degrees * M_PI / 180.f), m_position.y + m_radius * std::sin(degrees * M_PI / 180.f)));
}

void Node::changeSizeArrow(float length){
    m_arrow.minimizeArrow(length);
}

float Node::getLengthArrow(){
    return m_arrow.getLength();
}

sf::Vector2f Node::getNodePosition(){
    return m_circle.getPosition();
}

bool Node::getString(int t){
    int l = 1, res = 0;
    std::string s = m_text.getString();
    for (int i = s.size()-1; i >= 0; --i)res += l*(s[i] - '0'), l *= 10;
    return (t == res);
}
    
void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_circle, states);
    if (nextNode != nullptr)target.draw(m_arrow, states);
    target.draw(m_text, states);
    for (const auto& text : m_text_directions)
    {
        target.draw(text, states);
    }
}
       