cmake_minimum_required(VERSION 3.10)
project(diffusion_limited_aggregation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)  # Enable debug symbols

add_compile_options(-g -O0 -fno-omit-frame-pointer)

# Gather your source files
file(GLOB SRCS "src/*.cpp")

# Create the executable first
add_executable(${PROJECT_NAME} ${SRCS})

# Find SDL2 via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Apply SDL2 config to the executable
target_include_directories(${PROJECT_NAME} PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

target_link_directories(${PROJECT_NAME} PUBLIC
    ${SDL2_LIBRARY_DIRS}
)

target_compile_options(${PROJECT_NAME} PUBLIC
    ${SDL2_CFLAGS_OTHER}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${SDL2_LIBRARIES}
)

# Optional: rename executable to "final"
set_target_properties(${PROJECT_NAME}
    PROPERTIES OUTPUT_NAME "final"
)

