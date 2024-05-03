#ifndef IMAGE_GEN_H
#define IMAGE_GEN_H

#include "fractal.h"

void generate_mandelbrot_image();
void generate_julia_z2_image();
void generate_julia_z2_offset_frames();
void generate_julia_z4_image();
void generate_julia_z4_offset_frames();
void generate_julia_z8_image();
void generate_sierpinski_image();

void generate_lorenz_image();
void generate_aizawa_image();

void generate_noise_image();
void generate_gaussian_noise_image();
void generate_turbulence_image();
void generate_turbulence_frame();

void generate_flame_julia_image();

void generate_fractal_noise_image();
void generate_fractal_gaussian_image();
void generate_fractal_flame_image();

#endif // !IMAGE_GEN_H
