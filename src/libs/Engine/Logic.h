#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <cmath>
#pragma hdrstop
#include "portable-file-dialogs.h"
#include "Angle.hpp"
struct Vector2
{
    float x;
    float y;

    Vector2() {};
    Vector2(float y, float x)
    {
        this->x = x;
        this->y = y;
    }
    Vector2(const sf::Vector2f &vector2)
    {
        x = vector2.x;
        y = vector2.y;
    }
    void Set(float xpos, float ypos);
    operator sf::Vector2f() const
    {
        sf::Vector2f vector2;
        vector2.x = x;
        vector2.y = y;
        return vector2; // возвращаем ссылку на текущий объект
    }
    Vector2 operator=(const sf::FloatRect &vector2)
    {
        x = vector2.height;
        y = vector2.width;
        return *this; // возвращаем ссылку на текущий объект
    }

    Vector2 operator+(const sf::Vector2f &vector2)
    {
        x += vector2.x;
        y += vector2.y;
        return *this; // возвращаем ссылку на текущий объект
    }
    Vector2 operator=(const sf::Vector2f &vector2)
    {
        x = vector2.x;
        y = vector2.y;
        return *this; // возвращаем ссылку на текущий объект
    }


    Vector2(const sf::Vector2f vector, const sf::Vector2f vector2)
    {
        x = vector2.x + vector.x;
        y = vector2.y + vector.y;
    }
    Vector2(const float vector, const sf::Angle vector2)
    {
        x = vector * cos(vector2.asRadians());
        y = vector * sin(vector2.asRadians());
    }
};
struct Vector3
{
    float x;
    float y;
    float z;
    Vector3() {};
    Vector3(float x, float y,float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Vector4
{
    float x;
    float y;
    float z;
    float v;
    Vector4() {};
    Vector4(float x, float y,float z, float v)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->v = v;
    }
};

struct Indentation
{
    float left;
    float right;
    float up;
    float down;
    Indentation(Vector4 vector4)
    {
        left = vector4.x;
        up = vector4.y;
        right = vector4.z;
        down = vector4.v;

    }
    Indentation(Vector2 vector2)
    {
        left = vector2.x;
        up = vector2.y;
        right = vector2.x;
        down = vector2.y;
    }
    Indentation(float left,float up,float right,float down)
    {
        this->left = left;
        this->up = up;
        this->right = right;
        this->down = down;

    }
    Indentation(float horizontal,float vertical)
    {
        this->left = horizontal;
        this->up = vertical;
        this->right = horizontal;
        this->down = vertical;
    }
};

struct Transform
{
    Vector2 position = Vector2(0, 0);
    Vector2 scale = Vector2(0, 0);
    float rotation = 0;
    Transform() {};
};
struct Parent
{
    bool enable = false;
    Transform transform;

    Parent() {};
};
