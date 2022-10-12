/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:40:49 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/12 23:29:00 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_H
# define DOOMNUKEM_H
# define WIN_NAME "Doom Nukem"
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
# define COLLISION_OFFSET 0.25f
# define DIRECTION_START_X 0.f
# define DIRECTION_START_Y 1.f
# define POSITION_START_X 0.f
# define POSITION_START_Y 0.f
# define FOV 66
# define DEG_IN_RADIAN 0.01745f
# define RADIAN_IN_DEG 57.29578f
# define ROTATION_SPEED 1.8f
# define MOVEMENT_SPEED 3.2f
# define MAX_RAY_DISTANCE 25.f
# define TEX_SIZE 64
# define MOUSE_SENSITIVITY 20.f
//# define TEXTURE_PANELS "./assets/texture_spritesheet.xpm"
# define TEXTURE_PANELS "./assets/minecraft_spritesheet.xpm"
# define TEXTURE_BACKGROUND "./assets/bg.xpm"
# define FONT_FILE "./assets/SpaceMono-Regular.ttf"
# define MAX_POLYGON_CORNERS 8
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 8
# define MAX_VISIBLE_SECTORS 64
# define MAX_VISIBLE_WALLS 256
# define MAX_VIEW_DISTANCE 100.f
# define MAX_VERTEX_LENGTH 1048576.f
# define EDITOR_BG_COLOR 0x000000
# define EDITOR_GRID_COLOR 0x424242
# define EDITOR_MENU_COLOR 0xD3D3D3
# define EDITOR_MENU_W 280
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
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
 * Movement direction enumeration.
 */
typedef enum e_movement {
	FORWARD = 0,
	BACKWARD = 1,
	LEFT = 2,
	RIGHT = 3
}	t_movement;

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
 * Matrix that contains 2 t_point columns.
 */
typedef	struct s_point_matrix
{
	t_point			a;
	t_point			b;
}	t_point_matrix;

/**
 * Polygons GOING TO BE REMOVED SOON
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
	t_vector2		corners[MAX_POLYGON_CORNERS];
	int				corner_count;
	double			bottom;
	double			top;
	int				texture;
	t_polygon_hit	*hits;
}	t_polygon;

/**
 * Sectors
 */
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

/**
 * Rayhit struct.
*/
typedef struct s_rayhit
{
	t_sector	*sector;
	int			texture;
	t_vector2	position;
	double		distance;
	t_vector2	texture_offset;
	t_vector2	texture_step;
	int			height;
	int			wall_start;
	int			wall_end;
}	t_rayhit;


/**
 * Wall struct. Contains information of what sector it belongs to and which wall
 * of that sector it is.
 */
typedef struct s_wall
{
	int				sector_id;
	int				wall_id;
	t_bool			is_member;
}	t_wall;

/**
 * Struct for configuration variables of the application.
 */
typedef struct s_conf
{
	int				toggle_help;
	int				toggle_editor;
	int				fps;
	struct timespec	fps_clock;
	char			fps_info[20];
	double			delta_time;
	double			skybox_offset;
	int				fov;
	int				keystates;
	int				mouse_active;
	double			movement_speed;
	double			rotation_speed;
}	t_conf;

/**
 * Struct for threads about their specific drawing areas.
 */
typedef struct s_thread_data
{
	void			*app;
	int				id;
}	t_thread_data;

/**
 * Struct for player. Contains players position, direction and camera plane.
 */
typedef struct s_player
{
	t_vector2		pos;
	t_vector2		dir;
	t_vector2		cam;
	double			camera_length;
	double			height;
	int				current_sector;
}	t_player;

/**
 * Struct for editor.
 */

typedef struct s_editor
{
	int				zoom;
}	t_editor;

/**
 * Struct for font.
 */
typedef struct s_font
{
	SDL_Surface *font;
	int         size;
}	t_font;

/**
 * Struct for the application.
 */
typedef struct s_app
{
	t_conf			*conf;
	SDL_Window		*win;
	SDL_Surface		*surface;
	t_font			font;
	double			depthmap[WIN_H][WIN_W];
	int				occlusion_top[WIN_W];
	int				occlusion_bottom[WIN_W];
	t_wall			possible_visible[MAX_VISIBLE_WALLS];
	int				possible_visible_count;
	t_thread_data	thread_info[THREAD_COUNT];
	t_player		player;
	t_editor		editor;
	SDL_Surface		*sprite;
	SDL_Surface		*bg;
}	t_app;

/**
 * Messages
 */
void		exit_error(char *message);

/**
 * Configuration
 */
int			conf_init(t_app *app);
void		init_thread_info(t_app *app);
void		init_camera_plane(t_app *app);
void		update_info(t_app *app);

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
void		put_pixel_to_surface_depth(t_app *app, t_point point, int color,
				double distance);
void		put_pixel_to_surface_check(t_app *app, t_point point, int color,
				double distance);
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
void		handle_movement(t_app *app);

/**
 * Graphics
 */
void		*render_skybox(void *data);
void		*render_background(void *data);
void		render_multithreading(t_app *app, void *(*renderer)(void *));

/**
 * Player
 */
void		player_rotate(t_app *app, double angle);
void		player_move(t_app *app, t_movement movement, double speed);

/**
 * Polygons
*/
void		*render_polygons(void *data);
void		polygon_draw_floors(t_app *app, t_polygon *polygon);

/**
 * Helper functions
 */
double		get_radial_direction(t_vector2 *vector);
void		clamp_distance(double *distance);
int			get_pixel_color(SDL_Surface *surface, int x, int y);
double		distortion_correction(double angle, double distance);

/**
 * Sectors
 */
void			render_sectors(t_app *app);
void			sector_walls_possible_visible(t_app *app);
t_vertex2		get_sector_vertex_by_corner(t_app *app, int sector_id,
					int wall_id);
int				translate_window_x(t_app *app, t_vector2 coord);
void			sector_wall_draw(t_app *app, int sector_id, int wall_id);

/**
 * Editor
 */
void		open_map_editor(t_app *app);

/**
 * Font
 */
void        load_font(t_app *app);
void		color_font(t_app *app, int color);
void    	render_text(t_app *app, t_point position, char *text);

#endif

/**
 * TESTDATA globals
*/
extern t_polygon test_polygons[];
extern int test_polygon_count;

extern t_sector test_sectors[];