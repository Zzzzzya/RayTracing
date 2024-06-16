#pragma once
#ifndef COLOR_HPP
#define COLOR_HPP

#include "Vector.hpp"
#include <cmath>
#include <iostream>

using ColorRGB = Vector3;

// 绘制颜色
void write_color_rgb(std::ostream &out, const ColorRGB &color);
void write_color_rgb_f(std::fstream &out, const ColorRGB &color);

// 伽马矫正
inline double ColorLinear2Gama(double linearColor);
#endif