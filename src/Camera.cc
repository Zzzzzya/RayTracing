#include "Camera.hpp"
#include <fstream>
#include <iostream>
void Camera::Initialize() {
    imageHeight = (double)imageWidth / aspectRatio;
    imageHeight = imageHeight > 1 ? imageHeight : 1;

    Loc = lookfrom;
    lookto = lookfrom - lookat;

    lookto.normalize();

    auto h = d2r(vfov);
    auto tan_h = std::tan(h / 2);
    ViewportHeight = focusLen * tan_h * 2;
    ViewportWidth = ViewportHeight / (double)imageHeight * (double)imageWidth;

    Vector3 u = cross(vup, lookto.normalized()).normalized();
    Vector3 v = cross(lookto.normalized(), u).normalized();

    pixelDu = u * ViewportWidth / (double)imageWidth;
    pixelDv = -v * ViewportHeight / (double)imageHeight;

    ViewTopLeft = Loc - focusLen * lookto - u * ViewportWidth / 2 + v * ViewportHeight / 2;
    pixelLoc00 = ViewTopLeft + 0.5 * pixelDu + 0.5 * pixelDv;

    auto defocusRadius = focusLen * std::tan(d2r(defocus_angle) / 2);
    defocusDiskU = u * defocusRadius;
    defocusDiskV = v * defocusRadius;
}

void Camera::Render(const hittable &object, std::string outPath) {
    samplesDu = pixelDu / MSAA_samplesX_PerPixel;
    samplesDv = pixelDv / MSAA_samplesY_PerPixel;
    outPath = "../image/" + outPath;
    std::fstream out;
    out.open(outPath, std::ios::out);
    out << "P3\n" << imageWidth << " " << imageHeight << "\n256\n";
    std::clog << "Rendering to :\"" << outPath << "\"\n";

    for (int i = 0; i < imageHeight; i++) {
        std::clog << "\rRemain columns:" << imageHeight - i << "      " << std::flush;
        for (int j = 0; j < imageWidth; j++) {
            ColorRGB pixelCol;
            for (int x = 0; x < MSAA_samplesX_PerPixel; x++) {
                for (int y = 0; y < MSAA_samplesY_PerPixel; y++) {
                    pixelCol += ray_Color(MSAARay(i, j, x, y), object, 0);
                }
            }
            write_color_rgb_f(out, pixelCol / (MSAA_samplesX_PerPixel * MSAA_samplesY_PerPixel));
        }
    }
    std::clog << "\rDone                                \r\n";
}

void Camera::Render_withRandomAA(const hittable &object, std::string outPath) {
    std::fstream out;
    outPath = "../image/" + outPath;
    out.open(outPath, std::ios::out);
    out << "P3\n" << imageWidth << " " << imageHeight << "\n256\n";
    std::clog << "Rendering to :\"" << outPath << "\"\n";

    for (int i = 0; i < imageHeight; i++) {
        std::clog << "\rRemain columns:" << imageHeight - i << std::flush;
        for (int j = 0; j < imageWidth; j++) {
            ColorRGB pixelCol;
            for (int ps = 0; ps < samplesPerPixel; ps++) {
                pixelCol += ray_Color(RandomAARay(i, j), object, 0);
            }
            write_color_rgb_f(out, pixelCol / samplesPerPixel);
        }
    }
    std::clog << "\rDone                                \r\n";
}

void Camera::Render_withoutAA(const hittable &object, std::string outPath) {
    std::fstream out;
    out.open(outPath, std::ios::out);
    out << "P3\n" << imageWidth << " " << imageHeight << "\n256\n";
    std::clog << "Rendering to :\"" << outPath << "\"\n";

    for (int i = 0; i < imageHeight; i++) {
        std::clog << "\rRemain columns:" << imageHeight - i << std::flush;
        for (int j = 0; j < imageWidth; j++) {
            Point3 pixelLoc = pixelLoc00 + i * pixelDv + j * pixelDu;
            Ray ray(Loc, pixelLoc - Loc);
            write_color_rgb_f(out, ray_Color(ray, object, 0));
        }
    }
    std::clog << "\rDone                                \r\n";
}

ColorRGB Camera::ray_Color(const Ray &ray, const hittable &object, int Depth) {
    if (Depth >= diffuseMaxDepth)
        return ColorRGB(0, 0, 0);
    InterPoint curInter;
    if (!object.hit(ray, Interval(0.001, infinity), curInter))
        return Background;

    // 若击中
    ColorRGB Emitting = curInter.met->Emit(curInter);
    ColorRGB col;
    Ray scattered;

    if (!curInter.met->Scatter(ray, curInter, col, scattered)) {
        return Emitting;
    }

    // 没有反射说明打到光源了！

    return Emitting + productElement(col, ray_Color(scattered, object, Depth + 1));
}

ColorRGB Camera::ray_Color_diffuse(const Ray &ray, const hittable &object, int Depth) {
    if (Depth >= diffuseMaxDepth)
        return ColorRGB(0, 0, 0);
    InterPoint curInter;
    if (object.hit(ray, Interval(0.001, infinity), curInter)) {
        // 漫反射随机发射反射光
        Vector3 diffuse = Vector3::rand() + curInter.nor;
        return kd * ray_Color_diffuse(Ray(curInter.loc, diffuse), object, Depth + 1);
    }

    auto a = ray.dir().y();
    a = 0.5 * (a + 1);
    return ColorRGB((1 - a) * ColorRGB(1.0, 1.0, 1.0) + a * ColorRGB(0.5, 0.7, 1.0));
}

// 返回一个随机偏移量
Vector3 Camera::randomOffset() {
    return Vector3(random_double(-1.0, 1.0), random_double(-1.0, 1.0), 0);
}

Ray Camera::RandomAARay(int i, int j) {
    auto offset = randomOffset();
    offset.xx *= pixelDu.xx / 2;
    offset.yy *= pixelDv.yy / 2;
    Point3 pixelLoc = pixelLoc00 + i * pixelDv + j * pixelDu;
    auto start = defocus_angle <= 0 ? Loc : defocusDiskSample();
    return Ray(start, pixelLoc + offset - start, random_double());
}

Ray Camera::MSAARay(int i, int j, int x, int y) {
    Point3 sampleLoc = ViewTopLeft + i * pixelDv + j * pixelDu + x * samplesDu + y * samplesDv;
    auto start = defocus_angle <= 0 ? Loc : defocusDiskSample();
    return Ray(start, sampleLoc - start, random_double());
}

Point3 Camera::defocusDiskSample() const {
    auto p = Vector3::randomXYunit();
    return Loc + p.xx * defocusDiskU + p.yy * defocusDiskV;
}
