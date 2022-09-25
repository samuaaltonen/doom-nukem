#include "doomnukem.h"

/**
 * TESTDATA
*/
t_poly test_polygons[] = {
    // Simple 1x1 box
    {{(t_vector2){1.f, 1.f}, (t_vector2){2.f, 1.f}, (t_vector2){2.f, 2.f}, (t_vector2){1.f, 2.f}}, 4, 0.f, 1.f},

    // Triangle
    {{(t_vector2){10.f, 10.f}, (t_vector2){10.f, 15.f}, (t_vector2){15.f, 15.f}}, 3, 0.f, 1.f},
};

int test_polygon_count = 2;