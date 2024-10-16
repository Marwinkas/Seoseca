#include "UI.h"

void Text::Draw(sf::RenderWindow *window) {
  sf::Text Text;
  Text.setFont(font);
  Text.setFillColor(color);
  Text.setScale(Vector2(1, 1));
  Text.setStyle(style);
  Text.setString(text);
  Text.setCharacterSize(charactersize);
  string texts = text;
  while (Text.getTransform().transformRect(Text.getGlobalBounds()).getSize().x >
         parent.transform.scale.x) {

    text.erase(0, 1);
    Text.setString(text);
  }

  if (parent.enable) {
    Text.setPosition(Vector2(parent.transform.position.x,
                             parent.transform.position.y +
                                 parent.transform.scale.y / 2 +
                                 Text.getTransform()
                                         .transformRect(Text.getGlobalBounds())
                                         .getSize()
                                         .y /
                                     8 -
                                 Text.getTransform()
                                     .transformRect(Text.getGlobalBounds())
                                     .getSize()
                                     .y));
  } else {
    Text.setPosition(transform.position);
  }
  window->draw(Text);
};

Vector2 Text::GetLenght(sf::RenderWindow *window) {
  sf::Text Text;
  Text.setFont(font);
  Text.setFillColor(color);

  Text.setScale(Vector2(1, 1));
  Text.setStyle(style);
  Text.setString(text);
  Text.setCharacterSize(charactersize);

  return Vector2(
      Text.getTransform().transformRect(Text.getGlobalBounds()).getSize().x,
      Text.getTransform().transformRect(Text.getGlobalBounds()).getSize().y);
};

Vector2 SetAlignValue(sf::RenderWindow *window, Vector2 transform, Vector2 size,
                      Align align) {
  Vector2 value;
  if (align == LeftCenter)
    value = Vector2(0, (1080 - window->getSize().y) / 2 + size.y / 2);
  if (align == LeftDown)
    value = Vector2(0, (1080 - window->getSize().y) - size.y);
  if (align == RightUp)
    value = Vector2((1920 - window->getSize().x) - size.x, 0);
  if (align == RightCenter)
    value = Vector2((1920 - window->getSize().x) - size.x,
                    (1080 - window->getSize().y) / 2 - size.y / 2);
  if (align == RightDown)
    value = Vector2((1920 - window->getSize().x) - size.x,
                    (1080 - window->getSize().y) - size.y);
  if (align == CenterUp)
    value = Vector2((1920 - window->getSize().x) / 2 - size.x / 2, 0);
  if (align == Center)
    value = Vector2((1920 - window->getSize().x) / 2 - size.x / 2,
                    (1080 - window->getSize().y) / 2 - size.y / 2);
  if (align == CenterDown)
    value = Vector2((1920 - window->getSize().x) / 2 - size.x / 2,
                    (1080 - window->getSize().y) - size.y);
  value = Vector2(value.x + transform.x, value.y + transform.y);
  return value;
}
void Shapes::Draw(sf::RenderWindow *window) {
  shape Shape(30, 3);
  if (shapeform == Rectangle)
    Shape = shape(transform.scale);
  else if (shapeform == Circle)
    Shape = shape(transform.scale.x, polygon);
  Shape.setPosition(transform.position);
  Shape.setFillColor(color);
  window->draw(Shape);
}

void Inputfield::checking(Vector2 cursorPos, sf::Event event) {
  if (mousecollide(cursorPos, transform.position, transform.scale))
    hover = true;
  else
    hover = false;

  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    if (hover)
      clicked = true;
    else
      clicked = false;
  }

  if (event.type == sf::Event::TextEntered && clicked) {
    if (event.text.unicode < 128) {
      playerInput += event.text.unicode;
      text.text = playerInput;
    }
  }
  if (event.type == sf::Event::KeyPressed &&
      event.key.scancode == sf::Keyboard::Scan::Backspace) {
    erased = true;
  } else if (event.type == sf::Event::KeyReleased &&
             event.key.scancode == sf::Keyboard::Scan::Backspace) {
    erased = false;
  }
  if (erased && clicked && playerInput.length() > 0) {
    playerInput.pop_back();
    text.text = playerInput;
  }
  if (hover && !clicked)
    currentcolor = HoverColor;
  else if (hover && clicked)
    currentcolor = ClickColor;
  else if (!hover && clicked)
    currentcolor = ClickColor;
  else
    currentcolor = color;
}

void Inputfield::Draw(sf::RenderWindow *window) {
  shape Shape(30, 3);
  if (shapeform == Rectangle)
    Shape = shape(transform.scale);
  else if (shapeform == Circle)
    Shape = shape(transform.scale.x, polygon);
  Shape.setPosition(transform.position);
  Shape.setFillColor(currentcolor);
  window->draw(Shape);

  text.parent.enable = true;
  text.parent.transform.position = transform.position;
  text.parent.transform.scale = transform.scale;
  text.Draw(window);
}
void Color::Set(float red, float green, float blue) {
  r = red;
  g = green;
  b = blue;
}
void Color::Set(float red, float green, float blue, float alpha) {
  r = red;
  g = green;
  b = blue;
  a = alpha;
}
char word16[]{'A', 'B', 'C', 'D', 'E', 'F'};
char smallword16[]{'a', 'b', 'c', 'd', 'e', 'f'};
char count16[]{10, 11, 12, 13, 14, 15, 16};
int convert16to10(char c) {
  for (int i = 0; i < sizeof(word16); i++) {
    if (c == word16[i])
      return count16[i] * 16;
  }
  return (c - '0') * 16;
}
int convert16to10Plus(char c) {
  for (int i = 0; i < sizeof(word16) / sizeof(word16[0]); i++) {
    if (c == word16[i])
      return count16[i];
  }
  for (int i = 0; i < sizeof(smallword16) / sizeof(smallword16[0]); i++) {
    if (c == smallword16[i])
      return count16[i];
  }
  return (c - '0');
}
void Color::Set(string text) {

  r = convert16to10(text[1]) + convert16to10Plus(text[2]);
  g = convert16to10(text[3]) + convert16to10Plus(text[4]);
  b = convert16to10(text[5]) + convert16to10Plus(text[6]);
}
bool mousecollide(Vector2 MousePosition, Vector2 position, Vector2 size) {
  if (MousePosition.x >= position.x && MousePosition.x <= position.x + size.x &&
      MousePosition.y >= position.y && MousePosition.y <= position.y + size.y)
    return true;
  return false;
}
void Button::checking(Vector2 cursorPos, sf::Event event) {
  if (hover == false && clicked == false)
    currentcolor = color;
  if (clicked && hover)
    currentcolor = ClickColor;
  if (mousecollide(cursorPos, transform.position, transform.scale) == true) {
    hover = true;
    if (!clicked)
      currentcolor = HoverColor;
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
      clicked = true;
      currentcolor = ClickColor;
    } else if (event.type == sf::Event::MouseButtonReleased &&
               event.mouseButton.button == sf::Mouse::Left) {
      clicked = false;
    }
  } else {
    hover = false;
    clicked = false;
    currentcolor = color;
  }
}
int centrescreenX(sf::RenderWindow *window, Button button) {
  return window->getSize().x / 2 - button.transform.position.x / 2;
}
int centrescreenY(sf::RenderWindow *window, Button button) {
  return window->getSize().y / 2 - button.transform.position.y / 2;
}
void Button::Draw(sf::RenderWindow *window) {
  shape Shape(30, 3);
  if (shapeform == Rectangle)
    Shape = shape(transform.scale);
  else if (shapeform == Circle)
    Shape = shape(transform.scale.x, polygon);
  Shape.setPosition(transform.position);
  Shape.setFillColor(currentcolor);
  window->draw(Shape);

  text.parent.enable = true;
  text.parent.transform.position = transform.position;
  text.parent.transform.scale = transform.scale;
  text.Draw(window);
}