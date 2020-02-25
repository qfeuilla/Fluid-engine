#ifndef SIMPLE_MASS_SPRING_ANIMATION_HPP
# define SIMPLE_MASS_SPRING_ANIMATION_HPP

# include "PhysiqueAnimation.hpp"
# include "Vector3D.hpp"
# include <string>
# include <vector>
# include <fstream>
# include <iostream>
# include "Constraint.hpp"

class SimpleMassSpringAnimation: public PhysicsAnimation
{
public:
    struct Edge {
        size_t  first;
        size_t  second;
    };

    std::vector<Vector3d> positions;
    std::vector<Vector3d> velocities;
    std::vector<Vector3d> forces;
    std::vector<Edge> edges;

    double mass = 1.0;
    Vector3d gravity = Vector3d(0.0, -9.8, 0.0);
    double stiffness = 500.0;
    double restLength = 1.0;
    double dampingCoefficient = 1.0;
    double dragCoefficient = 0.1;

    double floorPositionY = -7.0;
    double restitusionCoefficient = 0.1;

    Vector3d windDir;

    std::vector<Constraint> constraints;

    SimpleMassSpringAnimation();

    void makeChain(size_t numberOfPoints);

    void exportStates(size_t frameIndex) const; // save data in a file for visualisation

protected:
    void onAdvanceTimeStep(double timeIntervalInSeconds) override {

        size_t numberOfPoints = positions.size();
        size_t numberOfEdges = edges.size();

        for (size_t i = 0; i < numberOfPoints ; ++i) {
            //Gravity
            forces[i] = gravity * mass;

            //Air
            Vector3d relativeVel = velocities[i] - windDir;
            forces[i] += relativeVel * (- dragCoefficient);
        }


        for (size_t i = 0; i < numberOfEdges; ++i) {
            size_t pointIndex0 = edges[i].first;
            size_t pointIndex1 = edges[i].second;

            // Compute spring force
            Vector3d pos0 = positions[pointIndex0];
            Vector3d pos1 = positions[pointIndex1];
            Vector3d r = pos0 - pos1;

            double distance = r.length();

            if (distance > 0.0) {
                Vector3d force = r.normalize() * -stiffness * (distance - restLength);
                forces[pointIndex0] += force;
                forces[pointIndex1] -= force;
            }

            // Add Damping force
            Vector3d vel0 = velocities[pointIndex0];
            Vector3d vel1 = velocities[pointIndex1];
            Vector3d relativeVl0 = vel0 - vel1;
            Vector3d damping = relativeVl0 * (- dampingCoefficient);
            forces[pointIndex0] += damping;
            forces[pointIndex1] -= damping;
        }

        // Update States
        for (size_t i = 0; i < numberOfPoints; ++i) {
            // Compute next states
            Vector3d newAcceleration = forces[i] / mass;
            Vector3d newVelocity = velocities[i] + newAcceleration * timeIntervalInSeconds;
            Vector3d newPosition = positions[i] + newVelocity * timeIntervalInSeconds;

            // Collision with floor
            if (newPosition.y() < floorPositionY) {
                newPosition.y(floorPositionY);

                if (newVelocity.y() < 0.0) {
                    newVelocity.y(newVelocity.y() * (-restitusionCoefficient));
                    newPosition.y(newPosition.y() + (newVelocity.y() * timeIntervalInSeconds));
                }
            }
            
            // final Update
            velocities[i] = newVelocity;
            positions[i] = newPosition;
        }

        // Apply constraints
        for (size_t i = 0; i < constraints.size(); ++i) {
            size_t pointIndex = constraints[i].pointIndex;
            positions[pointIndex] = constraints[i].fixedPosition;
            velocities[pointIndex] = constraints[i].fixedVelocity;
        }
    }
};

#endif