#include "doomnukem.h"

/**
 * TESTDATA
*/
t_poly test_polygons[] = {
    // Bix box (outer walls)
    {{(t_vector2){-16.f, -16.f}, (t_vector2){-16.f, 16.f}, (t_vector2){16.f, 16.f}, (t_vector2){16.f, -16.f}}, 4, 0.f, 10.f, MINECRAFT_NETHER_BRICK},

    // Simple 1x1 boxes
    {{(t_vector2){-16.f, -16.f}, (t_vector2){-16.f, -15.f}, (t_vector2){-15.f, -15.f}, (t_vector2){-15.f, -16.f}}, 4, 0.f, 1.f, MINECRAFT_TNT},
    {{(t_vector2){-14.f, -16.f}, (t_vector2){-14.f, -15.f}, (t_vector2){-13.f, -15.f}, (t_vector2){-13.f, -16.f}}, 4, 0.f, 1.f, MINECRAFT_TNT},

    // Simple 3x3 box
    {{(t_vector2){-1.f, -1.f}, (t_vector2){-4.f, -1.f}, (t_vector2){-4.f, -4.f}, (t_vector2){-1.f, -4.f}}, 4, 0.f, 1.f, MINECRAFT_REDSTONE_LAMP},

    // Triangle
    {{(t_vector2){10.f, 10.f}, (t_vector2){10.f, 15.f}, (t_vector2){15.f, 15.f}}, 3, 0.f, 1.f, MINECRAFT_GRASS_SIDE},

    // Hexa
    {{(t_vector2){5.89, 5.9}, (t_vector2){7.15, 5.54}, (t_vector2){7.79, 4.39}, (t_vector2){7.42, 3.12}, (t_vector2){6.27, 2.49}, (t_vector2){5.01, 2.85}, (t_vector2){4.37, 4.01}, (t_vector2){4.74, 5.27}}, 8, 0.f, 1.f, MINECRAFT_GRASS_SIDE},

    // Tall 1x1 polygon
    {{(t_vector2){-6.f, 0.f}, (t_vector2){-6.f, -1.f}, (t_vector2){-7.f, -1.f}, (t_vector2){-7.f, 0.f}}, 4, 0.f, 100.f, MINECRAFT_LOG_BIRCH},

    // Variable height blocks
    {{(t_vector2){1.f, 1.f}, (t_vector2){1.f, 2.f}, (t_vector2){2.f, 2.f}, (t_vector2){2.f, 1.f}}, 4, 0.f, 0.25, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){2.f, 1.f}, (t_vector2){2.f, 2.f}, (t_vector2){3.f, 2.f}, (t_vector2){3.f, 1.f}}, 4, 0.f, 0.5, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){3.f, 1.f}, (t_vector2){3.f, 2.f}, (t_vector2){4.f, 2.f}, (t_vector2){4.f, 1.f}}, 4, 0.f, 0.75, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){4.f, 1.f}, (t_vector2){4.f, 2.f}, (t_vector2){5.f, 2.f}, (t_vector2){5.f, 1.f}}, 4, 0.f, 1.f, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){5.f, 1.f}, (t_vector2){5.f, 2.f}, (t_vector2){6.f, 2.f}, (t_vector2){6.f, 1.f}}, 4, 0.f, 1.25, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){6.f, 1.f}, (t_vector2){6.f, 2.f}, (t_vector2){7.f, 2.f}, (t_vector2){7.f, 1.f}}, 4, 0.f, 1.5, MINECRAFT_PLANK_ACACIA},
};

int test_polygon_count = 13;