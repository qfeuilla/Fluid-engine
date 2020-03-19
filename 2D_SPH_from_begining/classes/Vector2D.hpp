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
    Vector2D(double x) : x(x), y(x) {}
    Vector2D(double x, double y) : x(x), y(y) {}
    ~Vector2D() {}

    double       x, y;

    Vector2D    operator+(const Vector2D& a) const {
        return (Vector2D(x + a.x, y + a.y));
    }
    
    Vector2D    operator-(const Vector2D& a) const {
        return (Vector2D(x - a.x, y - a.y));
    }

    Vector2D    operator*(const double a) const {
        return (Vector2D(x * a, y * a));
    }

    Vector2D    operator/(const double a) const {
        return (Vector2D(x / a, y / a));
    }

    Vector2D    operator+=(const double a) const {
        return (Vector2D(x + a, y + a));
    }

    Vector2D    operator-=(const double a) const {
        return (Vector2D(x - a, y - a));
    }

    void    operator+=(const Vector2D& a) {
        this->x += a.x;
        this->y += a.y;
    }

    void    operator-=(const Vector2D& a) {
        this->x -= a.x;
        this->y -= a.y;
    }

    double       dot(const Vector2D& a) const {
        return (x * a.x + y * a.y);
    }
};

#endif