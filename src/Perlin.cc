#include "Perlin.hpp"

Perlin::Perlin() {
    randvec = new Vector3[point_count];
    for (int i = 0; i < point_count; i++) {
        randvec[i] = Vector3::rand();
    }
    perm_x = generatePerlinPerm();
    perm_y = generatePerlinPerm();
    perm_z = generatePerlinPerm();
}

Perlin::~Perlin() {
    delete[] randvec;
    delete[] perm_x;
    delete[] perm_y;
    delete[] perm_z;
}
static inline double xx32x(double x) {
    return x * x * (3 - 2 * x);
}
double Perlin::noise(const Point3 &p) const {
    int i = std::floor(p.x());
    int j = std::floor(p.y());
    int k = std::floor(p.z());

    double u = p.x() - i;
    double v = p.y() - j;
    double w = p.z() - k;
    // u = xx32x(u);
    // v = xx32x(v);
    // w = xx32x(w);
    Vector3 c[2][2][2];
    for (int di = 0; di < 2; di++)
        for (int dj = 0; dj < 2; dj++)
            for (int dk = 0; dk < 2; dk++)
                c[di][dj][dk] = randvec[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];

    return perlinInterp(c, u, v, w);
}

double Perlin::turb(const Point3 &p, int depth) const {
    auto accum = 0.0;
    auto temp = p;
    auto weight = 1.0;
    for (int i = 0; i < depth; i++) {
        accum += weight * noise(temp);
        weight *= 0.5;
        temp *= 2;
    }
    return std::fabs(accum);
}

int *Perlin::generatePerlinPerm() {
    auto p = new int[point_count];
    for (int i = 0; i < point_count; i++)
        p[i] = i;
    permute(p, point_count);
    return p;
}

void Perlin::permute(int *p, int n) {
    for (int i = n - 1; i > 0; i--) {
        int target = random_int(0, i);
        std::swap(p[i], p[target]);
    }
}

double Perlin::trilinearInterp(double c[2][2][2], double u, double v, double w) {
    auto accum = 0.0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                accum += (i * u + (1 - i) * (1 - u)) * (j * v + (1 - j) * (1 - v)) * (k * w + (1 - k) * (1 - w)) *
                         c[i][j][k];
    return accum;
}

double Perlin::perlinInterp(const Vector3 c[2][2][2], double u, double v, double w) {
    auto uu = u * u * (3 - 2 * u);
    auto vv = v * v * (3 - 2 * v);
    auto ww = w * w * (3 - 2 * w);
    auto accum = 0.0;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) {
                Vector3 weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j) * (1 - vv)) * (k * ww + (1 - k) * (1 - ww)) *
                         dot(c[i][j][k], weight_v);
            }

    return accum;
}
