#include "../../includes/sph.h"

Vector2D	lerp(Vector2D a, Vector2D b, double t) {
    return Vector2D(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
}

double	lerp(double a, double b, double t) {
    return (a + t * (b - a));
}

double clamp(double a, double b, double c) {
    if (a < b)
        return (b);
    else if (a > c)
        return (c);
    return (a);
}