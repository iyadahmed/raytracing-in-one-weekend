#include "vec3.h"
#include "image.h"
#include "ray.h"
#include "sphere.h"

#include <time.h>
#include <stdio.h>
#include <stdint.h>

static double lerp(double a, double b, double t)
{
  return (1. - t) * a + t * b;
}

static void write_color(uint8_t *buf, Color3 *color)
{
  *buf = (uint8_t)(255 * color->r);
  *(buf + 1) = (uint8_t)(255 * color->g);
  *(buf + 2) = (uint8_t)(255 * color->b);
}

void ray_color(Color3 *out, Ray *ray)
{
  Vec3 unit_direction;
  v3_normalize(&unit_direction, &ray->direction);
  double t = .5 * (unit_direction.y + 1.);
  out->r = lerp(1., .5, t);
  out->g = lerp(1., .7, t);
  out->b = 1.;
}

static int raytrace()
{
  // Image
  const float aspect_ratio = 16.0f / 9.0f;
  const int image_width = 4096;
  const int image_height = (unsigned int)(image_width / aspect_ratio);

  // Camera
  const float viewport_height = 2.0f;
  const float viewport_width = aspect_ratio * viewport_height;
  const float focal_length = 1.0f;

  Point3 origin = {0., 0., 0.};
  Vec3 horizontal = {viewport_width, 0., 0.};
  Vec3 vertical = {0., viewport_height, 0.};

  Vec3 lower_left_corner;
  lower_left_corner.x = origin.x - .5 * (horizontal.x + vertical.x);
  lower_left_corner.y = origin.y - .5 * (horizontal.y + vertical.y);
  lower_left_corner.z = origin.z - .5 * (horizontal.z + vertical.z) - focal_length;

  Ray r;
  r.origin.x = origin.x;
  r.origin.y = origin.y;
  r.origin.x = origin.z;

  Color3 final_color = {1., 0., 1.};

  Image *image = create_image(image_width, image_height);
  uint8_t *image_buf_iter = image->data;

  int i, j;
  double u, v;

  Sphere sphere;
  sphere.center = (Vec3){0., 0., -1.};
  sphere.radius = .5;

  HitRecord hit_record;

  for (j = image->height; j > 0; j--)
  {
    for (i = 0; i < image->width; i++)
    {
      u = (double)i / image_width;
      v = (double)j / image_height;

      r.direction.x = lower_left_corner.x + u * horizontal.x + v * vertical.x - origin.x;
      r.direction.y = lower_left_corner.y + u * horizontal.y + v * vertical.y - origin.y;
      r.direction.z = lower_left_corner.z + u * horizontal.z + v * vertical.z - origin.z;

      if (hit_sphere(&sphere, &r, 0., 1., &hit_record))
      {
        final_color.r = 1.;
        final_color.g = 0.;
        final_color.b = 0.;
      }
      else
      {
        ray_color(&final_color, &r);
      }
      write_color(image_buf_iter, &final_color);
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