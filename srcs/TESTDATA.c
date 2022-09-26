#include "doomnukem.h"

/**
 * TESTDATA
*/
t_poly test_polygons[] = {
    // Bix box (outer walls)
    {{(t_vector2){-16.f, -16.f}, (t_vector2){-16.f, 16.f}, (t_vector2){16.f, 16.f}, (t_vector2){16.f, -16.f}}, 4, 0.f, 1.f, WALL_STONE_BRICK},

    // Simple 3x3 box
    {{(t_vector2){-1.f, -1.f}, (t_vector2){-4.f, -1.f}, (t_vector2){-4.f, -4.f}, (t_vector2){-1.f, -4.f}}, 4, 0.f, 1.f, WALL_FACE},

    // Triangle
    {{(t_vector2){10.f, 10.f}, (t_vector2){10.f, 15.f}, (t_vector2){15.f, 15.f}}, 3, 0.f, 1.f, WALL_ENGRAVED},

    // Hexa
    {{(t_vector2){5.89, 5.9}, (t_vector2){7.15, 5.54}, (t_vector2){7.79, 4.39}, (t_vector2){7.42, 3.12}, (t_vector2){6.27, 2.49}, (t_vector2){5.01, 2.85}, (t_vector2){4.37, 4.01}, (t_vector2){4.74, 5.27}}, 8, 0.f, 1.f, WALL_STONE_BRICK},
};

int test_polygon_count = 4;