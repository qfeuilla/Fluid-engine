
#include "../includes/sph.h"

void SPHSolver2D::advanceTimeStep(float advance_time) {
    beginAdvanceTimeStep(); // preprocess for the Algorithm

    accumulateForces(advance_time);
    timeIntegration(advance_time);
    resolveCollision(advance_time);

    endAdvanceTimeStep(); // postprocess for the Algorithm
}

void SPHSolver2D::accumulateForces(float advance_time) {
    accumulateExternalForces(advance_time);
}

void SPHSolver2D::accumulateExternalForces(float advance_time) {
    Vector2D force;
    Vector2D relativeVel;
    size_t n = particle_datas.numberOfParticles();

    for (int i = 0; i < n; i++) {
        force = _gravity * pm;
        relativeVel = particle_datas._velocities[i] + wind_dir;
        force = force + (relativeVel * _dragCoefficient);
        particle_datas._forces[i] += force;
    }
}

void SPHSolver2D::beginAdvanceTimeStep() {
    size_t n = particle_datas.numberOfParticles();
    _newPositions.resize(n);
    _newVelocities.resize(n);

    particle_datas._forces.clear();
    particle_datas._forces.resize(n, Vector2D(0, 0));
    particle_datas.comput_neighbors();
}

void SPHSolver2D::endAdvanceTimeStep() {
    size_t n = particle_datas.numberOfParticles();

    for (int i = 0; i < n; i++) {
        particle_datas._velocities[i] = _newVelocities[i];
        particle_datas._positions[i] = _newPositions[i];
    }
}

void SPHSolver2D::timeIntegration(float timeIntervalInSeconds) {
    size_t n = particle_datas.numberOfParticles();
    auto forces = particle_datas._forces;
    auto velocities = particle_datas._velocities;
    auto positions = particle_datas._positions;

    for (int i = 0; i < n; i++) {
        _newVelocities[i] = velocities[i] + (forces[i] / pm) * timeIntervalInSeconds;
        _newPositions[i] = positions[i] + _newVelocities[i] * timeIntervalInSeconds;
    }
}

void SPHSolver2D::resolveCollision(float timeIntervalInSeconds) {
    //resolve border Collision for the moment
    size_t n = particle_datas.numberOfParticles();

    for (int i = 0; i < n; i++) {
        if (_newPositions[i].y < floorPositionY) {
            _newPositions[i].y = floorPositionY;

            if (_newVelocities[i].y < 0.0) {
                _newVelocities[i].y = _newVelocities[i].y * -restitusionCoefficient;
                _newPositions[i].y = _newPositions[i].y + (_newVelocities[i].y * timeIntervalInSeconds);
            }
        }
        if (_newPositions[i].x < wallPositionXl) {
            _newPositions[i].x = wallPositionXl;

            if (_newVelocities[i].x < 0.0) {
                _newVelocities[i].x = _newVelocities[i].x * -restitusionCoefficient;
                _newPositions[i].x = _newPositions[i].x + (_newVelocities[i].x * timeIntervalInSeconds);
            }
        }
        if (_newPositions[i].x > wallPositionXr) {
            _newPositions[i].x = wallPositionXr;

            if (_newVelocities[i].x < 0.0) {
                _newVelocities[i].x = _newVelocities[i].x * -restitusionCoefficient;
                _newPositions[i].x = _newPositions[i].x + (_newVelocities[i].x * timeIntervalInSeconds);
            }
        }
    }
}

void SPHSolver2D::saveActualState() {
    std::string dir = "../render/values/";
    std::string name = "frame#";
    std::string num;
    size_t n = particle_datas.numberOfParticles();

    num = std::to_string(frameIndex);

    for (int i = 0; i < 4 - num.length(); ++i) {
        name += "0";
    }

    name += num;
    name += "2d_fluid_animation.txt";

    //std::cout << dir + name << std::endl;

    std::ofstream file(dir + name);

    file << n << std::endl;

    for (int i = 0; i < n; ++i) {
        file << particle_datas._positions[i].x << "," << particle_datas._positions[i].y << std::endl;
    }
}

void SPHSolver2D::runSimulation(float timeOfSimulation) {
    float timeToAdvance = 1 / fps;

    while (actual_time_seconds < timeOfSimulation) {
        advanceTimeStep(timeToAdvance);
        saveActualState();
        frameIndex++;
        actual_time_seconds += timeToAdvance;
    }
}