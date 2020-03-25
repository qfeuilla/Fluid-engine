#ifndef SPH_HPP
#define SPH_HPP

#include "../classes/Vector2D.hpp"
#include <cmath>
#include <algorithm>
#include <deque>

#define PI 355/113

using namespace std;

const static Vector2D G(0.f, 12000*-9.8f); // external (gravitational) forces
const static float REST_DENS = 1000.f; // rest density
const static float GAS_CONST = 2000.f; // const for equation of state
const static float H = 10.f; // kernel radius
const static float HSQ = H*H; // radius^2 for optimization
const static float MASS = 65.f; // assume all particles have the same mass
const static float VISC = 200.f; // viscosity constant
const static float DT = 0.0008f; // integration timestep

// smoothing kernels defined in Müller and their gradients
const static float POLY6 = 315.f/(65.f*PI*pow(H, 9.f));
const static float SPIKY_GRAD = -45.f/(PI*pow(H, 6.f));
const static float VISC_LAP = 45.f/(PI*pow(H, 6.f));

// simulation parameters
const static float EPS = H; // boundary epsilon
const static float BOUND_DAMPING = -0.5f;

static int frameIndex = 0;
static float actualTime = 0;

struct Particle {
	Particle(float _x, float _y) : x(_x,_y), v(0.f,0.f), f(0.f,0.f), rho(0), p(0.f) {}
	Vector2D x, v, f;
	float rho, p;
};

deque<deque<int>> neighbors;

// solver data
static deque<Particle> particles;

// rendering projection parameters
const static int WINDOW_WIDTH = 800;
const static int WINDOW_HEIGHT = 600;
static double VIEW_WIDTH = 1000.f;
const static double VIEW_HEIGHT = 1500.f;
static bool movingMax = false;

#endif