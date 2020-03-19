
#ifndef PARTICLE_STUFF_HPP
#define PARTICLE_STUFF_HPP

#include "../srcs/utils/neighbor.hpp"

class ParticleSystemData2 {
public:
    typedef std::deque<Vector2D> VectorArray;
    
    ParticleSystemData2() {}

    ParticleSystemData2(const VectorArray& positions) : _positions(positions) {
        _neighbors.resize(_positions.size());
        _velocities.resize(_positions.size(), Vector2D(0, 0));
        _forces.resize(_positions.size(), Vector2D(0, 0));
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
        Vector2D sum;
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
        double sum = 0;
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

    VectorArray _positions;
    VectorArray _velocities;
    VectorArray _forces;
    std::deque<double> _densities;
    std::deque<std::deque<int>> _neighbors;
};

#endif