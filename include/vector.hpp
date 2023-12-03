#pragma once

struct Vector2f{
    Vector2f() : x(0.0), y(0.0) {}
    Vector2f(float p_x, float p_y) : x(p_x), y(p_y) {}
    float x, y;

    // overload operators
    Vector2f operator+(const Vector2f &other) const
    {
        return Vector2f(x + other.x, y + other.y);
    }
    Vector2f operator-(const Vector2f &other) const
    {
        return Vector2f(x - other.x, y - other.y);
    }
    Vector2f operator*(const float &other) const
    {
        return Vector2f(x * other, y * other);
    }
    Vector2f operator/(const float &other) const
    {
        return Vector2f(x / other, y / other);
    }
    Vector2f &operator+=(const Vector2f &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
};

struct Vector2i{
    Vector2i() : x(0), y(0) {}
    Vector2i(int p_x, int p_y) : x(p_x), y(p_y) {}
    int x, y;
};