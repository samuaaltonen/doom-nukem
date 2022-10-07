/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:40:49 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/05 13:14:03 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_EDITOR_H
# define DOOMNUKEM_EDITOR_H
# define WIN_NAME "Doom Nukem Editor"
# define WIN_W 1280
# define WIN_H 720
# define MSG_ERROR "Error occured"
# define MSG_ERROR_WINDOW "Could not open a window."
# define MSG_ERROR_WINDOW_SURFACE "Could not get window surface."
# define MSG_ERROR_SDL_INIT "Could not initialize SDL."
# define MSG_ERROR_ALLOC "Could not allocate memory."
# define MSG_ERROR_IMAGE_INIT "Image initialization failed."
# define MSG_ERROR_THREADS "Could not create a thread."
# define MSG_ERROR_THREADS_JOIN "Could not join threads."
# define MSG_ERROR_TEXTURE_FILE_ACCESS "Could not open/close a texture file."
# define MSG_ERROR_TEXTURE_LOAD_FAILED "Texture files are invalid."
# define MSG_ERROR_FONT "Could not open font file."
# define MSG_ERROR_MOUSE "Could not set mouse cursor relative to the window."
# define THREAD_COUNT 2
# define IMAGE_PIXEL_BYTES 4
# define IMAGE_PIXEL_BITS 32
# define DEG_IN_RADIAN 0.01745f
# define RADIAN_IN_DEG 57.29578f
# define MAP_SPEED 0.25f
# define TEXTURE_PANELS "../assets/minecraft_spritesheet.xpm"
# define FONT_FILE "../assets/SpaceMono-Regular.ttf"
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 16
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include "libft.h"
# include "liblinearalgebra.h"

/**
 * Integer type definitions
 */
typedef unsigned char	t_uint8;

/**
 * Texture type enumeration.
*/
/* enum e_texture {
	FLOOR_STONE			= 0,
	FLOOR_LAMINATE		= 1,
	FLOOR_STONE_BRICK	= 2,
	FLOOR_GRAVEL		= 3,
	WALL_STONE_BRICK	= 15,
	WALL_FACE			= 16,
	WALL_ENGRAVED		= 17,
	WALL_DOOR			= 18
}; */
enum e_texture {
	MINECRAFT_CONCRETE_BLACK	= 0,
	MINECRAFT_CONCRETE_MAGENTA	= 1,
	MINECRAFT_DIRT_PODZOL_SIDE	= 2,
	MINECRAFT_DIRT_PODZOL_TOP	= 3,
	MINECRAFT_END_BRICKS		= 4,
	MINECRAFT_ENDSTONE			= 5,
	MINECRAFT_GRASS_SIDE		= 6,
	MINECRAFT_SNOW_SIDE			= 7,
	MINECRAFT_LOG_OAK			= 8,
	MINECRAFT_LOG_BIRCH			= 9,
	MINECRAFT_NETHER_BRICK		= 10,
	MINECRAFT_OBSIDIAN			= 11,
	MINECRAFT_PLANK_ACACIA		= 12,
	MINECRAFT_PLANKS_OAK		= 13,
	MINECRAFT_PLANKS_BIRCH		= 14,
	MINECRAFT_NETHER_BRICK_RED	= 15,
	MINECRAFT_REDSTONE_LAMP		= 16,
	MINECRAFT_TNT				= 17
};

/**
 * Keystate enumeration.
 * Keystate enumerations use powers of 2 for bit stacking operations.
 */
enum e_keystate {
	FORWARD_DOWN = 1,
	FORWARD_W_DOWN = 2,
	BACKWARD_DOWN = 4,
	BACKWARD_S_DOWN = 8,
	LEFT_DOWN = 16,
	RIGHT_DOWN = 32,
	ROTATE_LEFT_DOWN = 64,
	ROTATE_RIGHT_DOWN = 128
};

/**
 * Struct for integer coordinate point.
 */
typedef struct s_point
{
	int				x;
	int				y;
}	t_point;

/**
 * Polygons
*/
typedef struct s_polygon_hit
{
	int		y_first_top;
	int		y_second_top;
	int		y_first_bottom;
	int		y_second_bottom;
	double	distance_first;
	double	distance_second;
}	t_polygon_hit;

typedef struct s_polygon
{
	t_vector2		corners[MAX_SECTOR_CORNERS];
	int				corner_count;
	double			bottom;
	double			top;
	int				texture;
	t_polygon_hit	*hits;
}	t_polygon;

/**
 * Struct for the application.
 */
typedef struct s_app
{
	int				keystates;
	int				toggle_help;
	SDL_Window		*win;
	SDL_Surface		*surface;
	TTF_Font		*font;
	SDL_Surface		*sprite;
	t_vector2		view_pos;
	t_vector2		zoom_area;
}	t_app;

/**
 * Messages
 */
void		exit_error(char *message);

/**
 * Configuration
 */
int			conf_init(t_app *app);

/**
 * Application
 */
int			app_init(t_app **app);
void		app_prepare(t_app *app);
void		app_render(t_app *app);
void		app_loop(t_app *app);

/**
 * Images
 */
SDL_Surface	*init_image(int x, int y);
SDL_Surface	*init_xpm_image(char *path);
void		put_pixel_to_surface(SDL_Surface *surface, int x, int y, int color);
void		flush_surface(SDL_Surface *surface);

/**
 * Events
 */
int			events_keyup(int keycode, t_app *app);
int			events_keydown(int keycode, t_app *app);
int			events_mouse_track(t_app *app);
int			events_window_destroy(void);
int			events_window_other(int windowevent, t_app *app);
int			dispatch_event(t_app *app, SDL_Event *event);

/**
 * Graphics
 */
void		*render_background(void *data);

/**
 * Polygons
*/
void		*render_polygons(void *data);
void		polygon_draw_floors(t_app *app, t_polygon *polygon);

/**
 * Helper functions
 */
int			get_pixel_color(SDL_Surface *surface, int x, int y);



/**
 * Sectors
 */
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

/**
 * Map Editor functions
 * 
 */

typedef struct s_vec2list
{
	t_vector2 point;
	struct s_vec2list *next;
} t_vec2list;

t_bool complete_sector(t_app *app);
t_bool valid_point(t_app *app);
t_vector2 *nearest_point_cursor(t_app *app);
int	del_sector_list(t_app *app, t_vec2list *list);
void add_vector_list(t_app *app, t_vec2list *list);
t_vec2list *new_vector_list(t_app *app);
void	handle_movement(t_app *app);
void render_grid(t_app *app);


#endif

/**
 * TESTDATA globals
*/
extern t_polygon test_polygons[];
extern int test_polygon_count;

extern t_sector test_sectors[];
extern int test_sectors_count;