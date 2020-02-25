#include "../../includes/Constraint.hpp"

Constraint::Constraint() {
}

Constraint::Constraint(size_t index, Vector3d pos, Vector3d vel) {
    pointIndex = index;
    fixedPosition = pos;
    fixedVelocity = vel;
}

Constraint::~Constraint() {}