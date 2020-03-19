
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

    VectorArray _positions;
    VectorArray _velocities;
    VectorArray _forces;
    std::deque<double> _densities;
    std::deque<std::deque<int>> _neighbors;
};

#endif