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

// int Scene1() {
//     Camera camera;
//     Scene world;

//     auto texture0 = make_shared<ImageTex>("src/image.png");

//     auto material_ground = make_shared<Lambertian>(ColorRGB(0.8, 0.8, 0.0));
//     auto material_center = make_shared<Lambertian>(ColorRGB(0.1, 0.2, 0.5));
//     auto material_left = make_shared<Metal>(ColorRGB(0.8, 0.8, 0.8), 0.0);
//     auto material_right = make_shared<Metal>(ColorRGB(0.8, 0.6, 0.2), 1.0);

//     world.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground, texture0));
//     world.add(make_shared<Sphere>(Point3(0.0, 2, -1.2), 0.5, material_center));
//     world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
//     world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

//     world = Scene(make_shared<bvh>(world));

//     // Camera cam;
//     Camera cam;
//     cam.aspectRatio = 16.0 / 9.0;
//     cam.imageWidth = 400;

//     cam.vfov = 90;
//     cam.lookfrom = Point3(0, 0, 0);
//     cam.lookat = Point3(0, 0, -1);

//     cam.defocus_angle = -0.6;
//     cam.focusLen = 1.0;

//     cam.Initialize();

//     cam.Render(world, "../image/output.ppm");

//     return 0;
// }

// int CheckerSphere() {
//     Scene world;

//     auto texture0 = make_shared<Noise>(5);

//     auto material_center = make_shared<Lambertian>();

//     world.add(make_shared<Sphere>(Point3(0.0, -1000, 0.0), 1000, material_center, texture0));
//     world.add(make_shared<Sphere>(Point3(0.0, 2, 0.0), 2, material_center, texture0));
//     Camera cam;

//     cam.aspectRatio = 16.0 / 9.0;
//     cam.imageWidth = 400;

//     cam.vfov = 20;
//     cam.lookat = Point3(0, 0, 0);
//     cam.lookfrom = Point3(13, 2, 3);
//     cam.vup = Vector3(0, 1, 0);

//     cam.defocus_angle = 0;

//     cam.Initialize();
//     cam.Render(world, "TurbPerLin.ppm");
//     return 0;
// }

// int Triangle0() {
//     Scene world;

//     auto tex = make_shared<Solid>(ColorRGB(1.0, 0.2, 0.2));
//     auto tex1 = make_shared<Solid>(ColorRGB(0.2, 1.0, 0.2));
//     auto tex2 = make_shared<Solid>(ColorRGB(0.2, 0.2, 1.0));
//     auto tex3 = make_shared<Solid>(ColorRGB(1.0, 0.5, 0.0));
//     auto tex4 = make_shared<Solid>(ColorRGB(0.2, 0.8, 0.8));
//     auto tex5 = make_shared<Solid>(ColorRGB(0.9, 0.9, 0.9));

//     auto left_red = make_shared<Lambertian>();
//     auto back_green = make_shared<Lambertian>();
//     auto right_blue = make_shared<Lambertian>();
//     auto upper_orange = make_shared<Lambertian>();
//     auto lower_teal = make_shared<Lambertian>();

//     auto material1 = make_shared<Metal>(ColorRGB(0.9, 0.9, 0.9), 1.0);
//     auto material2 = make_shared<Metal>(ColorRGB(0.9, 0.9, 0.9), 1.0);
//     auto material3 = make_shared<Metal>(ColorRGB(0.9, 0.9, 0.9), 1.0);
//     auto material4 = make_shared<Metal>(ColorRGB(0.9, 0.9, 0.9), 1.0);
//     auto material5 = make_shared<Metal>(ColorRGB(0.9, 0.9, 0.9), 1.0);

//     // Quads

//     world.add(make_shared<Quad>(Point3(-3, -2, 5), Vector3(0, 0, -4), Vector3(0, 4, 0), left_red, tex));
//     world.add(make_shared<Quad>(Point3(-2, -2, 0), Vector3(4, 0, 0), Vector3(0, 4, 0), back_green, tex1));
//     world.add(make_shared<Quad>(Point3(3, -2, 1), Vector3(0, 0, 4), Vector3(0, 4, 0), right_blue, tex2));
//     world.add(make_shared<Quad>(Point3(-2, 3, 1), Vector3(4, 0, 0), Vector3(0, 0, 4), upper_orange, tex3));
//     world.add(make_shared<Quad>(Point3(-2, -3, 5), Vector3(4, 0, 0), Vector3(0, 0, -4), lower_teal, tex4));
//     // world.add(make_shared<Sphere>(Point3(0, 0, 0), 1, make_shared<Lambertian>(ColorRGB(0.3, 0.5, 0.6))));

//     // world.add(make_shared<Quad>(Point3(-3, -2, 5), Vector3(0, 0, -4), Vector3(0, 4, 0), material1, tex));
//     // world.add(make_shared<Quad>(Point3(-2, -2, 0), Vector3(4, 0, 0), Vector3(0, 4, 0), material2, tex1));
//     // world.add(make_shared<Quad>(Point3(3, -2, 1), Vector3(0, 0, 4), Vector3(0, 4, 0), material3, tex2));
//     // world.add(make_shared<Quad>(Point3(-2, 3, 1), Vector3(4, 0, 0), Vector3(0, 0, 4), material4, tex3));
//     // world.add(make_shared<Quad>(Point3(-2, -3, 5), Vector3(4, 0, 0), Vector3(0, 0, -4), material5, tex4));

//     // world.add(make_shared<Triangle>(Point3(-3, -2, 5), Point3(-3, -2, 5) + Vector3(0, 0, -4),
//     //                                 Point3(-3, -2, 5) + Vector3(0, 4, 0), left_red, tex));
//     // world.add(make_shared<Triangle>(Point3(-2, -2, 0), Point3(-2, -2, 0) + Vector3(4, 0, 0),
//     //                                 Point3(-2, -2, 0) + Vector3(0, 4, 0), back_green, tex1));
//     // world.add(make_shared<Triangle>(Point3(3, -2, 1), Point3(3, -2, 1) + Vector3(0, 0, 4),
//     //                                 Point3(3, -2, 1) + Vector3(0, 4, 0), right_blue, tex2));
//     // world.add(make_shared<Triangle>(Point3(-2, 3, 1), Point3(-2, 3, 1) + Vector3(4, 0, 0),
//     //                                 Point3(-2, 3, 1) + Vector3(0, 0, 4), upper_orange, tex3));
//     // world.add(make_shared<Triangle>(Point3(-2, -3, 5), Point3(-2, -3, 5) + Vector3(4, 0, 0),
//     //                                 Point3(-2, -3, 5) + Vector3(0, 0, -4), lower_teal, tex4));

//     Camera cam;

//     cam.aspectRatio = 16.0 / 9.0;
//     cam.imageWidth = 400;

//     cam.vfov = 80;
//     cam.lookat = Point3(0, 0, 0);
//     cam.lookfrom = Point3(0, 0, 9);
//     cam.vup = Vector3(0, 1, 0);
//     cam.Background = ColorRGB(0.2, 0.3, 0.7);

//     cam.defocus_angle = 0;

//     cam.Initialize();
//     cam.Render(Scene(make_shared<bvh>(world)), "Rectangle.ppm");
//     return 0;
// }

// int Triangle1() {
//     Scene world;

//     auto tex = make_shared<Solid>(ColorRGB(1.0, 0.2, 0.2));

//     auto left_red = make_shared<Lambertian>(ColorRGB(1.0, 0.2, 0.2));
//     auto back_green = make_shared<Lambertian>(ColorRGB(0.2, 1.0, 0.2));
//     auto right_blue = make_shared<Lambertian>(ColorRGB(0.2, 0.2, 1.0));
//     auto upper_orange = make_shared<Lambertian>(ColorRGB(1.0, 0.5, 0.0));
//     auto lower_teal = make_shared<Lambertian>(ColorRGB(0.2, 0.8, 0.8));
//     auto material_right = make_shared<Metal>(ColorRGB(0.9, 0.9, 0.9), 0.0);

//     // Quads

//     world.add(make_shared<Quad>(Point3(-3, -2, 5), Vector3(0, 0, -10), Vector3(0, 4, 0), material_right));
//     world.add(make_shared<Sphere>(Point3(0, 0, 0), 1, make_shared<Lambertian>(ColorRGB(0.3, 0.5, 0.6))));

//     Camera cam;

//     cam.aspectRatio = 16.0 / 9.0;
//     cam.imageWidth = 400;

//     cam.vfov = 80;
//     cam.lookat = Point3(0, 0, 0);
//     cam.lookfrom = Point3(0, 0, 9);
//     cam.vup = Vector3(0, 1, 0);

//     cam.defocus_angle = 0;

//     cam.Initialize();
//     cam.Render(Scene(make_shared<bvh>(world)), "Rectangle2.ppm");
//     return 0;
// }

// void simple_light() {
//     Scene world;

//     auto pertext = make_shared<Noise>(4);
//     world.add(
//         make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(ColorRGB(0.0, 0.0, 0.0)), pertext));

//     auto white = make_shared<Lambertian>(ColorRGB(.73, .73, .73));
//     auto a = Point3(0, 0, 0);
//     auto b = Point3(2, 2, 2);
//     world.add(box(roty(30, a), roty(30, b), white));

//     auto difflight = make_shared<LightDiffuse>();
//     world.add(make_shared<Quad>(Point3(3, 1, -2), Vector3(2, 0, 0), Vector3(0, 2, 0), difflight,
//                                 make_shared<Solid>(ColorRGB(4, 4, 4))));

//     world.add(make_shared<Sphere>(Point3(0, 7, 0), 2, difflight, make_shared<Solid>(ColorRGB(4, 4, 4))));

//     Camera cam;

//     cam.aspectRatio = 16.0 / 9.0;
//     cam.imageWidth = 400;

//     // cam.Background = ColorRGB(0.2, 0.3, 0.7);

//     cam.vfov = 20;
//     cam.lookfrom = Point3(26, 3, 0);
//     cam.lookat = Point3(0, 2, 0);
//     cam.vup = Vector3(0, 1, 0);

//     cam.defocus_angle = -10;
//     cam.Initialize();
//     cam.Render(world, "light2.ppm");
// }

// void simple_light2() {
//     Scene world;

//     auto pertext = make_shared<Solid>(ColorRGB(0.2, 0.3, 0.1));
//     world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(ColorRGB()), pertext));
//     // world.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(), pertext));

//     auto difflight = make_shared<LightDiffuse>();
//     // world.add(make_shared<Quad>(Point3(3, 1, -2), Vector3(2, 0, 0), Vector3(0, 2, 0), difflight,
//     // make_shared<Solid>(ColorRGB(4, 4, 4))));
//     world.add(make_shared<Sphere>(Point3(0, 10, 0), 5, difflight, make_shared<Solid>(ColorRGB(4, 4, 4))));

//     Camera cam;

//     cam.aspectRatio = 16.0 / 9.0;
//     cam.imageWidth = 400;

//     cam.Background = ColorRGB(0.2, 0.3, 0.7);

//     cam.vfov = 90;
//     cam.lookfrom = Point3(0, 2, 10);
//     cam.lookat = Point3(0, 2, 0);
//     cam.vup = Vector3(0, 1, 0);

//     cam.defocus_angle = -10;
//     cam.Initialize();
//     cam.Render(world, "light.ppm");
// }

// void cornell_box() {
//     Scene world;

//     auto red = make_shared<Lambertian>(ColorRGB(.65, .05, .05));
//     auto white = make_shared<Lambertian>(ColorRGB(.73, .73, .73));
//     auto green = make_shared<Lambertian>(ColorRGB(.12, .45, .15));

//     auto tex = make_shared<Solid>(ColorRGB(15, 15, 15));
//     auto light = make_shared<LightDiffuse>();

//     world.add(make_shared<Quad>(Point3(555, 0, 0), Vector3(0, 555, 0), Vector3(0, 0, 555), green));
//     world.add(make_shared<Quad>(Point3(0, 0, 0), Vector3(0, 555, 0), Vector3(0, 0, 555), red));
//     world.add(make_shared<Quad>(Point3(343, 554, 332), Vector3(-130, 0, 0), Vector3(0, 0, -105), light, tex));
//     world.add(make_shared<Quad>(Point3(0, 0, 0), Vector3(555, 0, 0), Vector3(0, 0, 555), white));
//     world.add(make_shared<Quad>(Point3(555, 555, 555), Vector3(-555, 0, 0), Vector3(0, 0, -555), white));
//     world.add(make_shared<Quad>(Point3(0, 0, 555), Vector3(555, 0, 0), Vector3(0, 555, 0), white));

//     shared_ptr<hittable> box1 = box(Point3(0, 0, 0), Point3(165, 330, 165), white);
//     box1 = make_shared<rotate_y>(box1, 15);
//     box1 = make_shared<translate>(box1, Vector3(265, 0, 295));
//     world.add(box1);

//     shared_ptr<hittable> box2 = box(Point3(0, 0, 0), Point3(165, 165, 165), white);
//     box2 = make_shared<rotate_y>(box2, -18);
//     box2 = make_shared<translate>(box2, Vector3(130, 0, 65));
//     world.add(box2);

//     Camera cam;

//     cam.aspectRatio = 1.0;
//     cam.imageWidth = 600;

//     cam.Background = ColorRGB(0, 0, 0);

//     cam.vfov = 40;
//     cam.lookfrom = Point3(278, 278, -800);
//     cam.lookat = Point3(278, 278, 0);
//     cam.vup = Vector3(0, 1, 0);

//     cam.defocus_angle = 0;
//     cam.Initialize();
//     cam.Render(Scene(make_shared<bvh>(world)), "cornell_box.ppm");
// }

void final_scene() {
    Scene boxes1;
    auto ground = make_shared<Lambertian>(ColorRGB(0.48, 0.83, 0.53));

    int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1, 101);
            auto z1 = z0 + w;

            boxes1.add(box(Point3(x0, y0, z0), Point3(x1, y1, z1), ground));
        }
    }

    Scene world;

    world.add(make_shared<bvh>(boxes1));
    auto tex1 = make_shared<Solid>(ColorRGB(7, 7, 7));

    auto light = make_shared<LightDiffuse>();
    world.add(make_shared<Quad>(Point3(123, 554, 147), Vector3(300, 0, 0), Vector3(0, 0, 265), light, tex1));

    auto center1 = Point3(400, 400, 200);
    auto center2 = center1 + Vector3(30, 0, 0);
    auto Sphere_material = make_shared<Lambertian>(ColorRGB(0.7, 0.3, 0.1));
    auto tex2 = make_shared<Solid>(ColorRGB(0.7, 0.3, 0.1));
    world.add(make_shared<SphereMovingStraight>(center1, center2, 50, Sphere_material, tex2));

    world.add(make_shared<Sphere>(Point3(260, 150, 45), 50, make_shared<Dielectric>(1.5)));
    auto tex3 = make_shared<Solid>(ColorRGB(0.8, 0.8, 0.9));
    world.add(make_shared<Sphere>(Point3(0, 150, 145), 50, make_shared<Metal>(ColorRGB(0.8, 0.8, 0.9), 1.0), tex3));

    auto boundary = make_shared<Sphere>(Point3(360, 150, 145), 70, make_shared<Dielectric>(1.5));
    world.add(boundary);

    boundary = make_shared<Sphere>(Point3(0, 0, 0), 5000, make_shared<Dielectric>(1.5));
    world.add(boundary);

    auto tex4 = make_shared<ImageTex>("image.jpg");
    auto emat = make_shared<Lambertian>();
    world.add(make_shared<Sphere>(Point3(400, 200, 400), 100, emat, tex4));
    auto pertext = make_shared<Noise>(0.2);
    world.add(make_shared<Sphere>(Point3(220, 280, 300), 80, make_shared<Lambertian>(), pertext));

    Scene boxes2;
    auto white = make_shared<Lambertian>(ColorRGB(.73, .73, .73));
    auto tex5 = make_shared<Solid>(ColorRGB(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<Sphere>(Point3::rand(0, 165), 10, white, tex5));
    }

    // world.add(make_shared<translate>(make_shared<rotate_y>(make_shared<bvh>(boxes2), 15), Vector3(-100, 270, 395)));

    Camera cam;

    cam.aspectRatio = 1.0;
    cam.imageWidth = 400;

    cam.Background = ColorRGB(0, 0, 0);

    cam.vfov = 40;
    cam.lookfrom = Point3(478, 278, -600);
    cam.lookat = Point3(278, 278, 0);
    cam.vup = Vector3(0, 1, 0);

    cam.defocus_angle = 0;
    cam.Initialize();
    cam.Render(world, "Finallll.ppm");
}

int main() {
    final_scene();
    return 0;
}