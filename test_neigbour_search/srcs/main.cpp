
#include "../include/neighbour.hpp"


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
			
			break;

		case 8:
			
			break;

		case 9:
			
			break;

		case 10:
			
			break;

		case 11:
			
			break;

		case 12:
			
			break;

		case 13:
			
			break;

		case 14:
			
			break;

		case 15:
			
			break;

		case 16:
			
			break;

		case 17:
			
			break;

		case 18:
			
			break;

		case 19:
			
			break;

		case 20:
			
			break;

		case 21:
			
			break;

		case 22:
			
			break;

		case 23:
			
			break;

		case 24:
			
			break;

		case 25:
			
			break;

		case 26:
			
			break;

		default:
			break;
	}

	/*
	group.push_back(vecToIndex(Vector3d(c.x - 1, c.y - 1, c.z - 1))); 
	group.push_back(vecToIndex(Vector3d(c.x - 1, c.y - 1, c.z))); 
	group.push_back(vecToIndex(Vector3d(c.x - 1, c.y - 1, c.z + 1))); 
	group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z - 1))); 
	group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z))); 
	group.push_back(vecToIndex(Vector3d(c.x - 1, c.y, c.z + 1))); 
	group.push_back(vecToIndex(Vector3d(c.x - 1, c.y + 1, c.z - 1))); 
	group.push_back(vecToIndex(Vector3d(c.x - 1, c.y + 1, c.z))); 
	group.push_back(vecToIndex(Vector3d(c.x - 1, c.y + 1, c.z + 1))); 
	group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z - 1))); 
	group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z))); 
	group.push_back(vecToIndex(Vector3d(c.x, c.y - 1, c.z + 1))); 
	group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z - 1))); 
	group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z))); 
	group.push_back(vecToIndex(Vector3d(c.x, c.y, c.z + 1))); 
	group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z - 1))); 
	group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z))); 
	group.push_back(vecToIndex(Vector3d(c.x, c.y + 1, c.z + 1))); 
	group.push_back(vecToIndex(Vector3d(c.x + 1, c.y - 1, c.z - 1))); 
	group.push_back(vecToIndex(Vector3d(c.x + 1, c.y - 1, c.z))); 
	group.push_back(vecToIndex(Vector3d(c.x + 1, c.y - 1, c.z + 1))); 
	group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z - 1))); 
	group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z))); 
	group.push_back(vecToIndex(Vector3d(c.x + 1, c.y, c.z + 1))); 
	group.push_back(vecToIndex(Vector3d(c.x + 1, c.y + 1, c.z - 1))); 
	group.push_back(vecToIndex(Vector3d(c.x + 1, c.y + 1, c.z))); 
	group.push_back(vecToIndex(Vector3d(c.x + 1, c.y + 1, c.z + 1))); */
	return (group);
}

std::map<int, std::deque<int>> getNeighbour(std::deque<Vector3d> particles) {
	long int indice;
	int type;
	std::map<int, std::deque<int>> buckets;
	std::map<int, std::map<int, std::deque<int>>> types;
	std::map<int, std::deque<int>> neighbour;
	std::deque<int> group;
	float x,y,z;
	Vector3d tmp;
	float doi = 2; // distance of interaction
	int part_index = 0;

	for(Vector3d p: particles) {
		tmp = Vector3d(p.x / h, p.y / h, p.z / h);
		indice = vecToIndex(tmp);
		x = std::round(std::fmod(tmp.x, 1) * 2);
		y = std::round(std::fmod(tmp.y, 1) * 2);
		z = std::round(std::fmod(tmp.z, 1) * 2);
		type = static_cast<int>(x + y * 3 + z * 9);
		buckets[indice].push_back(part_index);
		types[indice][type].push_back(part_index++);
	}


	for (std::pair<int, std::deque<int>> cell: buckets) {
		for (std::pair<int, std::deque<int>> groups: types[cell.first]) {
			group = getCellGroup(groups.first, cell.first);
			for (int particule: groups.second) {
				for (int g: group) {
					for (int possible: buckets[g]) {

					}
				}
			}
			//std::cout << cell.first << " : type (" << groups.first << ") with number of particule :" << groups.second.size() << std::endl;
		}
	}

	std::cout << buckets[-1].size() << std::endl;

	return (neighbour);
}

int main(int ac, char **av) {
	std::deque<Vector3d> particles;
	std::map<int, std::deque<int>> neighbour;
	// max x y z
	float xm = 100, ym = 100, zm = 100;
	float x,y,z;

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
	}
	datas.close();

	std::cout << particles.size() << std::endl;

	neighbour = getNeighbour(particles);
}
