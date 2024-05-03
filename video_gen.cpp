#include "video_gen.h"

void generate_julia_z2_video(){
   std::stringstream cmd;
   cmd << "ffmpeg -y -framerate " << FPS << " -i ./Julia_z2_Frames/julia_z2_frame_%06d.bmp -c:v libx264 -pix_fmt yuv420p julia_z2.mp4";

   int ret = system(cmd.str().c_str());
   if (ret == 0)
   {
      std::cout << "Video generated successfully\n";
   }
   else
   {
      std::cout << "Error generating video\n";
      std::cout << "Please ensure that ffmpeg is installed\n The commands to install ffmpeg are:\n sudo apt-get install ffmpeg\n sudo snap install ffmpeg\n";
   }
}

void generate_julia_z4_video(){
   std::stringstream cmd;
   cmd << "ffmpeg -y -framerate " << FPS << " -i ./Julia_z4_Frames/julia_z4_frame_%06d.bmp -c:v libx264 -pix_fmt yuv420p julia_z4.mp4";

   int ret = system(cmd.str().c_str());
   if (ret == 0)
   {
      std::cout << "Video generated successfully\n";
   }
   else
   {
      std::cout << "Error generating video\n";
      std::cout << "Please ensure that ffmpeg is installed\n The commands to install ffmpeg are:\n sudo apt-get install ffmpeg\n sudo snap install ffmpeg\n";
   }
}

void generate_turbulence_video(){
   std::stringstream cmd;
   cmd << "ffmpeg -y -framerate " << FPS << " -i ./Turbulence_Frames/turbulence_frame_%06d.bmp -c:v libx264 -pix_fmt yuv420p turbulence.mp4";

   int ret = system(cmd.str().c_str());
   if (ret == 0)
   {
      std::cout << "Video generated successfully\n";
   }
   else
   {
      std::cout << "Error generating video\n";
      std::cout << "Please ensure that ffmpeg is installed\n The commands to install ffmpeg are:\n sudo apt-get install ffmpeg\n sudo snap install ffmpeg\n";
   }
}