#include "BVH.hpp"
#include "Camera.hpp"
#include "ImageRTW.hpp"
#include "Materials.hpp"
#include "Scene.hpp"
#include "Texture.hpp"

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

int Scene1() {
    Camera camera;
    Scene world;

    auto texture0 = make_shared<ImageTex>("src/image.png");

    auto material_ground = make_shared<Lambertian>(ColorRGB(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(ColorRGB(0.1, 0.2, 0.5));
    auto material_left = make_shared<Metal>(ColorRGB(0.8, 0.8, 0.8), 0.0);
    auto material_right = make_shared<Metal>(ColorRGB(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground, texture0));
    world.add(make_shared<Sphere>(Point3(0.0, 2, -1.2), 0.5, material_center));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

    world = Scene(make_shared<bvh>(world));

    // Camera cam;
    Camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;

    cam.vfov = 90;
    cam.lookfrom = Point3(0, 0, 0);
    cam.lookat = Point3(0, 0, -1);

    cam.defocus_angle = -0.6;
    cam.focusLen = 1.0;

    cam.Initialize();

    cam.Render(world, "../image/output.ppm");

    return 0;
}

int CheckerSphere() {
    Scene world;

    auto texture0 = make_shared<Noise>(5);

    auto material_center = make_shared<Lambertian>();

    world.add(make_shared<Sphere>(Point3(0.0, -1000, 0.0), 1000, material_center, texture0));
    world.add(make_shared<Sphere>(Point3(0.0, 2, 0.0), 2, material_center, texture0));
    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;

    cam.vfov = 20;
    cam.lookat = Point3(0, 0, 0);
    cam.lookfrom = Point3(13, 2, 3);
    cam.vup = Vector3(0, 1, 0);

    cam.defocus_angle = 0;

    cam.Initialize();
    cam.Render(world, "TurbPerLin.ppm");
    return 0;
}

int Triangle0() {
    Scene world;

    auto tex = make_shared<Solid>(ColorRGB(1.0, 0.2, 0.2));
    auto tex1 = make_shared<Solid>(ColorRGB(0.2, 1.0, 0.2));
    auto tex2 = make_shared<Solid>(ColorRGB(0.2, 0.2, 1.0));
    auto tex3 = make_shared<Solid>(ColorRGB(1.0, 0.5, 0.0));
    auto tex4 = make_shared<Solid>(ColorRGB(0.2, 0.8, 0.8));
    auto tex5 = make_shared<Solid>(ColorRGB(0.9, 0.9, 0.9));

    auto left_red = make_shared<Lambertian>();
    auto back_green = make_shared<Lambertian>();
    auto right_blue = make_shared<Lambertian>();
    auto upper_orange = make_shared<Lambertian>();
    auto lower_teal = make_shared<Lambertian>();
    auto material_right = make_shared<Metal>(ColorRGB(0.9, 0.9, 0.9), 0.0);

    // Quads

    world.add(make_shared<Quad>(Point3(-3, -2, 5), Vector3(0, 0, -4), Vector3(0, 4, 0), left_red, tex));
    world.add(make_shared<Quad>(Point3(-2, -2, 0), Vector3(4, 0, 0), Vector3(0, 4, 0), back_green, tex1));
    world.add(make_shared<Quad>(Point3(3, -2, 1), Vector3(0, 0, 4), Vector3(0, 4, 0), right_blue, tex2));
    world.add(make_shared<Quad>(Point3(-2, 3, 1), Vector3(4, 0, 0), Vector3(0, 0, 4), upper_orange, tex2));
    world.add(make_shared<Quad>(Point3(-2, -3, 5), Vector3(4, 0, 0), Vector3(0, 0, -4), lower_teal, tex4));
    // world.add(make_shared<Sphere>(Point3(0, 0, 0), 1, make_shared<Lambertian>(ColorRGB(0.3, 0.5, 0.6))));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;

    cam.vfov = 80;
    cam.lookat = Point3(0, 0, 0);
    cam.lookfrom = Point3(0, 0, 9);
    cam.vup = Vector3(0, 1, 0);
    cam.Background = ColorRGB(0.2, 0.3, 0.7);

    cam.defocus_angle = 0;

    cam.Initialize();
    cam.Render(Scene(make_shared<bvh>(world)), "Rectangle.ppm");
    return 0;
}

int Triangle1() {
    Scene world;

    auto tex = make_shared<Solid>(ColorRGB(1.0, 0.2, 0.2));

    auto left_red = make_shared<Lambertian>(ColorRGB(1.0, 0.2, 0.2));
    auto back_green = make_shared<Lambertian>(ColorRGB(0.2, 1.0, 0.2));
    auto right_blue = make_shared<Lambertian>(ColorRGB(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<Lambertian>(ColorRGB(1.0, 0.5, 0.0));
    auto lower_teal = make_shared<Lambertian>(ColorRGB(0.2, 0.8, 0.8));
    auto material_right = make_shared<Metal>(ColorRGB(0.9, 0.9, 0.9), 0.0);

    // Quads

    world.add(make_shared<Quad>(Point3(-3, -2, 5), Vector3(0, 0, -10), Vector3(0, 4, 0), material_right));
    world.add(make_shared<Sphere>(Point3(0, 0, 0), 1, make_shared<Lambertian>(ColorRGB(0.3, 0.5, 0.6))));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;

    cam.vfov = 80;
    cam.lookat = Point3(0, 0, 0);
    cam.lookfrom = Point3(0, 0, 9);
    cam.vup = Vector3(0, 1, 0);

    cam.defocus_angle = 0;

    cam.Initialize();
    cam.Render(Scene(make_shared<bvh>(world)), "Rectangle2.ppm");
    return 0;
}

void simple_light() {
    Scene world;

    auto pertext = make_shared<Solid>(ColorRGB(0.5, 0.4, 0.3));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(), pertext));
    // world.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(), pertext));

    auto difflight = make_shared<LightDiffuse>();
    world.add(make_shared<Quad>(Point3(3, 1, -2), Vector3(2, 0, 0), Vector3(0, 2, 0), difflight,
                                make_shared<Solid>(ColorRGB(4, 4, 4))));
    world.add(make_shared<Sphere>(Point3(0, 7, 0), 2, difflight, make_shared<Solid>(ColorRGB(4, 4, 4))));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;

    cam.Background = ColorRGB(0.2, 0.3, 0.7);

    cam.vfov = 20;
    cam.lookfrom = Point3(26, 3, 6);
    cam.lookat = Point3(0, 2, 0);
    cam.vup = Vector3(0, 1, 0);

    cam.defocus_angle = -10;
    cam.Initialize();
    cam.Render(world, "light.ppm");
}

void simple_light2() {
    Scene world;

    auto pertext = make_shared<Solid>(ColorRGB(0.2, 0.3, 0.1));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(ColorRGB()), pertext));
    // world.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(), pertext));

    auto difflight = make_shared<LightDiffuse>();
    // world.add(make_shared<Quad>(Point3(3, 1, -2), Vector3(2, 0, 0), Vector3(0, 2, 0), difflight,
    // make_shared<Solid>(ColorRGB(4, 4, 4))));
    world.add(make_shared<Sphere>(Point3(0, 10, 0), 5, difflight, make_shared<Solid>(ColorRGB(4, 4, 4))));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;

    cam.Background = ColorRGB(0.2, 0.3, 0.7);

    cam.vfov = 90;
    cam.lookfrom = Point3(0, 2, 10);
    cam.lookat = Point3(0, 2, 0);
    cam.vup = Vector3(0, 1, 0);

    cam.defocus_angle = -10;
    cam.Initialize();
    cam.Render(world, "light.ppm");
}

int main() {
    Triangle0();
    return 0;
}