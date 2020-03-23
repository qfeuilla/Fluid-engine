
#ifndef PARTICLE_STUFF_HPP
#define PARTICLE_STUFF_HPP

#include "../srcs/utils/neighbor.hpp"

static double pm = 1e-2; // mass of a particle

double dist(Vector2D a, Vector2D b);

// std kernel
double stdKernel(double r);
Vector2D stdKernelGradient(double r, const Vector2D directionToCenter);
double firstDerivativeStdKernel(double r);
double secondDerivativeStdKernel(double r);

// spiky kernel
double spikyKernel(double r);
double firstDerivativeSpikyKernel(double r);
double secondDerivativeSpikyKernel(double r);
Vector2D spikyKernelGradient(double r, const Vector2D directionToCenter);

class ParticleSystemData2 {
public:
    typedef std::deque<Vector2D> VectorArray;
    
    ParticleSystemData2() {}

    ParticleSystemData2(const VectorArray& positions, double targetDensity = 1000) : targetDensity(targetDensity), _positions(positions) {
        _velocities.resize(_positions.size(), Vector2D(0, 0));
        _forces.resize(_positions.size(), Vector2D(0, 0));
        _neighbors.resize(_positions.size());
	    _densities.resize(_positions.size());
	    _pressure.resize(_positions.size());
    }

    virtual ~ParticleSystemData2() {}

    size_t numberOfParticles() const {
        return (_positions.size());
    }

    const Vector2D positions(int a) const {
        return(_positions[a]);
    }
    const Vector2D velocities(int a) const {
        return(_velocities[a]);
    }
    const Vector2D forces(int a) const {
        return(_forces[a]);
    }
    const std::deque<int> neighbors(int a) const {
        return(_neighbors[a]);
    }

    void    comput_neighbors() {
        _neighbors = getNeighbors(_positions);
    }

    Vector2D interpolate(int originIndex, VectorArray values) {
        Vector2D sum = Vector2D(0);
        double distance;
        double weight;

        for (int n: _neighbors[originIndex]) {
            distance = dist(_positions[originIndex], _positions[n]);
            weight = pm / _densities[n] * stdKernel(distance);
            sum += values[n] * weight;
        }
        return (sum);
    }

    double sumOfKernelNearby(int originIndex) {
        double sum = 0.0;
        double distance;

        for (int n: _neighbors[originIndex]) {
            distance = dist(_positions[originIndex], _positions[n]);
            sum += stdKernel(distance);
        }
        return (sum);
    }

    void    compute_densities() {
        size_t n = numberOfParticles();
        double sum;

        for (int i = 0; i < n; i++) {
            sum = sumOfKernelNearby(i);
            _densities[i] = pm * sum;
        }
    }

    Vector2D    gradienAt(int originIndex, std::deque<double> values) {
        Vector2D    sum = Vector2D(0);
        Vector2D    dir;
        Vector2D    origin = _positions[originIndex];
        Vector2D    neighborPos;
        double      distance;

        for (int n: _neighbors[originIndex]) {
            neighborPos = _positions[n];
            distance = dist(origin, neighborPos);
            if (distance > 0.0) {
                dir = (neighborPos - origin) / distance;
                sum += spikyKernelGradient(distance, dir) * 
                        (values[originIndex] / std::pow(_densities[originIndex] , 2)
                        + values[n] / std::pow(_densities[n] , 2))
                        * (_densities[originIndex] * pm);
            }
        }

        return (sum);
    }

    double      laplacianAt(int originIndex, std::deque<double> values) {
        double    sum = 0;
        Vector2D    origin = _positions[originIndex];
        Vector2D    neighborPos;
        double      distance;

        for (int n: _neighbors[originIndex]) {
            neighborPos = _positions[n];
            distance = dist(origin, neighborPos);
            sum += ((values[n] - values[originIndex]) / _densities[n]) * secondDerivativeSpikyKernel(distance) * pm;
        }
        return (sum);
    }

    VectorArray _positions;
    VectorArray _velocities;
    VectorArray _forces;
    std::deque<double> _pressure;
    std::deque<double> _densities;
    std::deque<std::deque<int>> _neighbors;
    double targetDensity; // 1000
};

#endif