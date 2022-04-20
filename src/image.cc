#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "image.hh"

/* Create an Image structure and allocates memory for its data,
image data will be NULL if allocation fails */
Image create_image(int width, int height)
{
    Image image{NULL, width, height};
    image.data = (uint8_t *)malloc(width * height * 3 * sizeof(uint8_t));
    if (image.data == NULL)
    {
        puts("Failed to allocate memory for image");
    }
    return image;
}

void free_image(Image &image)
{
    free(image.data);
}

/* Export image as a binary RGB PPM image, returns 0 on success, 1 on failure */
int write_ppm(const char *filepath, Image &image)
{
    FILE *file = fopen(filepath, "wb");
    if (file == NULL)
    {
        puts("Error opening file");
        return 1;
    }
    fprintf(file, "P6 %d %d 255\n", image.width, image.height);
    fwrite(image.data, sizeof(uint8_t), image.width * image.height * 3, file);
    fclose(file);
    return 0;
}