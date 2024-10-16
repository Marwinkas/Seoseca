#include "SpriteButton.hpp"
#include "Theme.hpp"

namespace gui
{
void SpriteButton::setSize(const sf::Vector2f& size)
{
    m_size = size;
    if (m_parent != nullptr)
    {
        Widget* parent = m_parent;
        parent->recomputeGeometry();
    }
}
void SpriteButton::setSize(float width, float height)
{
    
    background.setScale((float)(1 / (float)((float)background.getTexture()->getSize().x / (float)getSize().x)), (float)(1 / (float)((float)background.getTexture()->getSize().y / (float)getSize().y)));
    setSize(sf::Vector2f(width, height));
}
void SpriteButton::setIcon(const sf::Texture& texture){
    if(haveicon){

            sf::FloatRect r = m_text.getLocalBounds();
            m_text.setOrigin(r.left + std::round(r.width / 2.f), r.top + std::round(r.height / 2.f));
            m_text.setPosition(60, m_size.y / 2);


        icon.setTexture(icontext);
        icon.setScale((float)(1 / (float)((float)icon.getTexture()->getSize().x / (float)getSize().y)), (float)(1 / (float)((float)icon.getTexture()->getSize().y / (float)getSize().y)));
    }
}

SpriteButton::SpriteButton(const sf::Texture& texture, const sf::String& string,int x,int y):
    Widget(),
    m_pressed(false)
{

    background.setTexture(texture);
    background.setScale((float)(1 / (float)((float)background.getTexture()->getSize().x / (float)getSize().x)), (float)(1 / (float)((float)background.getTexture()->getSize().y / (float)getSize().y)));

    setSize(x,y);


    m_text.setFont(Theme::getFont());
    m_text.setCharacterSize(Theme::textSize);

    setString(string);
    
}


void SpriteButton::setString(const sf::String& string)
{
    m_text.setString(string);
}


const sf::String& SpriteButton::getString() const
{
    return m_text.getString();
}


void SpriteButton::setFont(const sf::Font& font)
{
    m_text.setFont(font);
}


const sf::Font& SpriteButton::getFont() const
{
    return *m_text.getFont();
}


void SpriteButton::setTextSize(size_t size)
{
     background.setScale((float)(1 / (float)((float)background.getTexture()->getSize().x / (float)getSize().x)), (float)(1 / (float)((float)background.getTexture()->getSize().y / (float)getSize().y)));
    m_text.setCharacterSize(size);
}


void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    target.draw(background, states);
    target.draw(icon, states);
    target.draw(m_text, states);
}


// Callbacks -------------------------------------------------------------------

void SpriteButton::onStateChanged(State state)
{
    sf::Vector2f size = getSize();
        switch (state)
    {
    case StateDefault:
        if(selected)background.setTexture(backgroundselected);
        else background.setTexture(backgrounddefault);
        break;
    case StateHovered:
        background.setTexture(backgroundhover);
        break;
    case StatePressed:
        if(selected)background.setTexture(backgroundselected);
        else background.setTexture(backgroundclick);
        break;
    case StateFocused:
        if(selected)background.setTexture(backgroundselected);
        else background.setTexture(backgroundclick);
        break;
    }
}


void SpriteButton::onMouseMoved(float x, float y)
{
    if (isFocused())
    {
        if (containsPoint({x, y}) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            press();
        else
            release();
    }
}


void SpriteButton::onMousePressed(float, float)
{
    press();
}


void SpriteButton::onMouseReleased(float x, float y)
{

    release();
    if (containsPoint({x, y}))
    {
        triggerCallback();
    }
}


void SpriteButton::onKeyPressed(const sf::Event::KeyEvent& key)
{
    if (key.code == sf::Keyboard::Return)
    {
        triggerCallback();
        press();
    }
}


void SpriteButton::onKeyReleased(const sf::Event::KeyEvent& key)
{
    if (key.code == sf::Keyboard::Return)
        release();
}


void SpriteButton::press()
{
    if (!m_pressed)
    {
        m_pressed = true;
        m_text.move(0, 1);
    }
}


void SpriteButton::release()
{
    if (m_pressed)
    {
        m_pressed = false;
        m_text.move(0, -1);
    }
}

}
