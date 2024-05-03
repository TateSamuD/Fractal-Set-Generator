#ifndef FRACTAL_H
#define FRACTAL_H

#include "base.h"

int mandelbrot(double x, double y, int max_iter);
int julia_z2(double x, double y, int max_iter);
int julia_z2_offset(double x, double y, int max_iter, double offset_x);
int julia_z4(double x, double y, int max_iter);
int julia_z4_offset(double x, double y, int max_iter, double offset_x);
int julia_z8(double x, double y, int max_iter);
int lorenz(double x, double y, int max_iter);
int aizawa(double x, double y, int max_iter);

int noise(double x, double y, int max_iter);
int gaussian(double x, double y, int max_iter);
int turbulence(double x, double y, int max_iter);
int turbulence_frame(double x, double y, int max_iter, int frame_numbe);

int fractal_noise(double x, double y, int max_iter);
int fractal_gaussian(double x, double y, int max_iter);
int fractal_flame(double x, double y, int max_iter);

#endif // !FRACTAL_H