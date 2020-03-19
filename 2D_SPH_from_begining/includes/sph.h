#ifndef SPH_H
#define SPH_H

#include "../classes/particles_stuff.hpp"

#define PI 355/113

static double xm = 200, ym = 200; // max pos
static double s = 4; // size of the edge of the square
static double radius = 0.02; // radius of a particule
static int xms = xm / s, yms = ym / s; // max pos in grid size index
static double pm = std::pow(10, -3); // mass of a particle
static double visc = 5e-4f;
static double dt = 0.002f;
static double doi = 1; // distance of interaction
static double h = 1; // len for kernel

class SPHSolver2D {
public:
    ParticleSystemData2 particle_datas;
    double               actual_time_seconds;
    double               fps;
    double              _dragCoefficient = 1e-4;
    Vector2D            wind_dir = Vector2D(0.0, 0.0);
    Vector2D            _gravity = Vector2D(0.0, -9.8);
    ParticleSystemData2::VectorArray _newPositions;
    ParticleSystemData2::VectorArray _newVelocities;
    int                 frameIndex;
    double               floorPositionY = -40;
    double               wallPositionXl = -40;
    double               wallPositionXr = 120;

    double               restitusionCoefficient = 0.2;

    SPHSolver2D() {}
    SPHSolver2D(const ParticleSystemData2 & datas, double fps) : particle_datas(datas), fps(fps), frameIndex(0), actual_time_seconds(0) { }

    void advanceTimeStep(double advance_time);
    void accumulateForces(double advance_time);
    void accumulateExternalForces(double advance_time);
    void beginAdvanceTimeStep();
    void endAdvanceTimeStep();
    void timeIntegration(double timeIntervalInSeconds);
    void resolveCollision(double timeIntervalInSeconds);
    void saveActualState();
    void runSimulation(double timeOfSimulation);
};

double stdKernel(double r);
double dist(Vector2D a, Vector2D b);

#endif