
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
	Vector3d operator-(const Vector3d& p) const { return Vector3d(x - p.x, y - p.y, z - p.z); }
	Vector3d operator+(const Vector3d& p) const { return Vector3d(x + p.x, y + p.y, z + p.z); }
	Vector3d operator*(const float p) const { return Vector3d(x * p, y * p, z * p); }
};

float xm = 100, ym = 100, zm = 100;
float h = 2; // size of the edge of the cube
float k = 2;
float radius = 0.02;
int xmh = xm / h, ymh = ym / h, zmh = zm / h;
float pm = std::pow(10, -3); // mass of a particle
float visc = 5e-4f;
float dt = 0.002f;
float SurfaceTensionIntensity = 0.0001f;

#endif