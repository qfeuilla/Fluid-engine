
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
	double x, y, z;

	Vector3d() : x(0), y(0), z(0) {}
	Vector3d(double x, double y, double z) : x(x), y(y), z(z) {}
	Vector3d operator-(const Vector3d& p) const { return Vector3d(x - p.x, y - p.y, z - p.z); }
	Vector3d operator+(const Vector3d& p) const { return Vector3d(x + p.x, y + p.y, z + p.z); }
	Vector3d operator*(const double p) const { return Vector3d(x * p, y * p, z * p); }
};

double xm = 100, ym = 100, zm = 100;
double h = 2; // size of the edge of the cube
double k = 2;
double radius = 0.02;
int xmh = xm / h, ymh = ym / h, zmh = zm / h;
double pm = std::pow(10, -3); // mass of a particle
double visc = 5e-4f;
double dt = 0.002f;
double SurfaceTensionIntensity = 0.0001f;

#endif