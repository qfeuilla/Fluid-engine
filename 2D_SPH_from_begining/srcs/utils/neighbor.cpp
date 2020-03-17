#include "neighbor.hpp"

int			vecToIndex(Vector2D p) {
	return (static_cast<int>(std::floor(p.x) + std::floor(p.y) * xmh));
}

Vector2D	indexToVector(int p) {
	return (Vector2D(static_cast<int>((p + 1) % xmh), static_cast<int>((p + 1) / xmh)));
}

std::deque<int>     getCellGroup(int type, int cell) {
	Vector2D c = indexToVector(cell);
	std::deque<int> group;
	group.push_back(cell);

	switch (type)
	{
		case 0:
			group.push_back(vecToIndex(Vector2D(c.x - 1, c.y))); 
			group.push_back(vecToIndex(Vector2D(c.x - 1, c.y - 1)));
			group.push_back(vecToIndex(Vector2D(c.x, c.y - 1)));
			break;

		case 1:
			group.push_back(vecToIndex(Vector2D(c.x, c.y - 1)));
			break;

		case 2:
			group.push_back(vecToIndex(Vector2D(c.x + 1, c.y))); 
			group.push_back(vecToIndex(Vector2D(c.x + 1, c.y - 1)));
			group.push_back(vecToIndex(Vector2D(c.x, c.y - 1)));
			break;

		case 3:
			group.push_back(vecToIndex(Vector2D(c.x - 1, c.y)));
			break;

		case 5:
			group.push_back(vecToIndex(Vector2D(c.x + 1, c.y)));
			break;

		case 6:
			group.push_back(vecToIndex(Vector2D(c.x - 1, c.y))); 
			group.push_back(vecToIndex(Vector2D(c.x - 1, c.y + 1)));
			group.push_back(vecToIndex(Vector2D(c.x, c.y + 1)));
			break;

		case 7:
			group.push_back(vecToIndex(Vector2D(c.x, c.y + 1)));
			break;

		case 8:
			group.push_back(vecToIndex(Vector2D(c.x + 1, c.y))); 
			group.push_back(vecToIndex(Vector2D(c.x + 1, c.y + 1)));
			group.push_back(vecToIndex(Vector2D(c.x, c.y + 1)));
			break;

		default:
			break;
	}

	return (group);
}

float dist(Vector2D a, Vector2D b) {
	return (std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)));
}

std::map<int, std::deque<int>> getNeighbour(std::deque<Vector2D> particles) {
	long int indice;
	int type;
	std::map<long int, std::deque<int>> buckets;
	std::map<int, std::map<int, std::deque<int>>> types;
	std::map<int, std::deque<int>> neighbour;
	std::deque<int> group;
	float x,y;
	Vector2D tmp;
	float doi = 1; // distance of interaction
	int part_index = 0;

	for(Vector2D p: particles) {
		tmp = Vector2D(p.x / h, p.y / h);
		indice = vecToIndex(tmp);
		x = std::round(std::fmod(tmp.x, 1) * 2);
		y = std::round(std::fmod(tmp.y, 1) * 2);
		type = static_cast<long int>(x + y * 3);
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