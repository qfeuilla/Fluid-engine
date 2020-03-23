
#include "../includes/sph.h"

int main(int ac, char **av) {
    std::deque<Vector2D> particles;
    std::deque<int> tmp;

	double x,y;

	std::ifstream datas("../scene/scene1.txt");
	std::string val;

	while (!datas.eof()) {
		for (int i = 0; i < 3; i++) {
			std::getline(datas, val, ' ');
			if (datas.eof())
				break;
			switch (i) {
				case 0:
					x = std::stof(val);
				case 1:
					y = std::stof(val);
			}
		}
		std::getline(datas, val);
		particles.push_back(Vector2D(x, y));
	}
	datas.close();

    std::cout << "read OK" << std::endl;

    ParticleSystemData2 particle_datas = ParticleSystemData2(particles);

    std::cout << "data OK" << std::endl;

    particle_datas.comput_neighbors();

    std::cout << "neighbor OK" << std::endl;

    SPHSolver2D solver = SPHSolver2D(particle_datas, 30);

    solver.runSimulation(20);

/*
    for (int i = 0; i < particle_datas.numberOfParticles(); i++) {
        tmp = particle_datas.neighbors(i);
        std::cout << "Particle " << i << " : ";
        for (int t: tmp) {
            std::cout << " " << t; 
        }
        std::cout << std::endl;
    }
*/
    return (0);
}