#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "image.hh"

/* Allocate memory for an Image structure and its data,
returns a pointer to the image structure on success,
otherwise it returns NULL */
Image *create_image(int width, int height)
{
    Image *image = (Image *)malloc(sizeof(Image));
    image->data = (uint8_t *)malloc(width * height * 3 * sizeof(uint8_t));
    if (NULL == image->data)
    {
        puts("Failed to allocate memory for image");
        return NULL;
    }
    image->width = width;
    image->height = height;
    return image;
}

void free_image(Image *image)
{
    free(image->data);
    free(image);
}

/* Export image as a binary RGB PPM image, returns 0 on success, 1 on failure */
int write_ppm(const char *filepath, Image *image)
{
    FILE *file = fopen(filepath, "wb");
    if (NULL == file)
    {
        puts("Error opening file");
        return 1;
    }
    fprintf(file, "P6 %d %d 255\n", image->width, image->height);
    fwrite(image->data, sizeof(uint8_t), image->width * image->height * 3, file);
    fclose(file);
    return 0;
}