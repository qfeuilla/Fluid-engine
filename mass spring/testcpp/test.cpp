#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include "../includes/Vector3D.hpp"

int main() {
    Vector3d test(0, 0, 0);

    std::cout << test.x();

    test.x(5.0);
    std::cout << test.x();
}