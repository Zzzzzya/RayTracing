#pragma once
#include "Head.hpp"

class Perlin {
  public:
    Perlin();
    ~Perlin();
    double noise(const Point3 &p) const;
    double turb(const Point3 &p, int depth) const;

  private:
    static const int point_count = 256;
    Vector3 *randvec;
    int *perm_x;
    int *perm_y;
    int *perm_z;

    static int *generatePerlinPerm();
    static void permute(int *p, int n);
    static double trilinearInterp(double c[2][2][2], double u, double v, double w);
    static double perlinInterp(const Vector3 c[2][2][2], double u, double v, double w);
};