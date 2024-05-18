#ifndef BASE_H
#define BASE_H

#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <sstream>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <vector>
#include <cassert>
// #include <opencv2/opencv.hpp>
// #include <png++/png.hpp>
// #include <png.h>

/* Image sizes*/
/* Generates 10.5mb images*/
#define WIDTH 1920
#define HEIGHT 1920
#define F_SIZE 10.5

// /* Generates 1.48mb images*/
// #define WIDTH 720
// #define HEIGHT 720
// #define F_SIZE 1.48

// /* Generates 4.9mb images*/
// #define WIDTH 1280
// #define HEIGHT 1280
// #define F_SIZE 4.9

#define NUM_FRAMES 1480
// #define NUM_FRAMES 720
#define FPS 20

#define M_PI 3.14159265358979323846

#define SATURATION 1.0
#define VALUE 1.0

#define C_1 0.8
#define C_2 0.156

#define MAX_ITER 1000

extern int frame_number;

typedef struct RGB
{
	uint8_t r, g, b;
	float h, s, v;
	RGB(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
} RGB_t;

#endif // !BASE_H