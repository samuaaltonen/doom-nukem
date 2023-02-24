cmake_minimum_required(VERSION 3.7.2)

project(doom-nukem C)

set(CMAKE_C_STANDARD 11)

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/sdl/SDL2-2.0.8/build")
find_package(SDL2 REQUIRED CONFIG)

set(LIBFT_DIR "${CMAKE_SOURCE_DIR}/libft")
set(LIBMATH_DIR "${CMAKE_SOURCE_DIR}/liblinearalgebra")
# Add the include directories
include_directories(${CMAKE_SOURCE_DIR}/includes
    ${SDL2_INCLUDE_DIRS}
    ${LIBFT_DIR}/includes
    ${LIBMATH_DIR}/includes)

# Add the source files
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/srcs/*.c")

# Find the SDL2 libraries

set(EXECUTABLE_NAME doom-nukem)
# Link against the SDL2 libraries
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(
    ${EXECUTABLE_NAME}
    ${SDL2_LIBRARIES}
    ${LIBFT_DIR}/libft.a
    ${LIBMATH_DIR}/liblinearalgebra.a)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build_cmake)

# Generate the build files
# add_subdirectory(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

# Add a custom target to build the project and install it
#add_custom_target(build_and_install
#    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
#    DEPENDS my_project
#)