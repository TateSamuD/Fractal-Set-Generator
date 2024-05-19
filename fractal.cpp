#include "fractal.h"

int mandelbrot(double x, double y, int max_iter)
{
   double a = 0.0;
   double b = 0.0;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = a * a - b * b + x;
      double b_new = 2 * a * b + y;
      a = a_new;
      b = b_new;
      i++;
   }
   return i;
}

// Julia Sets
// Julia Set z^2
int julia_z2(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = a * a - b * b;
      double b_new = 2 * a * b;
      a = a_new - 0.54;
      b = b_new + 0.54;
      i++;
   }
   return i;
}

// Julia Set z^2 with offset
int julia_z2_offset(double x, double y, int max_iter, double offset_x)
{
   double a = x;
   double b = y;
   int i = 0;
   double c_1 = -1.5 + offset_x;
   double c_2 = -0.5 + offset_x;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = a * a - b * b;
      double b_new = 2 * a * b;
      a = a_new + c_1;
      b = b_new + c_2;
      i++;
   }
   return i;
}

// Julia Set z^4
int julia_z4(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   double c_1 = 0.64;
   while (i < max_iter && a * a + b * b < 100.0)
   {
      double a_new = a * a * a * a - 6 * a * a * b * b + b * b * b * b;
      double b_new = 4 * a * a * a * b - 4 * a * b * b * b;
      a = a_new - c_1;
      b = b_new + 0.45;
      i++;
   }
   return i;
}

// Julia Set z^4 with offset
int julia_z4_offset(double x, double y, int max_iter, double offset_x)
{
   double a = x;
   double b = y;
   int i = 0;
   double offset = -0.75 + offset_x;
   while (i < max_iter && a * a * a * a + b * b * b * b < 4.0)
   {
      double a2 = a * a;
      double b2 = b * b;
      double a_new = a2 * a2 - 6 * a2 * b2 + b2 * b2;
      double b_new = 4 * a2 * a * b - 4 * a * b2 * b;
      a = a_new + offset;
      b = b_new + 0.45;
      i++;
   }
   return i;
}

// Julia Set z^8
// FIXME:
int julia_z8(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 100.0)
   {
      double a_new = a * a * a * a * a * a * a * a -
                     28 * a * a * a * a * a * a * b * b +
                     70 * a * a * a * b * b * b * b -
                     28 * a * b * b * b * b * b * b + b * b * b * b * b * b * b * b;
      double b_new = 8 * a * a * a * a * a * a * a * b -
                     8 * a * a * a * a * b * b * b * b -
                     8 * a * a * b * b * b * b * b * b +
                     8 * a * b * b * b * b * b * b * b;
      a = a_new - 0.8;
      b = b_new + 0.5;
      i++;
   }
   return i;
}

// FIXME:
int lorenz(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   double c = 2.667;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = 10 * (b - a);
      double b_new = a * (28 - 10) - b - a * c;
      a = a_new;
      b = b_new;
      i++;
   }
   return i;
}

// FIXME:
int aizawa(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = (b - 0.1) * a - 0.6 * b;
      double b_new = 0.6 * a + (b - 0.1) * b;
      a = a_new;
      b = b_new;
      i++;
   }
   return i;
}

// FIXME:
int noise(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = a + 0.1 * (rand() % 100 - 50);
      double b_new = b + 0.1 * (rand() % 100 - 50);
      a = a_new;
      b = b_new;
      i++;
   }
   return i;
}

// FIXME:
int gaussian(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = a + 0.1 * (rand() % 100 - 50);
      double b_new = b + 0.1 * (rand() % 100 - 50);
      a = a_new;
      b = b_new;
      i++;
   }
   return i;
}

// TODO: tighten up turbulence
int turbulence(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = a + 0.1 * sin(b);
      double b_new = b + 0.1 * cos(a);
      a = a_new;
      b = b_new;
      i++;
   }
   return i;
}

int turbulence_frame(double x, double y, int max_iter, int frame_number)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = a + 0.1 * sin(b) + 0.1 * sin(frame_number * 0.1);
      double b_new = b + 0.1 * cos(a) + 0.1 * cos(frame_number * 0.1);
      a = a_new;
      b = b_new;
      i++;
   }
   return i;
}

int fractal_noise(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      i += noise(a, b, max_iter);
      a += 0.1;
      b += 0.1;
   }
   return i;
}

int fractal_gaussian(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      i += gaussian(a, b, max_iter);
      a += 0.1;
      b += 0.1;
   }
   return i;
}

int fractal_flame(double x, double y, int max_iter)
{
   double a = x;
   double b = y;
   int i = 0;
   while (i < max_iter && a * a + b * b < 4.0)
   {
      double a_new = a * a - b * b;
      double b_new = 2 * a * b;
      a = a_new - 0.54; // Adjust this constant as needed
      b = b_new + 0.54; // Adjust this constant as needed
      i++;
   }
   return i;
}
