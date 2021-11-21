rel:
	gcc -Ofast -march=native src/main.c src/image.c src/sphere.c src/vec3.c src/ray.c src/hittable.c -o main

debug:
	gcc -Wall -Wextra -Wpedantic src/main.c src/image.c src/sphere.c src/vec3.c src/ray.c src/hittable.c -o main