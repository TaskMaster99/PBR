#include <camera.hpp>
#include <vecmath.hpp>
#include <exploit.hpp>
#include <image.hpp>
#include <pdf.hpp>
#include <primitive.hpp>
#include <ray.hpp>
#include <rng.hpp>
#include <sampler.hpp>
#include <transform.hpp>

enum TransType
{
  RotationX,
  RotationY,
  RotationZ
};

void GenerateRotation(const std::uint64_t max_frame, const TransType type)
{
  PBR_::Image img;

  PBR_::Camera cam{
      {0.0, 0.0, 0.5}
    };

  PBR_::Sphere sph;

  sph.origin = {0.0, 0.0, -1};
  sph.radius = 0.5;
  sph.rgb = {1.0, 0.0, 1.0};

  std::double_t aspect_ratio =
      static_cast<std::double_t>(img.width) / img.height;
  std::double_t fov = std::tan(PBR_::radian(60.0 / 2.0));

  PBR_::Transformation RasterToScreenSpace =
      PBR_::ScreenFromNDC(aspect_ratio, fov) *
      PBR_::NDCFromRaster(static_cast<std::double_t>(img.width),
                          static_cast<std::double_t>(img.height));

  PBR_::Transformation CameraToWorldSpace = PBR_::LookAt(cam);

  const std::double_t step = 2*std::numbers::pi/static_cast<std::double_t>(max_frame);
  PBR_::Transformation rotate;
  char loc[32];
  for(std::uint64_t frame{0ULL}; frame < max_frame; ++frame)
  {
    const std::double_t theta = static_cast<std::double_t>(frame) * step;

    switch (type) 
    {
      case RotationX:
        rotate = PBR_::RotationX(theta);
        std::snprintf(loc, 32,"x");
        break;
      case RotationY:
        rotate = PBR_::RotationY(theta);
        std::snprintf(loc, 32,"y");
        break;
      default:
        rotate = PBR_::RotationZ(theta);
        std::snprintf(loc, 32,"z");
        break;
    }


    for (std::uint64_t y{0ULL}; y < img.height; ++y) 
    {
        std::double_t shade = (static_cast<std::double_t>(y)) / img.height;

        for (std::uint64_t x{0ULL}; x < img.width; ++x) 
        {
        PBR_::Point3 raster_coord = {static_cast<std::double_t>(x), static_cast<std::double_t>(y), -1};
        PBR_::Point3 screen_coord = RasterToScreenSpace(raster_coord);
        PBR_::Vector3 screen_dir{
            screen_coord.x,
            screen_coord.y,
            screen_coord.z
        };

        PBR_::Ray ray{{0.0,0.0,0.0}, PBR_::normalize(screen_dir), 0.0};


        ray = CameraToWorldSpace(rotate(ray));

        if (intersect(sph, ray))
            img.putPixel(x, y, sph.rgb);
        else
            img.putPixel(x, y, {shade, shade, 1.});
        }
    }
    char name_file[256];
    std::snprintf(name_file,256, "frame/rotation/%s/frame%ld.ppm",loc, frame);
    img.saveImg(name_file);
  }
}

int main() 
{
  GenerateRotation(120ULL, RotationX);
  GenerateRotation(120ULL, RotationY);
  GenerateRotation(120ULL, RotationZ);
}