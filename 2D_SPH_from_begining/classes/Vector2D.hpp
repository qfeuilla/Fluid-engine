#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <deque>
#include <map>
#include <cmath>

class Vector2D {
public:
    Vector2D() : x(0), y(0) {}
    Vector2D(float x) : x(x), y(x) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    ~Vector2D() {}

    float       x, y;

    Vector2D    operator+(Vector2D &const a) {
        return (Vector2D(x + a.x, y + a.y));
    }
    Vector2D    operator+(Vector2D &const a) {
        return (Vector2D(x - a.x, y - a.y));
    }
    Vector2D    operator*(float a) {
        return (Vector2D(x * a, y * a));
    }
    Vector2D    operator/(float a) {
        return (Vector2D(x / a, y / a));
    }
    float       dot(Vector2D &const a) {
        return (x * a.x + y * a.y);
    }
};

#endif