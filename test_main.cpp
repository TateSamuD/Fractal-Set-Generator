#include <fractal.h>
#include <cassert>

// Function to redirect cin and capture user input
void redirectCin(const std::string& input) {
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf());
}

// Function to capture cout output
std::string captureCout() {
    std::stringstream ss;
    std::streambuf* oldCout = std::cout.rdbuf(ss.rdbuf());
    std::cout.rdbuf(oldCout);
    return ss.str();
}

// Test for julia_choice function
void testJuliaChoice() {
    std::string input = "1\n0\n";
    redirectCin(input);

    std::string expectedOutput = "\n\n\n-----------------------------\n"
                                 "***# Julia Set #***\n"
                                 "Please choose an Option\n"
                                 "-----------------------------\n"
                                 "[1] Julia Set z^2\n"
                                 "[2] Julia Set z^4\n"
                                 "[3] Julia Set z^8\n"
                                 "-----------------------------\n"
                                 "[4] Julia Set z^2 Frames\n"
                                 "[5] Julia Set z^4 Frames\n"
                                 "-----------------------------\n"
                                 "[6] Julia Set z^2 Video\n"
                                 "[7] Julia Set z^4 Video\n"
                                 "-----------------------------\n"
                                 "[0] Exit\n\n"
                                 "Enter your choice: "
                                 "Exiting\n";

    std::string actualOutput = captureCout();

    assert(actualOutput == expectedOutput);
}

// Test for noise_choice function
void testNoiseChoice() {
    std::string input = "2\n0\n";
    redirectCin(input);

    std::string expectedOutput = "\n\n\n-----------------------------\n"
                                 "***# Noise #***\n"
                                 "Please choose an Option\n"
                                 "-----------------------------\n"
                                 "[1] Noise\n"
                                 "[2] Noise Fractal\n"
                                 "-----------------------------\n"
                                 "[0] Exit\n\n"
                                 "Enter your choice: "
                                 "Exiting\n";

    std::string actualOutput = captureCout();

    assert(actualOutput == expectedOutput);
}

// Test for gaussian_choice function
void testGaussianChoice() {
    std::string input = "1\n0\n";
    redirectCin(input);

    std::string expectedOutput = "\n\n\n-----------------------------\n"
                                 "***# Gaussian #***\n"
                                 "Please choose an Option\n"
                                 "-----------------------------\n"
                                 "[1] Gaussian\n"
                                 "[2] Gaussian Fractal\n"
                                 "-----------------------------\n"
                                 "[0] Exit\n\n"
                                 "Enter your choice: "
                                 "Exiting\n";

    std::string actualOutput = captureCout();

    assert(actualOutput == expectedOutput);
}

// Test for main function
void testMain() {
    std::string input = "2\n1\n0\n";
    redirectCin(input);

    std::string expectedOutput = "\n-----------------------------\n"
                                 "***# Image Processing #***\n"
                                 "Please choose an Option\n"
                                 "-----------------------------\n"
                                 "[1] Mandelbrot Set Image\n"
                                 "[2] Julia Set [Options]\n"
                                 "[8] Turbulence (adjust c value)\n"
                                 "-----------------------------\n"
                                 "[0] Exit\n\n"
                                 "Enter your choice: "
                                 "\n\n\n-----------------------------\n"
                                 "***# Julia Set #***\n"
                                 "Please choose an Option\n"
                                 "-----------------------------\n"
                                 "[1] Julia Set z^2\n"
                                 "[2] Julia Set z^4\n"
                                 "[3] Julia Set z^8\n"
                                 "-----------------------------\n"
                                 "[4] Julia Set z^2 Frames\n"
                                 "[5] Julia Set z^4 Frames\n"
                                 "-----------------------------\n"
                                 "[6] Julia Set z^2 Video\n"
                                 "[7] Julia Set z^4 Video\n"
                                 "-----------------------------\n"
                                 "[0] Exit\n\n"
                                 "Enter your choice: "
                                 "Exiting\n"
                                 "Exiting\n";

    std::string actualOutput = captureCout();

    assert(actualOutput == expectedOutput);
}

int main() {
    testJuliaChoice();
    testNoiseChoice();
    testGaussianChoice();
    testMain();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}