#include "../includes/SimpleMassSpringAnimation.hpp"

int main() {

    SimpleMassSpringAnimation anim;

    anim.makeChain(20);
    anim.floorPositionY = -19;
    anim.windDir = Vector3d(0, 0, 0);
    anim.constraints.push_back(Constraint(0, Vector3d(), Vector3d()));

    anim.exportStates(0);

    Frame frame(0, 1.0 / 60.0);

    for (Frame frame(0, 1.0 / 60.0); frame.index < 3600; frame.advance())
    {
        anim.update(frame);
        anim.exportStates(frame.index);
    }
}