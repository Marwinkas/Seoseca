#ifndef GUI_LAYOUT_HPP
#define GUI_LAYOUT_HPP

#include "../Widget.hpp"
#include "../Image.hpp"
#include "../Enums/Enums.hpp"
#include "../../Engine/UI.h"
namespace gui
{

class Widget;
class Label;
class Button;
class FormLayout;

/**
 * Base class for layouts. Layouts are special widgets which act as containers
 * See FormLayout, HBoxLayout and VBoxLayout
 */
class Layout: public Widget
{
public:
    Layout();

    Layout(Orientation orientation){
        this->orientation = orientation;
    };
        Layout(Orientation orientation,Vector2 size){
        this->orientation = orientation;
         this->m_size.y = size.x;
         this->m_size.x = size.y;

    };
            Layout(Orientation orientation,Vector2 size,Vector2 pos){
        this->orientation = orientation;
         this->m_size.x = size.x;
         this->m_size.y = size.y;
         this->m_position = pos;
    };
    ~Layout();
    Indentation padding = Indentation(0,0);
    Indentation margin = Indentation(0,0);
    float gap = 0;
    Orientation orientation = None;
    sf::Sprite background;
    bool havebackground = false;
    bool isform;
    int objectcount;
    float sizex= 0;
    float sizey= 0;
    Widget* addRow(const sf::String& label, Widget* widget);
    float m_labelWidth;
    /**
     * Add a new widget in the container
     * The container will take care of widget deallocation
     * @return added widget
     */
    Widget* add(Widget* widget);
   void remove(int id);
   void deletes(int id);
   void reset();
    /// Helpers
    Button* addButton(const sf::String& string, std::function<void(void)> callback);
    Label* addLabel(const sf::String& string);
    FormLayout* addFormLayout();
    FormLayout* addFormLayout(Vector2 size);
    Layout* addLayout();
    Layout* addLayout(Orientation orientation);
    Layout* addLayout(Orientation orientation,Vector2 size);
    Layout* addLayout(Orientation orientation,Vector2 size,Vector2 pos);
    void setSize(const sf::Vector2f& size);
    void setSize(float widget, float height);
    void recomputeGeometry() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Callbacks ---------------------------------------------------------------
    void onStateChanged(State state) override;
    void onMouseMoved(float x, float y) override;
    void onMousePressed(float x, float y) override;
    void onMouseReleased(float x, float y) override;
    void onMouseWheelMoved(int delta) override;
    void onKeyPressed(const sf::Event::KeyEvent& key) override;
    void onKeyReleased(const sf::Event::KeyEvent& key) override;
    void onTextEntered(sf::Uint32 unicode) override;

    inline Layout* toLayout() override { return this; }
    bool focusNextWidget();
    bool focusPreviousWidget();

    Widget* getFirstWidget();

    /**
     * Give the focus to a widget, if applicable
     * @param state: new state of the widget if it took focus
     * @return true if widget took the focus, otherwise false
     */
    bool focusWidget(Widget* widget);
    
    Widget* m_first;
    Widget* m_last;
    Widget* m_hover;
    Widget* m_focus;
};

}

#endif // GUI_LAYOUT_HPP
