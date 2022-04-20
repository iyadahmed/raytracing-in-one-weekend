cmake_minimum_required(VERSION 3.10)

project(raytracing_in_one_weekend VERSION 1.0 DESCRIPTION "Raytracing in one weekend" LANGUAGES CXX)

add_executable(render
    src/main.cc
    src/image.cc src/image.hh
    src/sphere.hh
    src/vec3.hh
    src/ray.hh
    src/hittable.hh
)

target_compile_features(render PUBLIC cxx_std_11)
set_target_properties(render PROPERTIES CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(render PUBLIC m)
    target_compile_options(render PUBLIC "-Ofast;-march=native")
elseif(MSVC)
    target_compile_options(render PUBLIC "/O2")
endif()