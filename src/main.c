#include "vec3.h"
#include "image.h"
#include "ray.h"
#include <time.h>
#include <stdio.h>

double lerp(double a, double b, double t)
{
  return (1. - t) * a + t * b;
}

void write_color(char *buf, Color3 color)
{
  *buf = (char)(255 * color.r);
  *(buf + 1) = (char)(255 * color.g);
  *(buf + 2) = (char)(255 * color.b);
}

int raytrace()
{
  // Image
  const float aspect_ratio = 16.0 / 9.0;
  const unsigned int image_width = 100;
  const unsigned int image_height = (unsigned int)(image_width / aspect_ratio);

  // Camera
  const float viewport_height = 2.0;
  const float viewport_width = aspect_ratio * viewport_height;
  const float focal_LEN = 1.0;

  Point3 origin = {.x = 0., .y = 0., .z = 0.};
  Vec3 horizontal = {.x = viewport_width, .y = 0., .z = 0.};
  Vec3 vertical = {.x = 0., .y = viewport_height, .z = 0.};

  Vec3 lower_left_corner;
  lower_left_corner.x = origin.x - .5 * (horizontal.x + vertical.x);
  lower_left_corner.y = origin.y - .5 * (horizontal.y + vertical.y);
  lower_left_corner.z = origin.z - .5 * (horizontal.z + vertical.z) - focal_LEN;

  Ray r;
  r.origin.x = origin.x;
  r.origin.y = origin.y;
  r.origin.x = origin.z;

  Color3 final_color = {.r = 1., .g = 0., .b = 1.};

  Image *image = create_image(image_width, image_height);

  char *image_buf_iter = image->data;

  int i, j;
  double u, v;

  for (j = image->height; j > 0; j--)
  {
    for (i = 0; i < image->width; i++)
    {
      u = (double)i / image_width;
      v = (double)j / image_height;

      r.direction.x = lower_left_corner.x + u * horizontal.x + v * vertical.x - origin.x;
      r.direction.y = lower_left_corner.y + u * horizontal.y + v * vertical.y - origin.y;
      r.direction.z = lower_left_corner.z + u * horizontal.z + v * vertical.z - origin.z;

      write_color(image_buf_iter, final_color);
      image_buf_iter += 3;
    }
  }

  write_ppm("out.ppm", image);

  free_image(image);
  image = NULL;
}

int main()
{
  raytrace();
  return 0;
}