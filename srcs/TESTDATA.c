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
	int				parent_sector;
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
	// Big square sector
    {
		{(t_vector2){-16.0, -16.0}, (t_vector2){-16.0, 16.0}, (t_vector2){16.0, 16.0}, (t_vector2){16.0, -16.0}},
		{-1, -1, -1, -1},
		{MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK},
		//{1, 2, 3, -1},
		{1},
		-1,
		4,
		0.0,
		40.0,
		MINECRAFT_DIRT_PODZOL_TOP,
		MINECRAFT_REDSTONE_LAMP,
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
	},
	// Small 1x1x4 rectangle, in front of player
	{
		{(t_vector2){-1.0, 2.0}, (t_vector2){-1.0, 3.0}, (t_vector2){1.0, 3.0}, (t_vector2){1.0, 2.0}},
		{-1, -1, -1, -1},
		{MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK},
		{-1},
		0,
		4,
		0.0,
		1.0,
		MINECRAFT_DIRT_PODZOL_TOP,
		MINECRAFT_REDSTONE_LAMP,
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
	},
	// Thin box, partially occluding previous one (wall 3 should get ordered before wall 3 of previous one)
	{
		{(t_vector2){-0.5, 1.5}, (t_vector2){-0.5, 2.0}, (t_vector2){0.5, 2.0}, (t_vector2){0.5, 1.5}},
		{-1, -1, -1, -1},
		{MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK},
		{-1},
		0,
		4,
		0.0,
		1.0,
		MINECRAFT_DIRT_PODZOL_TOP,
		MINECRAFT_REDSTONE_LAMP,
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
	},
	// Small box, partially occluding previous ones (wall 0 and 3 should get ordered to be before previous walls)
	{
		{(t_vector2){0.25, 1.25}, (t_vector2){0.25, 1.4}, (t_vector2){0.5, 1.4}, (t_vector2){0.5, 1.25}},
		{-1, -1, -1, -1},
		{MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK, MINECRAFT_NETHER_BRICK},
		{-1},
		0,
		4,
		0.0,
		1.0,
		MINECRAFT_DIRT_PODZOL_TOP,
		MINECRAFT_REDSTONE_LAMP,
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
		(t_vector3){0.0, 0.0, 0.0},
		(t_vector2){0.0, 0.0},
	},
};

int test_sector_count = 2;