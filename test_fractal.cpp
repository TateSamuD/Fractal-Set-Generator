#include <fractal.h>
#include <iostream>
#include <cassert>

// Test for mandelbrot function
void testMandelbrot()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = mandelbrot(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for julia_z2 function
void testJuliaZ2()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = julia_z2(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for julia_z2_offset function
void testJuliaZ2Offset()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;
    double offset_x = 0.1;

    int expectedOutput = 100;

    int actualOutput = julia_z2_offset(x, y, max_iter, offset_x);

    assert(actualOutput == expectedOutput);
}

// Test for julia_z4 function
void testJuliaZ4()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = julia_z4(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for julia_z4_offset function
void testJuliaZ4Offset()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;
    double offset_x = 0.1;

    int expectedOutput = 100;

    int actualOutput = julia_z4_offset(x, y, max_iter, offset_x);

    assert(actualOutput == expectedOutput);
}

// Test for julia_z8 function
void testJuliaZ8()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = julia_z8(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for lorenz function
void testLorenz()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = lorenz(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for aizawa function
void testAizawa()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = aizawa(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for noise function
void testNoise()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = noise(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for gaussian function
void testGaussian()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = gaussian(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for turbulence function
void testTurbulence()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = turbulence(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for fractal_noise function
void testFractalNoise()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = fractal_noise(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for fractal_gaussian function
void testFractalGaussian()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = fractal_gaussian(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

// Test for fractal_flame function
void testFractalFlame()
{
    double x = 0.5;
    double y = 0.5;
    int max_iter = 100;

    int expectedOutput = 100;

    int actualOutput = fractal_flame(x, y, max_iter);

    assert(actualOutput == expectedOutput);
}

int main()
{
    testMandelbrot();
    testJuliaZ2();
    testJuliaZ2Offset();
    testJuliaZ4();
    testJuliaZ4Offset();
    testJuliaZ8();
    testLorenz();
    testAizawa();
    testNoise();
    testGaussian();
    testTurbulence();
    testFractalNoise();
    testFractalGaussian();
    testFractalFlame();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}