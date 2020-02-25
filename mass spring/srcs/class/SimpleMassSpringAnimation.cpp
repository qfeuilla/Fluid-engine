#include "SimpleMassSpringAnimation.hpp"

SimpleMassSpringAnimation::SimpleMassSpringAnimation() {

}

void SimpleMassSpringAnimation::makeChain(size_t numberOfPoints) {
    if (numberOfPoints == 0)
    {
        return;
    }

    size_t numberOfEdges = numberOfPoints - 1;

    positions.resize(numberOfPoints);
    velocities.resize(numberOfPoints);
    forces.resize(numberOfPoints);
    edges.resize(numberOfEdges);

    for (size_t i = 0; i < numberOfPoints; ++i)
    {
        positions[i].x(-static_cast<double>(i));
    }

    for (size_t i = 0; i < numberOfEdges; ++i)
    {
        edges[i] = Edge{i, i + 1};
    }
}

void SimpleMassSpringAnimation::exportStates(size_t frameIndex) const {

    std::string dir = "./resultat/";
    std::string name = "frame#";
    std::string num;

    num = std::to_string(frameIndex);

    for (int i = 0; i < 4 - num.length(); ++i) {
        name += "0";
    }

    name += num;
    name += "spring_animation.txt";

    std::cout << dir + name << std::endl;

    std::ofstream file(dir + name);

    file << positions.size() << std::endl;

    for (int i = 0; i < positions.size(); ++i) {
        file << positions[i].x() << "," << positions[i].y() << std::endl;
    }
}
