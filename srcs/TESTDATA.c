#include "doomnukem.h"

/**
 * TESTDATA
*/
t_poly test_polygons[] = {
    // Bix box (outer walls)
    {{(t_vector2){-16.f, -16.f}, (t_vector2){-16.f, 16.f}, (t_vector2){16.f, 16.f}, (t_vector2){16.f, -16.f}}, 4, 0.f, 1.f, WALL_STONE_BRICK},

    // Simple 1x1 box
    {{(t_vector2){1.f, 1.f}, (t_vector2){4.f, 1.f}, (t_vector2){4.f, 4.f}, (t_vector2){1.f, 4.f}}, 4, 0.f, 1.f, WALL_FACE},

    // Triangle
    {{(t_vector2){10.f, 10.f}, (t_vector2){10.f, 15.f}, (t_vector2){15.f, 15.f}}, 3, 0.f, 1.f, WALL_ENGRAVED},
};

int test_polygon_count = 4;