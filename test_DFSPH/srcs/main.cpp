
#include "../include/dfsph.hpp"

int			vecToIndex(Vector3d p) {
	return (static_cast<int>(std::floor(p.x) + std::floor(p.y) * xmh + std::floor(p.z) * xmh * ymh));
}

Vector3d	indexToVector(int p) {
	return (Vector3d(static_cast<int>(std::fmod(p, xmh)), static_cast<int>(std::fmod(std::floor(p / xmh), ymh)), static_cast<int>(std::floor(p / (xmh * ymh)))));
}

std::deque<int>     getCellGroup(int type, int cell) {
	Vector3d c = indexToVector(cell);
	std::deque<int> group;
	group.push_back(cell);

	switch (type)
	{
		case 0:
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z - 1))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y - 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1)));
			break;

		case 1:
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1)));
			break;

		case 2:
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z - 1))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y - 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1)));
			break;

		case 3:
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1)));
			break;

		case 4:
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1)));
			break;

		case 5:
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1)));
			break;

		case 6:
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z - 1))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y + 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1)));
			break;

		case 7:
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1)));
			break;

		case 8:
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z - 1))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y + 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z - 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1)));
			break;

		case 9:
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z)));
			break;

		case 10:
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z)));
			break;

		case 11:
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z)));
			break;

		case 12:
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z)));
			break;

		case 14:
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z)));
			break;

		case 15:
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z)));
			break;

		case 16:
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z)));
			break;

		case 17:
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z)));
			break;

		case 18:
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z + 1))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y - 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1)));
			break;

		case 19:
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1)));
			break;

		case 20:
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z + 1))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y - 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1)));
			break;

		case 21:
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1)));
			break;

		case 22:
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1)));
			break;

		case 23:
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1)));
			break;

		case 24:
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z + 1))); 
			group.push_back(vecToIndex(Vector3d(c.x - 1, c.y + 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1)));
			break;

		case 25:
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1)));
			break;

		case 26:
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z)));
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z + 1))); 
			group.push_back(vecToIndex(Vector3d(c.x + 1, c.y + 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z + 1)));
			group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1)));
			break;

		default:
			break;
	}

	return (group);
}

double dist(Vector3d a, Vector3d b) {
	return (std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) + std::pow(a.z - b.z, 2)));
}

std::map<int, std::deque<int>> getNeighbour(std::deque<Vector3d> particles) {
	long int indice;
	int type;
	std::map<long int, std::deque<int>> buckets;
	std::map<int, std::map<int, std::deque<int>>> types;
	std::map<int, std::deque<int>> neighbour;
	std::deque<int> group;
	double x,y,z;
	Vector3d tmp;
	double doi = 1; // distance of interaction
	int part_index = 0;

	for(Vector3d p: particles) {
		tmp = Vector3d(p.x / h, p.y / h, p.z / h);
		indice = vecToIndex(tmp);
		x = std::round(std::fmod(tmp.x, 1) * 2);
		y = std::round(std::fmod(tmp.y, 1) * 2);
		z = std::round(std::fmod(tmp.z, 1) * 2);
		type = static_cast<long int>(x + y * 3 + z * 9);
		buckets[indice].push_back(part_index);
		types[indice][type].push_back(part_index++);
	}


	for (std::pair<int, std::deque<int>> cell: buckets) {
		for (std::pair<int, std::deque<int>> groups: types[cell.first]) {
			group = getCellGroup(groups.first, cell.first);
			for (int particle: groups.second) {
				for (int g: group) {
					for (int possible: buckets[g]) {
						if (dist(particles[possible], particles[particle]) < doi) {
							neighbour[particle].push_back(possible);
						}
					}
				}
			}
		}
	}
	/*
	for (std::pair<int, std::deque<int>> neig: neighbour) {
		std::cout << neig.first << " : ";
		for (int part: neig.second) {
			std::cout << part << " ";
		}
		std::cout << std::endl;
	}*/

	return (neighbour);
}

#define PI 355/113

double CubicSplineFuncion(double s, double h) {
    double alphad;

	alphad = 1 / (4 * PI * std::pow(h,3));
	if (s >= 0 && s < 1)
		return(alphad * (std::pow(2 - s, 3) - (4 * std::pow(1 - s, 3))));
	else if (s < 2 && s >= 0) {
		return (alphad * std::pow(2 - s, 3));
	} else {
		return (0);
	}
}

double CubicSplineFuncionGrad(double s, double h) {
    double alphad;

	alphad = 1 / (4 * PI * std::pow(h,3));
	if (s >= 0 && s < 1)
		return(alphad * ((3 * std::pow(2 - s, 2)) - (4 * (3 * std::pow(1 - s, 2)))));
	else if (s < 2 && s >= 0) {
		return (alphad * (3 * std::pow(2 - s, 2)));
	} else {
		return (0);
	}
}

std::map<int, double> getAlpha(std::map<int, std::deque<int>> neig, std::deque<Vector3d> particules) {
    double sum1;
	double sum2;
	double gauss;

    std::map<int, double> ret;

    for (std::pair<int, std::deque<int>> particule : neig) {
        sum1 = 0;
        sum2 = 0;
		for (int nb: particule.second) {
			gauss = CubicSplineFuncionGrad(dist(particules[particule.first], particules[nb]), h);
            sum1 += pm * gauss;
			sum2 += std::pow(pm * gauss, 2);
        }
        ret[particule.first] = std::pow(sum1, 2) + sum2;
    }
    return(ret);
}

std::map<int, double> getDensity(std::map<int, std::deque<int>> neig, std::deque<Vector3d> particules) {
    double sum;
    std::map<int, double> ret;

    for (std::pair<int, std::deque<int>> particule : neig) {
        sum = 0;
        for (int nb: particule.second) {
            sum += pm * CubicSplineFuncion(dist(particules[particule.first], particules[nb]), h);
        }
        ret[particule.first] = sum;
    }
    return(ret);
}

double viscosity_kernel_laplacian(double r, double radius) {
	return (r <= radius) ? (45.0f * (radius - r) / (PI * powf(radius, 6))) : 0.0f;
}

std::deque<Vector3d> ComputeForces(std::map<int, std::deque<int>> neighbour, std::deque<Vector3d> particles, std::deque<double> mass, double g, std::deque<Vector3d> velocities) {
	std::deque<Vector3d> vel;
	Vector3d a;
	Vector3d b;
	Vector3d tmp;

	for (int i = 0; i < particles.size(); i++) {
		tmp = Vector3d(0, -g, 0) * dt; // gravity
		for (int j: neighbour[i]) {
			a =  a + ((velocities[j] - velocities[i]) * viscosity_kernel_laplacian(dist(particles[i], particles[i]), radius) * mass[j]);
		}
		tmp = tmp + (a * visc * dt); //viscosity
		tmp = tmp + (b * dt); // surface tension
		vel.push_back(velocities[i] + tmp);
	}
	return (vel);
}

int main(int ac, char **av) {
	std::deque<Vector3d> particles;
	std::deque<Vector3d> velocities;
	std::map<int, std::deque<int>> neighbour;
	std::deque<double> mass;
	std::map<int, double> alphas;
	std::map<int, double> densities;
	std::deque<Vector3d> tmpVel;

	// max x y z
	double xm = 100, ym = 100, zm = 100;
	double x,y,z;

	std::ifstream datas("scene/scene1.txt");
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
				case 2:
					z = std::stof(val);
			}
		}
		std::getline(datas, val);
		particles.push_back(Vector3d(x, y, z));
		velocities.push_back(Vector3d(0, 0, 0));
		mass.push_back(10e-3);
	}
	datas.close();

	std::cout << particles.size() << std::endl;

	// step 1: update neighborhodd
	neighbour = getNeighbour(particles);
	// step 2: compute density and alpha
	densities = getDensity(neighbour,  particles);
	alphas = getAlpha(neighbour, particles);
	/*
	for (std::pair<int, double> al: alphas) {
		std::cout << al.first << " : " << al.second << std::endl;
	}*/
	// step 4: compute forces
	tmpVel = ComputeForces(neighbour, particles, mass, 9.81, velocities);

	// step 5: update deltaT

	// step 6: compute velocitie

	// step 7: correct density error

	// step 8: update pos

	// step 9: correct divergence error

	// step 10: update velocities

	// step 11: save frame;
}
