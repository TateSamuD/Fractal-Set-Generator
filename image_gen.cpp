#include "image_gen.h"

double smooth_step(double edge0, double edge1, double x)
{
   x = std::clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
   return x * x * (3 - 2 * x);
}

RGB get_tur_colour(double t)
{
   double r = 9 * (1 - t) * (1 - t) * (1 - t) * t * 255;
   double g = 15 * (1 - t) * t * t * t * 255;
   double b = 8.5 * (1 - t) * (1 - t) * t * t * 255;
   return RGB(r, g, b);
}

RGB get_colour(int iter, int max_iter)
{
   if (iter == max_iter)
   {
      // return RGB(0, 0, 0);
      return RGB(255, 255, 255);
   }
   else
   {
      double t = static_cast<double>(iter) / max_iter;
      double smooth_t = smooth_step(0.0, 1.0, t);
      // /* Generates Black and White*/
      // uint8_t r = static_cast<uint8_t>(255 * cos(2 * M_PI * t));         // Red value
      // uint8_t g = static_cast<uint8_t>(255 * cos(2 * M_PI * t));         // Green value
      // uint8_t b = static_cast<uint8_t>(255 * cos(2 * M_PI *(1 - t)));    // Blue value

      // /* Generates Rainbow */
      // uint8_t r = static_cast<uint8_t>(255 * cos(2 * M_PI * t));        // Red value
      // uint8_t g = static_cast<uint8_t>(255 * cos(2 * M_PI * t + 2));    // Green value
      // uint8_t b = static_cast<uint8_t>(255 * cos(2 * M_PI * t + 4));    // Blue value

      // /* Generates Blue to Red */
      // uint8_t r = static_cast<uint8_t>(255 * cos(2 * M_PI * t));        // Red value
      // uint8_t g = 0;                                                    // Green value
      // uint8_t b = static_cast<uint8_t>(255 * cos(2 * M_PI * (1 - t))); // Blue value

      // /* Generates Red to Blue */
      // uint8_t r = static_cast<uint8_t>(255 * cos(2 * M_PI * (1 - t))); // Red value
      // uint8_t g = 0;                                                    // Green value
      // uint8_t b = static_cast<uint8_t>(255 * cos(2 * M_PI * t));        // Blue value

      // /* Generates Blue Circle*/
      // uint8_t r = static_cast<uint8_t>(255 * sin(2 * M_PI * t));         // Red value
      // uint8_t g = static_cast<uint8_t>(255 * sin(2 * M_PI * t));         // Green value
      // uint8_t b = static_cast<uint8_t>(255 * sin(2 * M_PI *(1 - t)));    // Blue value

      // /* Generates Lime Green */
      // uint8_t r = static_cast<uint8_t>(255 * sin(2 * M_PI * t));         // Red value
      // uint8_t g = static_cast<uint8_t>(255 * sin(2 * M_PI * t + 2));         // Green value
      // uint8_t b = static_cast<uint8_t>(255 * sin(2 * M_PI * t + 4));    // Blue value

      // /* Generates weird gradient Blue-Red*/
      // uint8_t r = static_cast<uint8_t>(255 * tan(2 * M_PI * t + 4));         // Red value
      // uint8_t g = static_cast<uint8_t>(255 * tan(2 * M_PI * t));         // Green value
      // uint8_t b = static_cast<uint8_t>(255 * tan(2 * M_PI * t + 2));    // Blue value

      /* Black and Purple*/
      uint8_t r = static_cast<uint8_t>(255 * smooth_t * tan(2 * M_PI * t + 4)); // Red value
      uint8_t g = static_cast<uint8_t>(255 * smooth_t * cos(2 * M_PI * t));     // Green value
      uint8_t b = static_cast<uint8_t>(255 * smooth_t * tan(2 * M_PI * t + 2)); // Blue value
      return RGB(r, g, b);
   }
}

void generate_mandelbrot_image()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Mandelbrot image\n";
   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = mandelbrot(x0, y0, MAX_ITER);
         RGB rgb = get_colour(iter, MAX_ITER);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Mandelbrot image generated\n";
   std::ofstream image("mandelbrot.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_julia_z2_image()
{

   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;
   int max_iter = 1000;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Julia z^2 image\n";
   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = julia_z2(x0, y0, max_iter);
         RGB rgb = get_colour(iter, max_iter);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Julia z^2 image generated\n";
   std::ofstream image("julia_z2.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_julia_z2_offset_frames()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;
   int max_iter = 1000;
   double accuracy = 0.001;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Julia z^2 offset frames\n";

   for (int frame = 0; frame < NUM_FRAMES; frame++)
   {
      std::cout << "\033[2A"; // Move cursor up one line
      std::cout << "Overall Progress:   " << frame << "/" << NUM_FRAMES << std::endl;
      // std::cout << "\033[A"; // Move cursor up one line
      std::cout << std::flush;
      for (int y = HEIGHT - 1; y >= 0; y--)
      {
#pragma omp parallel for
         for (int x = 0; x < WIDTH; x++)
         {
            double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
            int iter = julia_z2_offset(x0, y0, max_iter, frame * accuracy);
            RGB rgb = get_colour(iter, max_iter);

            int index = (y * WIDTH + x) * 3;
            buffer[index] = rgb.b;
            buffer[index + 1] = rgb.g;
            buffer[index + 2] = rgb.r;
         }

         for (int i = 0; i < padding_size; i++)
         {
            buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
         }

         int processed_pixels = HEIGHT - y;
         if (processed_pixels % (HEIGHT / 5) == 0)
         {
            double progress = (double)processed_pixels / HEIGHT * 100.0;
            // printf("Progress: %.2f%%\n", progress);
            std::cout << "Frame " + std::to_string(frame + 1) + " Progress: " << std::setw(6) << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
            std::cout << "\033[A"; // Move cursor up one line
            std::cout << std::flush;
         }
      }
      std::cout << "Frame " + std::to_string(frame + 1) + " Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

      std::ostringstream oss;
      oss << "/julia_z2_frame_" << std::setw(6) << std::setfill('0') << frame + 1 << ".bmp";
      std::string filename = oss.str();
      std::ofstream image("./Julia_z2_Frames" + filename, std::ios::binary);
      if (image.is_open())
      {
         image.write(reinterpret_cast<char *>(file_header), 54);
         image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
         if (image.fail())
         {
            std::cout << "Error writing to file: " << filename << std::endl;
         }
         image.close();
      }
      else
      {
         std::cout << "Error opening file: " << filename << std::endl;
      }
   }

   std::cout << "Julia z^2 frames generated\n";
}

void generate_julia_z4_image()
{

   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;
   int max_iter = 5000;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Julia z^4 image\n";
   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = julia_z4(x0, y0, max_iter);
         RGB rgb = get_colour(iter, max_iter);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Julia z^4 image generated\n";
   std::ofstream image("julia_z4.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_julia_z4_offset_frames()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;
   int max_iter = 10000;
   double accuracy = 0.005;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Julia z^4 offset frames\n";

   for (int frame = 0; frame < NUM_FRAMES; frame++)
   {
      std::cout << "\033[2A"; // Move cursor up one line
      std::cout << "Overall Progress:   " << frame << "/" << NUM_FRAMES << std::endl;
      // std::cout << "\033[A"; // Move cursor up one line
      std::cout << std::flush;

#pragma omp parallel for
      for (int y = HEIGHT - 1; y >= 0; y--)
      {
         for (int x = 0; x < WIDTH; x++)
         {
            double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
            int iter = julia_z4_offset(x0, y0, max_iter, frame * accuracy);
            RGB rgb = get_colour(iter, max_iter);

            int index = (y * WIDTH + x) * 3;
            buffer[index] = rgb.b;
            buffer[index + 1] = rgb.g;
            buffer[index + 2] = rgb.r;
         }

         for (int i = 0; i < padding_size; i++)
         {
            buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
         }

         int processed_pixels = HEIGHT - y;
         if (processed_pixels % (HEIGHT / 5) == 0)
         {
            double progress = (double)processed_pixels / HEIGHT * 100.0;
            // printf("Progress: %.2f%%\n", progress);
            std::cout << "Frame " + std::to_string(frame + 1) + " Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
            std::cout << "\033[A"; // Move cursor up one line
            std::cout << std::flush;
         }
      }
      std::cout << "Frame " + std::to_string(frame + 1) + " Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

      std::ostringstream oss;
      oss << "julia_z4_frame_" << std::setfill('0') << std::setw(6) << frame + 1 << ".bmp";
      std::string filename = oss.str();
      std::ofstream image("./Julia_z4_Frames/" + filename, std::ios::binary);
      if (image.is_open())
      {
         image.write(reinterpret_cast<char *>(file_header), 54);
         image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
         if (image.fail())
         {
            std::cout << "Error writing to file: " << filename << std::endl;
            return;
         }
         image.close();
      }
      else
      {
         std::cout << "Error opening file: " << filename << std::endl;
         return;
      }
   }

   std::cout << "Julia z^4 frames generated\n";
}

void generate_julia_z8_image()
{

   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;
   int max_iter = 5000;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Julia z^8 image\n";

   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = julia_z8(x0, y0, max_iter);
         RGB rgb = get_colour(iter, max_iter);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Julia z^8 image generated\n";
   std::ofstream image("julia_z8.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_lorenz_image()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Lorenz image\n";

   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = lorenz(x0, y0, MAX_ITER);
         RGB rgb = get_colour(iter, MAX_ITER);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Lorenz image generated\n";
   std::ofstream image("lorenz.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_aizawa_image()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;
   int max_iter = 10000;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Aizawa image\n";

   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = aizawa(x0, y0, MAX_ITER);
         RGB rgb = get_colour(iter, MAX_ITER);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Aizawa image generated\n";
   std::ofstream image("aizawa.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_noise_image()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Noise image\n";

   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = noise(x0, y0, MAX_ITER);
         RGB rgb = get_colour(iter, MAX_ITER);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Noise image generated\n";
   std::ofstream image("noise.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_gaussian_noise_image()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Gaussian Noise image\n";

   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = gaussian(x0, y0, MAX_ITER);
         RGB rgb = get_colour(iter, MAX_ITER);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Gaussian Noise image generated\n";
   std::ofstream image("gaussian_noise.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_turbulence_image()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Turbulence image\n";

   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = turbulence(x0, y0, MAX_ITER);
         RGB rgb = get_tur_colour(iter);
         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Turbulence image generated\n";
   std::ofstream image("turbulence.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

// FIXME:
void generate_turbulence_frame()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Turbulence Frames\n";

   for (int frame = 0; frame < NUM_FRAMES; frame++)
   {
      std::cout << "Overall Progress:   " << frame << "/" << NUM_FRAMES << std::endl;
      for (int y = HEIGHT - 1; y >= 0; y--)
      {
         for (int x = 0; x < WIDTH; x++)
         {
            double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
            int iter = turbulence_frame(x0, y0, MAX_ITER, frame);
            RGB rgb = get_tur_colour(iter);
            int index = (y * WIDTH + x) * 3;
            buffer[index] = rgb.b;
            buffer[index + 1] = rgb.g;
            buffer[index + 2] = rgb.r;
         }

         for (int i = 0; i < padding_size; i++)
         {
            buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
         }

         int processed_pixels = HEIGHT - y;
         if (processed_pixels % (HEIGHT / 5) == 0)
         {
            double progress = (double)processed_pixels / HEIGHT * 100.0;
            // printf("Progress: %.2f%%\n", progress);
            std::cout << "Frame " + std::to_string(frame + 1) + " Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
            std::cout << "\033[A"; // Move cursor up one line
            std::cout << std::flush;
         }
      }
      std::cout << "Frame " + std::to_string(frame + 1) + " Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

      std::ostringstream oss;
      oss << "turbulence_frame_" << std::setfill('0') << std::setw(6) << frame + 1 << ".bmp";
      std::string filename = oss.str();
      std::ofstream image("./Turbulence_Frames/" + filename, std::ios::binary);
      if (image.is_open())
      {
         image.write(reinterpret_cast<char *>(file_header), 54);
         image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
         image.close();
      }
      else
      {
         std::cout << "Error: Unable to open file\n";
      }
   }
   std::cout << "Turbulence Frames generated\n";
}

void generate_fractal_noise_image()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Fractal Noise image\n";

   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = fractal_noise(x0, y0, MAX_ITER);
         RGB rgb = get_colour(iter, MAX_ITER);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Fractal Noise image generated\n";
   std::ofstream image("fractal_noise.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_fractal_gaussian_image()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Fractal Gaussian image\n";

   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = fractal_gaussian(x0, y0, MAX_ITER);
         RGB rgb = get_colour(iter, MAX_ITER);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Fractal Gaussian image generated\n";
   std::ofstream image("fractal_gaussian.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}

void generate_fractal_flame_image()
{
   int padding_size = (4 - (WIDTH * sizeof(RGB)) % 4) % 4;
   int data_size = (WIDTH * sizeof(RGB) + padding_size) * HEIGHT;

   uint8_t file_header[54] = {
       0x42, 0x4D,                                             // BM - Windows Bitmap
       static_cast<uint8_t>(data_size + 54), 0x00, 0x00, 0x00, // File size
       0x00, 0x00, 0x00, 0x00,                                 // Reserved
       0x36, 0x00, 0x00, 0x00,                                 // Offset to image data
       0x28, 0x00, 0x00, 0x00,                                 // Info header size
       static_cast<uint8_t>(WIDTH), static_cast<uint8_t>(WIDTH >> 8),
       static_cast<uint8_t>(WIDTH >> 16), static_cast<uint8_t>(WIDTH >> 24), // Image Width
       static_cast<uint8_t>(HEIGHT), static_cast<uint8_t>(HEIGHT >> 8),
       static_cast<uint8_t>(HEIGHT >> 16), static_cast<uint8_t>(HEIGHT >> 24), // Image Height
       0x01, 0x00, 0x18, 0x00,                                                 // Planes, Bits per Pixel
       0x00, 0x00, 0x00, 0x00,                                                 // Compression (none), Image Size
       static_cast<uint8_t>(data_size), static_cast<uint8_t>(data_size >> 8),
       static_cast<uint8_t>(data_size >> 16), static_cast<uint8_t>(data_size >> 24), // Image Size
       0x13, 0x0B, 0x00, 0x00,                                                       // Horizontal Resolution
       0x13, 0x0B, 0x00, 0x00,                                                       // Vertical Resolution
       0x00, 0x00, 0x00, 0x00,                                                       // Colors in Palette
       0x00, 0x00, 0x00, 0x00                                                        // Important Colors
   };

   std::vector<uint8_t> buffer(WIDTH * HEIGHT * 3 + padding_size * HEIGHT);

   std::cout << "\nGenerating Fractal Flame image\n";

   for (int y = HEIGHT - 1; y >= 0; y--)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         double x0 = (x - WIDTH / 2.0) * 4.0 / WIDTH;
         double y0 = (y - HEIGHT / 2.0) * 4.0 / WIDTH;
         int iter = fractal_flame(x0, y0, MAX_ITER);
         RGB rgb = get_colour(iter, MAX_ITER);

         int index = (y * WIDTH + x) * 3;
         buffer[index] = rgb.b;
         buffer[index + 1] = rgb.g;
         buffer[index + 2] = rgb.r;
      }

      for (int i = 0; i < padding_size; i++)
      {
         buffer[(y * WIDTH + WIDTH) * 3 + i] = 0x00;
      }

      int processed_pixels = HEIGHT - y;
      if (processed_pixels % (HEIGHT / 5) == 0)
      {
         double progress = (double)processed_pixels / HEIGHT * 100.0;
         // printf("Progress: %.2f%%\n", progress);
         std::cout << "Progress: " << std::fixed << std::setprecision(2) << progress << "%" << std::endl;
         std::cout << "\033[A"; // Move cursor up one line
         std::cout << std::flush;
      }
   }
   std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100.0 << "%" << std::endl;

   std::cout << "Fractal Flame image generated\n";
   std::ofstream image("fractal_flame.bmp", std::ios::binary);
   image.write(reinterpret_cast<char *>(file_header), 54);
   image.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
   image.close();
}
