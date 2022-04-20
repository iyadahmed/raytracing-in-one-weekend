#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

typedef struct _Image
{
    uint8_t *data;
    int width;
    int height;
} Image;

Image *create_image(int width, int height);
void free_image(Image *image);
int write_ppm(const char *filepath, Image *image);

#endif