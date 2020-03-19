
#include "../../includes/sph.h"

double dist(Vector2D a, Vector2D b) {
    return (std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)));
}