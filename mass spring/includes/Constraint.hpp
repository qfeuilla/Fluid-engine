#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

# include "Vector3D.hpp"
class Constraint {

public:
    size_t  pointIndex;
    Vector3d fixedPosition;
    Vector3d fixedVelocity;

    Constraint();
    ~Constraint();
    Constraint(size_t, Vector3d, Vector3d);
};

#endif