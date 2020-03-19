#ifndef SPH_H
#define SPH_H

#include "../classes/particles_stuff.hpp"

static float xm = 200, ym = 200; // max pos
static float h = 4; // size of the edge of the square
static float radius = 0.02; // radius of a particule
static int xmh = xm / h, ymh = ym / h; // max pos in grid size index
static float pm = std::pow(10, -3); // mass of a particle
static float visc = 5e-4f;
static float dt = 0.002f;
static float doi = 1; // distance of interaction

class SPHSolver2D {
public:
    ParticleSystemData2 particle_datas;
    float               actual_time_seconds;
    float               fps;
    double              _dragCoefficient = 1e-4;
    Vector2D            wind_dir = Vector2D(0.0, 0.0);
    Vector2D            _gravity = Vector2D(0.0, -9.8);
    ParticleSystemData2::VectorArray _newPositions;
    ParticleSystemData2::VectorArray _newVelocities;
    int                 frameIndex;
    float               floorPositionY = -40;
    float               wallPositionXl = -40;
    float               wallPositionXr = 120;

    float               restitusionCoefficient = 0.2;

    SPHSolver2D() {}
    SPHSolver2D(const ParticleSystemData2 & datas, float fps) : particle_datas(datas), fps(fps), frameIndex(0), actual_time_seconds(0) { }

    void advanceTimeStep(float advance_time);
    void accumulateForces(float advance_time);
    void accumulateExternalForces(float advance_time);
    void beginAdvanceTimeStep();
    void endAdvanceTimeStep();
    void timeIntegration(float timeIntervalInSeconds);
    void resolveCollision(float timeIntervalInSeconds);
    void saveActualState();
    void runSimulation(float timeOfSimulation);
};


#endif