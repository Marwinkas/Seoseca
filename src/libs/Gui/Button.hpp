#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include "Widget.hpp"
#include "Utils/ItemBox.hpp"
#include "Layouts/Layout.hpp"
namespace gui
{

/**
 * The Button widget is a simple press button.
 * The callback is triggered when the button is clicked/activated.
 */
class Button: public Widget
{
public:
    Button(const sf::String& string);
    ItemBox<sf::Text> m_box;
    /**
     * Set the displayed button label
     */
    void setString(const sf::String& string);
        void setSize(const sf::Vector2f& size) ;
void  setSize(float width, float height);
    Button* parentobj;
    const sf::String& getString() const;
    int ids = 0;
    bool hopa = false;
protected:
    // Callbacks
    void onStateChanged(State state) override;
    void onMouseMoved(float x, float y) override;
    void onMousePressed(float x, float y) override;
    void onMouseReleased(float x, float y) override;
    void onKeyPressed(const sf::Event::KeyEvent& key) override;
    void onKeyReleased(const sf::Event::KeyEvent& key) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}

#endif // GUI_BUTTON_HPP
