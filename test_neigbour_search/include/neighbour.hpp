
#ifndef NEIGHBOUR_HPP
# define NEIGHBOUR_HPP

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <deque>
#include <map>
#include <cmath>

class  Vector3d {
public:
    float x, y, z;

    Vector3d() : x(0), y(0), z(0) {}
    Vector3d(float x, float y, float z) : x(x), y(y), z(z) {}
};

#endif