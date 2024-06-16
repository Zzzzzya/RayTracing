#pragma once
#include "Head.hpp"
#include "Material.hpp"
#include "Scene.hpp"

class Camera {
  public:
    Point3 Loc;                      // 摄像机位置
    int imageWidth = 400;            // 最终渲染的图片大小
    double ViewportHeight;           // 投影面的大小 一般默认高度为-1 ~ 1 之后由focusLen && vfov决定
    double aspectRatio = 16.0 / 9.0; // 宽高比 宽：高
    double focusLen = 10.0;          // 聚焦距离
    double vfov = 90;                // 视野宽度 高和focusLen的比值

    double defocus_angle = 0;

    Point3 lookfrom;
    Point3 lookat;
    Vector3 vup = Vector3(0, 1, 0);

    double samplesPerPixel = 4; // 随机采样AA的个数
    double MSAA_samplesX_PerPixel = 4;
    double MSAA_samplesY_PerPixel = 4;
    int diffuseMaxDepth = 50;
    double kd = 0.7;

    ColorRGB Background = ColorRGB(0, 0, 0);

    Camera() = default;
    void Initialize();
    void Render(const hittable &object, std::string outPath = "output.ppm");
    void Render_withRandomAA(const hittable &object, std::string outPath = "output_RandomAA.ppm");
    void Render_withoutAA(const hittable &object, std::string outPath = "output_NoAA.ppm");

  private:
    int imageHeight;
    double ViewportWidth;
    Vector3 lookto;
    Vector3 pixelDu;
    Vector3 pixelDv;
    Point3 ViewTopLeft;
    Point3 pixelLoc00;
    Vector3 defocusDiskU;
    Vector3 defocusDiskV;

    ColorRGB ray_Color(const Ray &ray, const hittable &object, int depth);
    ColorRGB ray_Color_diffuse(const Ray &ray, const hittable &object, int depth);

    // RANDOM AA
    Vector3 randomOffset();
    Ray RandomAARay(int i, int j);

    // MSAA
    Vector3 samplesDu;
    Vector3 samplesDv;
    Ray MSAARay(int i, int j, int x, int y);

    // Defocus
    Point3 defocusDiskSample() const;
};