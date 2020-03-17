#ifndef NEIGHBOR_HPP
#define NEIGHBOR_HPP

#include "../../classes/Vector2D.hpp"

std::deque<std::deque<int>> getNeighbors(std::deque<Vector2D> particles);

float xm = 200, ym = 200; // max pos
float h = 2; // size of the edge of the square
float radius = 0.02; // radius of a particule
int xmh = xm / h, ymh = ym / h; // max pos in grid size index
float pm = std::pow(10, -3); // mass of a particle
float visc = 5e-4f;
float dt = 0.002f;

#endif