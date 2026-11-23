#include <camera.hpp>
#include <primitive.hpp>
#include <cstdint>
#include <image.hpp>
#include <transform.hpp>

int main()
{
    PBR_::Image img;
    PBR_::Plane up = 
    {
      {-0.5, 0.0, -0.5}, 
     {0.0, 0.0, -1.0}, 
     {0.0, 1.0, 0.0}, 
      {1.0, 1.0, 0.0}
    };

    PBR_::Camera user = {{0.0, 0.0, 2.0}};

    std::double_t aspect_ratio =
        static_cast<std::double_t>(img.width) / img.height;
    std::double_t fov = std::tan(PBR_::radian(60.0 / 2.0));


    PBR_::Transformation RasterToScreenSpace =
        PBR_::ScreenFromNDC(aspect_ratio, fov) *
        PBR_::NDCFromRaster(static_cast<std::double_t>(img.width),
                            static_cast<std::double_t>(img.height));

    PBR_::Transformation CameraToWorldSpace = PBR_::LookAt(user);

    for(std::uint64_t y = 0ULL; y < img.height; ++y)
    {
        std::double_t shade = (static_cast<std::double_t>(y)) / img.height;

        for(std::uint64_t x = 0ULL; x < img.width; ++x)
        {
            PBR_::Point3 raster_coord = {static_cast<std::double_t>(x), static_cast<std::double_t>(y), -1};
            PBR_::Point3 screen_coord = RasterToScreenSpace(raster_coord);
            PBR_::Vector3 screen_dir
            {
                screen_coord.x,
                screen_coord.y,
                screen_coord.z
            };

            PBR_::Ray ray{{0.0,0.0,0.0}, PBR_::normalize(screen_dir), 0.0};

            ray = CameraToWorldSpace(ray);

            if (intersect(up, ray))
                img.putPixel(x, y, up.rgb);
            else
                img.putPixel(x, y, {shade, shade, 1.});
        }
    }

    img.saveImg("plane_test.ppm");
}