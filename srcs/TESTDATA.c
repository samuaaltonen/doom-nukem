#include "doomnukem.h"

/**
 * TESTDATA
 * 
typedef struct s_sector
{
	t_vector2		corners[MAX_SECTOR_CORNERS];
	int				wall_types[MAX_SECTOR_CORNERS];
	int				wall_textures[MAX_SECTOR_CORNERS];
	int				member_sectors[MAX_MEMBER_SECTORS];
	int				corner_count;
	double			floor_height;
	double			ceiling_height;
	int				floor_texture;
	int				ceiling_texture;
	t_vector3		floor_slope_position;
	t_vector2		floor_slope_angles;
	t_vector3		ceiling_slope_position;
	t_vector2		ceiling_slope_angles;
}	t_sector;
*/
t_sector test_sectors[] = {
    {
		{(t_vector2){-16.0, -16.0}, (t_vector2){-16.0, 16.0}, (t_vector2){16.0, 16.0}, (t_vector2){16.0, -16.0}},
		{-1, -1, -1, -1},
		{MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK},
		{},
		4,
		0.0,
		4.0,
		MINECRAFT_DIRT_PODZOL_TOP,
		MINECRAFT_REDSTONE_LAMP,
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
	},

};

int test_sector_count = 1;