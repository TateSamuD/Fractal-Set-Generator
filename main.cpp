#include <iostream>

#include "base.h"
#include "fractal.h"
#include "image_gen.h"
#include "video_gen.h"

void mk_dir(const char *dir)
{
   std::stringstream cmd;
   cmd << "mkdir " << dir;
   int ret = system(cmd.str().c_str());
   if (ret == 0){
      std::cout << "Directory " << dir << " created\n";
   }
}

bool frame_warning()
{
   char choice;
   std::cout << "This will generate " << NUM_FRAMES << " frames of " << F_SIZE << "mb each\n";
   std::cout << "This will take a while and take up " << F_SIZE * NUM_FRAMES << "mb of space\n";
   std::cout << "Do you want to continue? [y/n]: ";
   std::cin >> choice;
   if (choice == 'y')
   {
      return true;
   }
   else
   {
      return false;
   }
}

void julia_choice()
{
   int choice = -1;
   while (choice != 0)
   {
      std::cout << "\n\n\n-----------------------------\n";
      std::cout << "***# Julia Set #***\n";
      std::cout << "Please choose an Option\n";
      std::cout << "-----------------------------\n";
      std::cout << "[1] Julia Set z^2\n";
      std::cout << "[2] Julia Set z^4\n";
      std::cout << "[3] Julia Set z^8\n";
      std::cout << "-----------------------------\n";
      std::cout << "[4] Julia Set z^2 Frames\n";
      std::cout << "[5] Julia Set z^4 Frames\n";
      std::cout << "-----------------------------\n";
      std::cout << "[6] Julia Set z^2 Video\n";
      std::cout << "[7] Julia Set z^4 Video\n";
      std::cout << "-----------------------------\n";
      std::cout << "[0] Exit\n\n";
      std::cout << "Enter your choice: ";
      std::cin >> choice;

      switch (choice)
      {
      case 1:
         generate_julia_z2_image();
         break;
      case 2:
         generate_julia_z4_image();
         break;
      case 3:
         generate_julia_z8_image();
         break;
      case 4:
         if (!frame_warning()){break;}
         generate_julia_z2_offset_frames();
         break;
      case 5:
         if (!frame_warning()){break;}
         generate_julia_z4_offset_frames();
         break;
      case 6:
         generate_julia_z2_video();
         break;
      case 7:
         generate_julia_z4_video();
         break;
      case 0:
         std::cout << "Exiting\n";
         break;
      default:
         std::cout << "Invalid choice\n";
         break;
      }
   }
}

void turbulence_choice()
{
   int choice = -1;
   while (choice != 0)
   {
      std::cout << "\n\n\n-----------------------------\n";
      std::cout << "***# Turbulence #***\n";
      std::cout << "Please choose an Option\n";
      std::cout << "-----------------------------\n";
      std::cout << "[1] Turbulence\n";
      std::cout << "[2] Turbulence Video\n";
      std::cout << "-----------------------------\n";
      std::cout << "[0] Exit\n\n";
      std::cout << "Enter your choice: ";
      std::cin >> choice;

      switch (choice)
      {
      case 1:
         generate_turbulence_image();
         break;
      case 2:
         if (!frame_warning()){break;}
         generate_turbulence_frame();
         generate_turbulence_video();
         break;
      case 0:
         std::cout << "Exiting\n";
         break;
      default:
         std::cout << "Invalid choice\n";
         break;
      }
   }
}

void noise_choice()
{
   int choice = -1;
   while (choice != 0)
   {
      std::cout << "\n\n\n-----------------------------\n";
      std::cout << "***# Noise #***\n";
      std::cout << "Please choose an Option\n";
      std::cout << "-----------------------------\n";
      std::cout << "[1] Noise\n";
      std::cout << "[2] Noise Fractal\n";
      std::cout << "-----------------------------\n";
      std::cout << "[0] Exit\n\n";
      std::cout << "Enter your choice: ";
      std::cin >> choice;

      switch (choice)
      {
      case 1:
         generate_noise_image();
         break;
      case 2:
         generate_fractal_noise_image();
         break;
      case 0:
         std::cout << "Exiting\n";
         break;
      default:
         std::cout << "Invalid choice\n";
         break;
      }
   }
}

void gaussian_choice()
{
   int choice = -1;
   while (choice != 0)
   {
      std::cout << "\n\n\n-----------------------------\n";
      std::cout << "***# Gaussian #***\n";
      std::cout << "Please choose an Option\n";
      std::cout << "-----------------------------\n";
      std::cout << "[1] Gaussian\n";
      std::cout << "[2] Gaussian Fractal\n";
      std::cout << "-----------------------------\n";
      std::cout << "[0] Exit\n\n";
      std::cout << "Enter your choice: ";
      std::cin >> choice;

      switch (choice)
      {
      case 1:
         generate_gaussian_noise_image();
         break;
      case 2:
         generate_fractal_gaussian_image();
         break;
      case 0:
         std::cout << "Exiting\n";
         break;
      default:
         std::cout << "Invalid choice\n";
         break;
      }
   }
}

int main(int argc, char *argv[])
{

   srand(time(NULL));
   mk_dir("Julia_z4_Frames");
   mk_dir("Julia_z2_Frames");
   mk_dir("Turbulence_Frames");

   int choice = -1;

   while (choice != 0)
   {
      std::cout << "\n-----------------------------\n";
      std::cout << "***# Image Processing #***\n";
      std::cout << "Please choose an Option\n";
      std::cout << "-----------------------------\n";
      std::cout << "[1] Mandelbrot Set Image\n";
      std::cout << "[2] Julia Set [Options]\n";
      // std::cout << "[3] Fractal Flame (adjust c value)\n";
      // std::cout << "[4] Lorenz System Image (adjust c value)\n";
      // std::cout << "[5] Aizawa Attractor (adjust c value)\n";
      // std::cout << "[6] Noise  [Options] (adjust c value)\n";
      // std::cout << "[7] Gaussian  [Options] (adjust c value)\n";
      std::cout << "[8] Turbulence [Options]\n";
      std::cout << "-----------------------------\n";
      std::cout << "[0] Exit\n\n";
      std::cout << "Enter your choice: ";
      std::cin >> choice;

      switch (choice)
      {
      case 1:
         generate_mandelbrot_image();
         break;
      case 2:
         julia_choice();
         break;
      // case 3:
      //    generate_fractal_flame_image();
      //    break;
      // case 4:
      //    generate_lorenz_image();
      //    break;
      // case 5:
      //    generate_aizawa_image();
      //    break;
      // case 6:
      //    noise_choice();
      //    break;
      // case 7:
      //    gaussian_choice();
      //    break;
      case 8:
         turbulence_choice();
         break;
      case 0:
         std::cout << "Exiting\n";
         break;
      default:
         std::cout << "Invalid choice\n";
         break;
      }
   }

   return 0;
}