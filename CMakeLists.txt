cmake_minimum_required(VERSION 3.10)

project(raytracing-c)
add_executable(raytracing_c src/main.c src/image.c src/sphere.c src/vec3.c src/ray.c src/hittable.c)

set(TARGET raytracing_c PROPERTY C_STANDARD 99)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(raytracing_c m)
    add_compile_options("-Ofast")
    add_compile_options("-march=native")
elseif(MSVC)
    add_compile_options("/O2")
endif()