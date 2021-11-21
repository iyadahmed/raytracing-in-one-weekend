#ifndef IMAGE_H
#define IMAGE_H

typedef struct _Image {
    char *data;
    int width;
    int height;
} Image;


Image *create_image(int width, int height);
void free_image(Image *image);
int write_ppm(char *filepath, Image *image);

#endif