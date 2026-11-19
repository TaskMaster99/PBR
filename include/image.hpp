#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>

namespace  PBR_
{
struct Image
{
    std::uint64_t width;
    std::uint64_t height;

    std::uint8_t* r_channel;
    std::uint8_t* g_channel;
    std::uint8_t* b_channel;

    Image() : width(800ULL), height(600ULL)
    {
        r_channel = (std::uint8_t*)std::malloc(width * height * sizeof(std::uint8_t));
        g_channel = (std::uint8_t*)std::malloc(width * height * sizeof(std::uint8_t));
        b_channel = (std::uint8_t*)std::malloc(width * height * sizeof(std::uint8_t));
    }


    Image(const std::uint64_t w, const std::uint64_t h) : width(w), height(h)
    {
        r_channel = (std::uint8_t*)std::malloc(width * height * sizeof(std::uint8_t));
        g_channel = (std::uint8_t*)std::malloc(width * height * sizeof(std::uint8_t));
        b_channel = (std::uint8_t*)std::malloc(width * height * sizeof(std::uint8_t));
    }

    void putPixel(std::uint64_t x, std::uint64_t y, 
                  std::double_t r, std::double_t g, std::double_t b)
    {
        r_channel[y * width + x] = static_cast<std::uint8_t>(r * 255.0);
        g_channel[y * width + x] = static_cast<std::uint8_t>(g * 255.0);
        b_channel[y * width + x] = static_cast<std::uint8_t>(b * 255.0);
    }

    void saveImg(const char* filename)
    {

        std::FILE* file = std::fopen(filename, "w");
        if (file == nullptr)
        {
            std::printf("Failed to open. Please check if filepath exist.\n");
            std::exit(EXIT_FAILURE);
        }

        std::fprintf( file, "P3\n");
        std::fprintf( file, "%ld %ld\n", width, height);
        std::fprintf( file, "%d\n", 255);

        for(std::uint64_t p{0ULL}; p < width * height; ++p)
        {
            std::fprintf(file, "%u %u %u\n", r_channel[p], g_channel[p], b_channel[p]);
        }


        std::fclose(file);
    }

    ~Image()
    {
        std::free(r_channel);
        std::free(g_channel);
        std::free(b_channel);
    }


};
};
#endif