#include <time.h>
#include <stdio.h>
#include <stdint.h>

#include "vec3.hh"
#include "image.hh"
#include "ray.hh"
#include "sphere.hh"

typedef Vec3 Color3;

static double lerp(double a, double b, double t)
{
    return (1. - t) * a + t * b;
}

static void write_color(uint8_t *buf, Color3 *color)
{
    *buf = (uint8_t)(255 * color->x);
    *(buf + 1) = (uint8_t)(255 * color->y);
    *(buf + 2) = (uint8_t)(255 * color->z);
}

static void ray_color(Color3 &out, const Ray &ray)
{
    Vec3 normal = ray.direction.normalized();
    double t = .5 * (normal.y + 1.);
    out.x = lerp(1., .5, t);
    out.y = lerp(1., .7, t);
    out.z = 1.;
}

static void raytrace()
{
    // Image
    const float aspect_ratio = 16.0f / 9.0f;
    const int image_width = 1280;
    const int image_height = (unsigned int)(image_width / aspect_ratio);

    // Camera
    const float viewport_height = 2.0f;
    const float viewport_width = aspect_ratio * viewport_height;
    const float focal_length = 1.0f;

    Point3 origin(0., 0., 0.);
    Vec3 horizontal(viewport_width, 0., 0.);
    Vec3 vertical(0., viewport_height, 0.);

    Vec3 lower_left_corner = origin - (horizontal + vertical) * .5;
    lower_left_corner.z -= focal_length;

    Sphere sphere({0., 0., -1.}, .5);
    HitRecord hit_record;
    Ray ray(origin, 0.);
    Color3 final_color(1., 0., 1.);

    Image *image = create_image(image_width, image_height);
    uint8_t *image_buf_iter = image->data;

    int i, j;
    double u, v;

    for (j = image->height; j > 0; j--)
    {
        for (i = 0; i < image->width; i++)
        {
            u = (double)i / image_width;
            v = (double)j / image_height;

            ray.direction.x = lower_left_corner.x + u * horizontal.x + v * vertical.x - origin.x;
            ray.direction.y = lower_left_corner.y + u * horizontal.y + v * vertical.y - origin.y;
            ray.direction.z = lower_left_corner.z + u * horizontal.z + v * vertical.z - origin.z;

            if (sphere.hit(ray, 0., 1., hit_record))
            {
                final_color.x = 1.;
                final_color.y = 0.;
                final_color.z = 0.;
            }
            else
            {
                ray_color(final_color, ray);
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