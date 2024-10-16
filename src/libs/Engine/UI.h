#include "Angle.hpp"
#include "Logic.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <string>

using namespace std;

enum ShapeForm { Rectangle, Circle, Polygon };
enum Style {
  Regular = 0,
  Bold = 1 << 0,
  Italic = 1 << 1,
  Underlined = 1 << 2,
  StrikeThrough = 1 << 3
};
enum Align {
  LeftUp,
  LeftCenter,
  LeftDown,
  CenterUp,
  Center,
  CenterDown,
  RightUp,
  RightCenter,
  RightDown,
};
Vector2 SetAlignValue(Vector2 transform, Align align);

bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp);
bool mousecollide(Vector2 MousePosition, Vector2 position, Vector2 size);
struct Color {
  float r = 0;
  float g = 0;
  float b = 0;
  float a = 255;

  Color() {};
  Color(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
  }
  Color(float red, float green, float blue, float alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }
  Color(const string text) { Set(text); };
  void Set(float red, float green, float blue);
  void Set(float red, float green, float blue, float alpha);
  void Set(string text);
  operator sf::Color() const {
    sf::Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;

    return color; // возвращаем ссылку на текущий объект
  }
};
struct Text {
  Text() {}
  Transform transform;
  string text;
  sf::Font font;
  Style style;
  Color color;
  Color outlinecolor;
  float outlinethickness;
  float letterspacing; //!< Spacing factor between letters
  float linespacing;
  float rotation = 0;
  Parent parent;
  unsigned int charactersize;
  void Draw(sf::RenderWindow *window);
  Vector2 GetLenght(sf::RenderWindow *window);
};

class shape : public sf::Shape {
public:
  ShapeForm shapeform;
  explicit shape(Vector2 size) {
    shapeform = Rectangle;
    setSize(size);
  }
  explicit shape(float radius, std::size_t pointCount)
      : m_radius(radius), m_pointCount(pointCount) {
    shapeform = Circle;
    update();
  }
  void setSize(const Vector2 &size) {
    m_size = size;
    update();
  }

  const sf::Vector2f &getSize() const { return m_size; }

  virtual std::size_t getPointCount() const {
    return m_pointCount; // fixed, but could be an attribute of the class if
                         // needed
  }

  Vector2 getPointRectangle(size_t index) const {
    switch (index) {
    default:
    case 0:
      return {0, 0};
    case 1:
      return {m_size.x, 0};
    case 2:
      return {m_size.x, m_size.y};
    case 3:
      return {0, m_size.y};
    }
  }
  Vector2 getPointCircle(size_t index) const {
    const sf::Angle angle = static_cast<float>(index) /
                                static_cast<float>(m_pointCount) *
                                sf::degrees(360.f) -
                            sf::degrees(90.f);
    return Vector2(m_radius, m_radius) + Vector2(m_radius, angle);
  }
  virtual sf::Vector2f getPoint(size_t index) const {
    if (shapeform == Rectangle)
      return getPointRectangle(index);
    else if (shapeform == Circle)
      return getPointCircle(index);
    return Vector2(0, 0);
  }

private:
  Vector2 m_size;
  float m_radius;
  size_t m_pointCount = 4;
};

struct Shapes {
  Shapes() {};
  Transform transform;
  int polygon = 3;
  Color color = Color("#FFFFFF");
  ShapeForm shapeform = ShapeForm::Rectangle;
  Align align = Align::LeftUp;
  bool enable;

  void Draw(sf::RenderWindow *window);
};

struct Inputfield : public Shapes {
  Inputfield() {}
  Inputfield(Vector2 Position, Vector2 Scale, Color Color, bool Enable) {
    transform.position = Position;
    transform.scale = Scale;
    color = Color;
    enable = Enable;
  }
  Inputfield(Vector2 Position, Vector2 Scale, bool Enable) {
    transform.position = Position;
    transform.scale = Scale;
    enable = Enable;
  }
  bool hover = false;
  bool clicked = false;
  bool erased;
  Color HoverColor;
  Color ClickColor;
  Text text;
  string playerInput;
  void checking(Vector2 cursorPos, sf::Event event);
  void Draw(sf::RenderWindow *window);

private:
  Color currentcolor;
};
struct Button : public Shapes {
  Button() {}
  Button(Vector2 Position, Vector2 Scale, Color Color, bool Enable) {
    transform.position = Position;
    transform.scale = Scale;
    color = Color;
    enable = Enable;
  }
  Button(Vector2 Position, Vector2 Scale, bool Enable) {
    transform.position = Position;
    transform.scale = Scale;
    enable = Enable;
  }
  bool hover = false;
  bool clicked = false;
  Color HoverColor;
  Color ClickColor;
  Text text;
  void checking(Vector2 cursorPos, sf::Event event);
  void Draw(sf::RenderWindow *window);

private:
  Color currentcolor;
};
