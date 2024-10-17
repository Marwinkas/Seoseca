#ifndef GUI_SPRITEBUTTON_HPP
#define GUI_SPRITEBUTTON_HPP

#include "Widget.hpp"
#include "Layouts/Layout.hpp"
namespace gui
{

/**
 * Push button linked to a sprite sheet
 */
class SpriteButton: public Widget
{
public:
    SpriteButton(const sf::String& texture, const sf::String& label = "",int x = 0,int y = 0);
    void setString(const sf::String& string);
    const sf::String& getString() const;
    int ids = 0;
    bool hopa = false;
    sf::Sprite background;
    sf::Sprite icon;
    bool haveicon;
    sf::Texture icontext;
    sf::Texture backgrounddefault;
    sf::Texture backgroundhover;
    sf::Texture backgroundclick;
    sf::Texture backgroundselected;
    bool selected = false;
    void setFont(const sf::Font& font);
    const sf::Font& getFont() const;

    void setTextSize(size_t size);
    void setSize(const sf::Vector2f& size) ;
    void setIcon(const sf::Texture& texture);
void  setSize(float width, float height);
    void setTexture(const sf::Texture& texture);

    void onStateChanged(State state) override;
    void onMouseMoved(float x, float y) override;
    void onMousePressed(float x, float y) override;
    void onMouseReleased(float x, float y) override;
    void onKeyPressed(const sf::Event::KeyEvent& key) override;
    void onKeyReleased(const sf::Event::KeyEvent& key) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void press();
    void release();

    sf::Text m_text;
    sf::Sprite m_background;
    bool m_pressed;
};

}

#endif // GUI_SPRITEBUTTON_HPP
