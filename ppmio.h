#ifndef PPM_H
#define PPM_H

#include <stdio.h>

void write_ppm(unsigned char *data, unsigned int width, unsigned int height) {
	FILE *fptr = fopen("image.ppm", "wb");
	if (fptr == NULL) {
		printf("Erorr opening file\n");
		exit(1);
	}
	fprintf(fptr, "P6\n%d %d\n255\n", width, height);
	fwrite(data, sizeof(unsigned char), width * height * 3, fptr);
	fclose(fptr);
}

#endif