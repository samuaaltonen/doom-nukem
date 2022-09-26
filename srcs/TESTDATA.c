#include "doomnukem.h"

/**
 * TESTDATA
*/
t_poly test_polygons[] = {
    // Bix box (outer walls)
    {{(t_vector2){-16.0, -16.0}, (t_vector2){-16.0, 16.0}, (t_vector2){16.0, 16.0}, (t_vector2){16.0, -16.0}}, 4, 0.0, 10.0, MINECRAFT_NETHER_BRICK},

    // Simple 1x1 boxes
    {{(t_vector2){-16.0, -16.0}, (t_vector2){-16.0, -15.0}, (t_vector2){-15.0, -15.0}, (t_vector2){-15.0, -16.0}}, 4, 0.0, 1.0, MINECRAFT_TNT},
    {{(t_vector2){-14.0, -16.0}, (t_vector2){-14.0, -15.0}, (t_vector2){-13.0, -15.0}, (t_vector2){-13.0, -16.0}}, 4, 0.0, 1.0, MINECRAFT_TNT},

    // Simple 3x3 box
    {{(t_vector2){-1.0, -1.0}, (t_vector2){-4.0, -1.0}, (t_vector2){-4.0, -4.0}, (t_vector2){-1.0, -4.0}}, 4, 0.0, 1.0, MINECRAFT_REDSTONE_LAMP},

    // Triangle
    {{(t_vector2){10.0, 10.0}, (t_vector2){10.0, 15.0}, (t_vector2){15.0, 15.0}}, 3, 0.0, 1.0, MINECRAFT_GRASS_SIDE},

    // Hexa
    {{(t_vector2){5.89, 5.9}, (t_vector2){7.15, 5.54}, (t_vector2){7.79, 4.39}, (t_vector2){7.42, 3.12}, (t_vector2){6.27, 2.49}, (t_vector2){5.01, 2.85}, (t_vector2){4.37, 4.01}, (t_vector2){4.74, 5.27}}, 8, 0.0, 1.0, MINECRAFT_GRASS_SIDE},

    // Tall 1x1 polygon
    {{(t_vector2){-6.0, 0.0}, (t_vector2){-6.0, -1.0}, (t_vector2){-7.0, -1.0}, (t_vector2){-7.0, 0.0}}, 4, 0.0, 100.0, MINECRAFT_LOG_BIRCH},

    // Variable height blocks
    {{(t_vector2){1.0, 1.0}, (t_vector2){1.0, 2.0}, (t_vector2){2.0, 2.0}, (t_vector2){2.0, 1.0}}, 4, 0.0, 0.25, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){2.0, 1.0}, (t_vector2){2.0, 2.0}, (t_vector2){3.0, 2.0}, (t_vector2){3.0, 1.0}}, 4, 0.0, 0.5, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){3.0, 1.0}, (t_vector2){3.0, 2.0}, (t_vector2){4.0, 2.0}, (t_vector2){4.0, 1.0}}, 4, 0.0, 0.75, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){4.0, 1.0}, (t_vector2){4.0, 2.0}, (t_vector2){5.0, 2.0}, (t_vector2){5.0, 1.0}}, 4, 0.0, 1.0, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){5.0, 1.0}, (t_vector2){5.0, 2.0}, (t_vector2){6.0, 2.0}, (t_vector2){6.0, 1.0}}, 4, 0.0, 1.25, MINECRAFT_PLANK_ACACIA},
    {{(t_vector2){6.0, 1.0}, (t_vector2){6.0, 2.0}, (t_vector2){7.0, 2.0}, (t_vector2){7.0, 1.0}}, 4, 0.0, 1.5, MINECRAFT_PLANK_ACACIA},

    // Small triangle
    {{(t_vector2){1.0, 3.5}, (t_vector2){1.0, 4.0}, (t_vector2){1.5, 4.0}}, 3, 0.0, 0.25, MINECRAFT_NETHER_BRICK_RED},
    
};

int test_polygon_count = 14;