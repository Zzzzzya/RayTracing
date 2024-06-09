#include "Vector.hpp"
#include <fstream>
#include <iostream>

using namespace std;
int main() {
    fstream img;
    img.open("../image/image2.ppm", ios::out);

    int imgWidth = 256;
    int imgHeight = 256;

    img << "P3\n" << imgWidth << " " << imgHeight << "\n255\n";

    for (int _h = 0; _h < imgHeight; _h++) {
        std::clog << "\rScanlines remaining: " << imgHeight - _h << " " << std::flush;
        for (int _w = 0; _w < imgWidth; _w++) {
            float r = float(_w) / (imgHeight - 1);
            float g = float(_h) / (imgWidth - 1);
            float b = 0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            img << ir << " " << ig << " " << ib << "\n";
        }
    }

    std::clog << "\rDone.                           \n";

    Vector3 v1(1, 2, 3);
    Vector3 v2(-1, -1, -1);

    std::clog << "v1.len = " << v1.len() << " v2.len = " << v2.len() << "\n";
    std::clog << v1 << " " << v2 << std::endl;
    std::clog << "dot: " << dot(v1, v2) << " cross" << cross(v1, v2) << std::endl;
    return 0;
}