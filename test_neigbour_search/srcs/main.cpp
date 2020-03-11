
#include "../include/neighbour.hpp"

std::map<Vector3d, std::deque<Vector3d>> getNeighbour(std::deque<Vector3d> particles) {
    float xm = 100, ym = 100, zm = 100;
    float h = 10; // size of the edge of the cube
    float xmh = xm / h, ymh = ym / h, zmh = zm / h;
    long int indice;
    int type;
    std::map<int, std::map<int, std::deque<Vector3d>>> buckets;
    std::map<Vector3d, std::deque<Vector3d>> neighbour;
    float x,y,z;
    Vector3d tmp;
    float doi = 2; // distance of interaction


    for(Vector3d p: particles) {
        tmp = Vector3d(p.x / h, p.y / h, p.z / h);
        indice = static_cast<int>(std::floor(tmp.x) + std::floor(tmp.y) * xmh + std::floor(tmp.z) * xmh * ymh);
        x = std::round(std::fmod(tmp.x, 1) * 2);
        y = std::round(std::fmod(tmp.y, 1) * 2);
        z = std::round(std::fmod(tmp.z, 1) * 2);
        type = static_cast<int>(x + y * 3 + z * 9);
        buckets[indice][type].push_back(p);
    } // time without the stocking time into the vector particles for 10 millions is aproximaly 4 seconds without multi threading and optimisation so it is a good start

    return (neighbour);
}

int main(int ac, char **av) {
    std::deque<Vector3d> particles;
    std::map<Vector3d, std::deque<Vector3d>> neighbour;
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
