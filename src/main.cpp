#include "primitive.hpp"
#include "ray.hpp"
#include <rng.hpp>
#include <pdf.hpp>
#include <sampler.hpp>
#include <exploit.hpp>
#include <image.hpp>

int main() 
{
    PBR_::Image img;

    PBR_::Sphere sph;

    sph.origin = {0.0, 0.0, -1.5};
    sph.radius = 0.5;
    sph.r = 1.0;
    sph.g = 0.0;
    sph.b = 1.0;

    std::double_t t;

    PBR_::Ray r;

    r.origin = {0.0, 0.0, -.2};

    std::double_t aspect_ratio = static_cast<std::double_t>(img.width)/img.height;
    std::double_t fov = std::tan(0.01745329251 * (90.0/2.0));
    for(std::uint64_t y{0ULL}; y < img.height; ++y)
    {
        std::double_t pixelNormalizeY = (static_cast<std::double_t>(y) + 0.5)/img.height;
        std::double_t bg = pixelNormalizeY;
        for(std::uint64_t x{0ULL}; x < img.width; ++x)
        {
            std::double_t pixelNormalizeX = (static_cast<std::double_t>(x) + 0.5)/img.width;
            r.direction.x = (2.0 * pixelNormalizeX - 1.0) * fov * aspect_ratio;
            r.direction.y = (1.0 - 2.0 * pixelNormalizeY) * fov;
            r.direction.z = -1.0;

            r.direction = normalize(r.direction);

            if(sph.intersect(r, t)) img.putPixel(x, y, sph.r, sph.g, sph.b);
            else img.putPixel(x, y, bg, bg, 1.);
        }
    }

    img.saveImg("render_result/test.ppm");
}