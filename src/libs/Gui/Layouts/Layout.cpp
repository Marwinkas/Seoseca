#include "Layout.hpp"
#include "../Button.hpp"
#include "../Label.hpp"
#include "FormLayout.hpp"

namespace gui {

Layout::Layout()
    : m_first(nullptr), m_last(nullptr), m_hover(nullptr), m_focus(nullptr) {}

Layout::~Layout() {
  // Deallocate all widgets
  const Widget *widget = m_first;
  while (widget != nullptr) {
    const Widget *next = widget->m_next;
    delete widget;
    widget = next;
  }
}

Widget *Layout::add(Widget *widget) {
  widget->setParent(this);

  if (m_first == nullptr) {
    widget->id = 0;
    m_first = m_last = widget;
  } else {
    widget->id = m_last->id + 1;
    m_last->m_next = widget;
    widget->m_previous = m_last;
    m_last = widget;
  }
  objectcount++;
  recomputeGeometry();
  return widget;
}
void Layout::remove(int id) {
  Widget *findwidget;
  Widget *widget[200];
  int object = 0;
   for (int i = 0; i < sizeof(widget) / sizeof(widget[0]) - 1; i++) {
    widget[i] = nullptr;
   }
  for (Widget *w = getFirstWidget(); w != nullptr; w = w->m_next) {
    if (w->id == id) {
      findwidget = w;
    } else {
      widget[object] = w;
      object++;
    }
  }
  if (findwidget != nullptr) {
    findwidget->setParent(nullptr);
    findwidget->m_previous = nullptr;
    findwidget->m_next = nullptr;
  }

  m_first = nullptr;
  m_last = nullptr;
  


  for (int i = 0; i < sizeof(widget) / sizeof(widget[0]) - 1; i++) {
    if(widget[i] != nullptr)widget[i]->setParent(this);
    if (m_first == nullptr && widget[i] != nullptr) {
      widget[i]->id = 0;
      m_first = m_last = widget[i];
    }
     else if(widget[i] != nullptr){
      widget[i]->id = m_last->id + 1;
      m_last->m_next = widget[i];
      widget[i]->m_previous = m_last;
      m_last = widget[i];
    }
  }

  recomputeGeometry();
}
void Layout::deletes(int id) {
  Widget *findwidget;
  Widget *widget[200];
  int object = 0;
   for (int i = 0; i < sizeof(widget) / sizeof(widget[0]) - 1; i++) {
    widget[i] = nullptr;
   }
  for (Widget *w = getFirstWidget(); w != nullptr; w = w->m_next) {
    if (w->id == id) {
      findwidget = w;
    } else {
      widget[object] = w;
      object++;
    }
  }
  if (findwidget != nullptr) {
    findwidget->setParent(nullptr);
    findwidget->m_previous = nullptr;
    findwidget->m_next = nullptr;
  }

  m_first = nullptr;
  m_last = nullptr;
  


  for (int i = 0; i < sizeof(widget) / sizeof(widget[0]) - 1; i++) {
    if(widget[i] != nullptr)widget[i]->setParent(this);
    if (m_first == nullptr && widget[i] != nullptr) {
      widget[i]->id = 0;
      m_first = m_last = widget[i];
    }
     else if(widget[i] != nullptr){
      widget[i]->id = m_last->id + 1;
      m_last->m_next = widget[i];
      widget[i]->m_previous = m_last;
      m_last = widget[i];
    }
  }

  recomputeGeometry();
  delete findwidget;
}

void Layout::reset(){
 m_first = m_last = nullptr;


  objectcount = 0;
  recomputeGeometry();

}
Button *Layout::addButton(const sf::String &string,
                          std::function<void(void)> callback) {
  Button *button = new Button(string);
  button->setCallback(callback);
  add(button);
  return button;
}

Label *Layout::addLabel(const sf::String &string) {
  Label *label = new Label(string);
  add(label);
  return label;
}

Widget *Layout::getFirstWidget() { return m_first; }

// Callbacks -------------------------------------------------------------------

void Layout::onStateChanged(State state) {
  if (state == StateDefault) {
    if (m_focus != nullptr) {
      m_focus->setState(StateDefault);
      m_focus = nullptr;
    }
  }
}

void Layout::onMouseMoved(float x, float y) {
  // Pressed widgets still receive mouse move events even when not hovered if
  // mouse is pressed Example: moving a slider's handle
  if (m_focus != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    m_focus->onMouseMoved(x - m_focus->getPosition().x,
                          y - m_focus->getPosition().y);
    if (!m_focus->containsPoint({x, y})) {
      m_hover = nullptr;
    }
  } else {
    // Loop over widgets
    for (Widget *widget = m_first; widget != nullptr; widget = widget->m_next) {
      // Convert mouse position to widget coordinates system
      sf::Vector2f mouse = sf::Vector2f(x, y) - widget->getPosition();
      if (widget->containsPoint(mouse)) {
        if (m_hover != widget) {
          // A new widget is hovered
          if (m_hover != nullptr) {
            m_hover->setState(StateDefault);
            m_hover->onMouseLeave();
          }

          m_hover = widget;
          // Don't send Hovered state if widget is already focused
          if (m_hover != m_focus) {
            widget->setState(StateHovered);
          }
          widget->onMouseEnter();
        } else {
          // Hovered widget was already hovered
          widget->onMouseMoved(mouse.x, mouse.y);
        }
        return;
      }
    }
    // No widget hovered, remove hovered state
    if (m_hover != nullptr) {
      m_hover->onMouseMoved(x, y);
      m_hover->setState(m_focus == m_hover ? StateFocused : StateDefault);
      m_hover->onMouseLeave();
      m_hover = nullptr;
    }
  }
}

void Layout::onMousePressed(float x, float y) {
  if (m_hover != nullptr) {
    // Clicked widget takes focus
    if (m_focus != m_hover) {
      focusWidget(m_hover);
    }
    // Send event to widget
    sf::Vector2f mouse = sf::Vector2f(x, y) - m_hover->getPosition();
    m_hover->onMousePressed(mouse.x, mouse.y);
  }
  // User didn't click on a widget, remove focus state
  else if (m_focus != nullptr) {
    m_focus->setState(StateDefault);
    m_focus = nullptr;
  }
}

void Layout::onMouseReleased(float x, float y) {
  if (m_focus != nullptr) {
    // Send event to the focused widget
    sf::Vector2f mouse = sf::Vector2f(x, y) - m_focus->getPosition();
    m_focus->onMouseReleased(mouse.x, mouse.y);
    m_focus->setState(StateFocused);
  }
}

void Layout::onMouseWheelMoved(int delta) {
  if (m_focus != nullptr) {
    m_focus->onMouseWheelMoved(delta);
  }
}

void Layout::onKeyPressed(const sf::Event::KeyEvent &key) {
  if (key.code == Theme::nextWidgetKey) {
    if (!focusNextWidget())
      // Try to focus first widget if possible
      focusNextWidget();
  } else if (key.code == Theme::previousWidgetKey) {
    if (!focusPreviousWidget())
      focusPreviousWidget();
  } else if (m_focus != nullptr) {
    m_focus->onKeyPressed(key);
  }
}

void Layout::onKeyReleased(const sf::Event::KeyEvent &key) {
  if (m_focus != nullptr) {
    m_focus->onKeyReleased(key);
  }
}

void Layout::onTextEntered(sf::Uint32 unicode) {
  if (m_focus != nullptr) {
    m_focus->onTextEntered(unicode);
  }
}

void Layout::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (havebackground) target.draw(background, states);
  states.transform *= getTransform();
  for (const Widget *widget = m_first; widget != nullptr;
       widget = widget->m_next) {
    target.draw(*widget, states);
  }
}

bool Layout::focusWidget(Widget *widget) {
  if (widget != nullptr) {

    // If another widget was already focused, remove focus
    if (m_focus != nullptr && m_focus != widget) {
      m_focus->setState(StateDefault);
      m_focus = nullptr;
    }
    // Apply focus to widget
    if (widget->isSelectable()) {
      m_focus = widget;
      widget->setState(StateFocused);
      return true;
    }
  }
  return false;
}

bool Layout::focusPreviousWidget() {
  // If a sublayout is already focused
  if (m_focus != nullptr && m_focus->toLayout() != nullptr) {
    if (m_focus->toLayout()->focusPreviousWidget())
      return true;
  }

  Widget *start = m_focus != nullptr ? m_focus->m_previous : m_last;
  for (Widget *widget = start; widget != nullptr; widget = widget->m_previous) {
    Layout *container = widget->toLayout();
    if (container != nullptr) {
      if (container->focusPreviousWidget()) {
        focusWidget(container);
        return true;
      }
    } else if (focusWidget(widget)) {
      return true;
    }
  }

  if (m_focus != nullptr)
    m_focus->setState(StateDefault);
  m_focus = nullptr;
  return false;
}

bool Layout::focusNextWidget() {
  // If a sublayout is already focused
  if (m_focus != nullptr && m_focus->toLayout() != nullptr) {
    if (m_focus->toLayout()->focusNextWidget())
      return true;
  }

  Widget *start = m_focus != nullptr ? m_focus->m_next : m_first;
  for (Widget *widget = start; widget != nullptr; widget = widget->m_next) {
    Layout *container = widget->toLayout();
    if (container != nullptr) {
      if (container->focusNextWidget()) {
        focusWidget(container);
        return true;
      }
    } else if (focusWidget(widget)) {
      return true;
    }
  }

  if (m_focus != nullptr)
    m_focus->setState(StateDefault);
  m_focus = nullptr;
  return false;
}
FormLayout *Layout::addFormLayout() {
  FormLayout *form = new FormLayout();
  add(form);
  return form;
}
FormLayout *Layout::addFormLayout(Vector2 size) {
  FormLayout *form = new FormLayout(size);
  add(form);
  return form;
}
Layout *Layout::addLayout() {
  Layout *form = new Layout();
  add(form);
  return form;
}
Layout *Layout::addLayout(Orientation orientation) {
  Layout *form = new Layout(orientation);
  add(form);

  return form;
}
Layout *Layout::addLayout(Orientation orientation, Vector2 size) {
  
  Layout *form = new Layout(orientation,size);
  Vector2 sz = m_size;
  Vector2 sz2 = form->m_size;
  add(form);
  
  m_size.x = sz.x;
  m_size.y = sz.y;

  form->m_size.x = sz2.x;
  form->m_size.y = sz2.y;

  setSize(m_size.x,m_size.y);
  form->setSize(form->m_size.x,form->m_size.y);
  return form;
}

Layout *Layout::addLayout(Orientation orientation, Vector2 size, Vector2 pos) {
  Layout *form = new Layout(orientation,size,pos);
  add(form);
  return form;
}
  void Layout::setSize(const sf::Vector2f& size)
{
    m_size = size;
    if (m_parent != nullptr)
    {
        Widget* parent = m_parent;
        parent->recomputeGeometry();
    }
}
void Layout::setSize(float width, float height)
{
    setSize(sf::Vector2f(width, height));
     sizex = getSize().x;
     sizey = getSize().y;
}

void Layout::recomputeGeometry() {
  sf::Vector2f pos =
      Vector2(padding.up + margin.up, padding.left + margin.left);
  sf::Vector2f size;



  
  if (orientation == Horizontal) {
    float y= 0;
    for (Widget *w = getFirstWidget(); w != nullptr; w = w->m_next) {
      w->setPosition(pos);
      pos.x += w->getSize().x + gap;
      if(w->getSize().y > y)y = w->getSize().y;
    }
    if(pos.x + padding.left + margin.left + padding.right + margin.right > sizex + padding.left + margin.left + padding.right + margin.right) size.x = pos.x - gap + padding.right + margin.right + padding.left   + margin.left;
    else size.x = sizex + padding.left + margin.left + padding.right + margin.right;
    if(y + padding.up + margin.up + padding.down + margin.down > sizey + padding.up + margin.up + padding.down + margin.down) size.y = y + padding.up + margin.up + padding.down + margin.down;
    else size.y = sizey + padding.up + margin.up + padding.down + margin.down;
    Widget::setSize(size);
  } 
  


  else if (orientation == Vertical) {

    float x= 0;
    for (Widget *w = getFirstWidget(); w != nullptr; w = w->m_next) {
      w->setPosition(pos);
      pos.y += w->getSize().y + gap;
      if(w->getSize().x > x)x = w->getSize().x;
    }
    if(x + padding.left + margin.left + padding.right + margin.right > sizex + padding.left + margin.left + padding.right + margin.right) size.x = x + padding.right + margin.right + padding.left   + margin.left;
    else size.x = sizex + padding.left + margin.left + padding.right + margin.right;
    if(pos.y - gap + padding.up + margin.up + padding.down + margin.down > sizey + padding.up + margin.up + padding.down + margin.down) size.y = pos.y - gap + padding.up + margin.up + padding.down + margin.down;
    else size.y = sizey + padding.up + margin.up + padding.down + margin.down;
    Widget::setSize(size);
  } 
  
  else if (orientation == None) {
    float x = 0;
    float y = 0;

    for (Widget *w = getFirstWidget(); w != nullptr; w = w->m_next) {
      sf::Vector2f posw = w->getPosition();
      sf::Vector2f sizew = w->getSize();

      //if(posw.x < this->getPosition().x)posw.x = this->getPosition().x;

      //if(x < sizew.x + posw.x) x = sizew.x + posw.x;
      //if(y < sizew.y + posw.y) y = sizew.y + posw.y;
    }
    if(x + padding.left + margin.left + padding.right + margin.right > sizex + padding.left + margin.left + padding.right + margin.right) size.x = x + padding.right + margin.right + padding.left   + margin.left;
    else size.x = sizex + padding.left + margin.left + padding.right + margin.right;
    if(y + padding.up + margin.up + padding.down + margin.down > sizey + padding.up + margin.up + padding.down + margin.down) size.y = y + padding.up + margin.up + padding.down + margin.down;
    else size.y = sizey + padding.up + margin.up + padding.down + margin.down;
    Widget::setSize(size);
  }

  if (havebackground) {

    background.setPosition(margin.left + getPosition().x, margin.up + getPosition().y);
    
    background.setScale((float)(1 / (float)((float)background.getTexture()->getSize().x / (float)(size.x - margin.down - margin.up))), (float)(1 / (float)((float)background.getTexture()->getSize().y / (float)(size.y - margin.right - margin.left))));
  }
}
} // namespace gui