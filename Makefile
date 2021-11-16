rel:
	gcc -Ofast -march=native src/main.c -o main

debug:
	gcc -Wall -Wextra -Wpedantic src/main.c -o main