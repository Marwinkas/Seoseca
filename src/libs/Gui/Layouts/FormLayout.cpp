#include "FormLayout.hpp"
#include "../Theme.hpp"
#include "../Label.hpp"

namespace gui
{

FormLayout::FormLayout():
    m_labelWidth(0.f)
{
}


Widget* FormLayout::addRow(const sf::String& str, Widget* widget)
{
    gui::Label* label = new gui::Label(str);
    if (label->getSize().x > m_labelWidth)
    {
        m_labelWidth = label->getSize().x;
    }
    Layout::add(label);
    Layout::add(widget);
    return widget;
}

Widget* FormLayout::addRow(const sf::String& str, Widget* widget, Widget* widget2)
{
    gui::Label* label = new gui::Label(str);
    if (label->getSize().x > m_labelWidth)
    {
        m_labelWidth = label->getSize().x;
    }
    Layout::add(label);
    Layout::add(widget);
    Layout::add(widget2);
    return widget;
}

void FormLayout::recomputeGeometry()
{
    size_t i = 0;
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Vector2f poswidget2;
    for (Widget* widget = getFirstWidget(); widget != nullptr; widget = widget->m_next)
    {
        if (i == 0)
        {
            // Left-side: label
            widget->setPosition(0, pos.y);
            if (widget->getSize().x > m_labelWidth)
                m_labelWidth = widget->getSize().x;
        }
        else if (i == 1)
        {
            // Right-side: widget
            widget->setPosition(m_labelWidth + 0, pos.y);
            // Row height is at least Theme::getBoxHeight()
            poswidget2 = widget->getSize();
            if (widget->getSize().x > size.x)
                size.x = widget->getSize().x;
                
        }        
        else if (i == 2)
        {
            // Right-side: widget
            widget->setPosition(m_labelWidth + poswidget2.x, pos.y);
            // Row height is at least Theme::getBoxHeight()
            if (widget->getSize().x > size.x)
                size.x = widget->getSize().x;
        }
        ++i;
        size.y = std::max(widget->getSize().y, Theme::getBoxHeight());
    }
    size.x += m_labelWidth;
    
    Widget::setSize(size);
}

}
