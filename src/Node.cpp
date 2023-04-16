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
    m_circle.setOutlineColor(color);
    m_circle.setOutlineThickness(3.f);
    m_circle.setFillColor(sf::Color::White);

      // Set the position and color of the text
    m_text.setFillColor(sf::Color::Black);
    setText(text);

    m_text_directions[TOP].setString("N");
    m_text_directions[TOP].setOrigin(m_text_directions[TOP].getLocalBounds().width / 2.f, m_text_directions[TOP].getLocalBounds().height);
    m_text_directions[TOP].setPosition(sf::Vector2f(position.x, position.y - radius - text_size));
    setDirectionColor(sf::Color::Black,TOP);
    // east text
    m_text_directions[RIGHT].setString("E");
    m_text_directions[RIGHT].setPosition(sf::Vector2f(position.x + radius + text_size, position.y));
    // south text
    m_text_directions[BOT].setString("S");
    m_text_directions[BOT].setStyle(sf::Text::Bold);
    m_text_directions[BOT].setOrigin(m_text_directions[BOT].getLocalBounds().width / 2.f, m_text_directions[BOT].getLocalBounds().height);
    m_text_directions[BOT].setPosition(sf::Vector2f(position.x, position.y + radius + text_size));
    setDirectionColor(sf::Color::Red,BOT);
    // west text
    m_text_directions[LEFT].setString("W");
    m_text_directions[LEFT].setOrigin(m_text_directions[LEFT].getLocalBounds().width / 2.f, m_text_directions[LEFT].getLocalBounds().height);
    m_text_directions[LEFT].setPosition(sf::Vector2f(position.x - radius - text_size, position.y));

    m_arrow = DynArrow(60, color, sf::Vector2f(position.x + radius, position.y), 0.f);
    nextNode = nullptr;
}

void Node::setColor(const sf::Color& color){
    m_color = color;
    m_circle.setFillColor(color);
    m_arrow.setColor(color);
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
       
