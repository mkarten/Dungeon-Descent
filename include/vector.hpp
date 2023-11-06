#pragma once

struct Vector2f{
    Vector2f() : x(0.0), y(0.0) {}
    Vector2f(float p_x, float p_y) : x(p_x), y(p_y) {}
    float x, y;
};