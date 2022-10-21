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
# define MAX_TEX_COUNT 128
# define DEG_IN_RADIAN 0.01745f
# define PI_HALF 1.57079632679
# define RADIAN_IN_DEG 57.29578f
# define MAP_SPEED 0.25f
# define HEIGHT_INC 0.125f
# define TEXTURE_PANELS "../assets/minecraft_spritesheet.xpm"
# define FONT_FILE "../assets/SpaceMono-Regular.ttf"
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 8
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
	FORWARD_DOWN = 0b1,
	FORWARD_W_DOWN = 0b10,
	BACKWARD_DOWN = 0b100,
	BACKWARD_S_DOWN = 0b1000,
	LEFT_DOWN = 0b10000,
	RIGHT_DOWN = 0b100000,
	ROTATE_LEFT_DOWN = 0b1000000,
	ROTATE_RIGHT_DOWN = 0b10000000,
	C_BUTTON = 0b100000000,
	V_BUTTON = 0b1000000000
};

enum e_colors {
	PORTAL = 0xFF0000,
	WALL = 0x999999,
	CEILING_ROTATE = 0x888888,
	FLOOR_ROTATE = 0x777777
};

/**
 * Struct for integer coordinate point.
 */
typedef struct s_point
{
	int				x;
	int				y;
}	t_point;

typedef struct	s_vec2list
{
	t_vector2			point;
	int					wall_type;
	int					wall_texture;
	struct s_vec2list	*next;
} t_vec2list;

/**
 * 
 * 
 */
typedef struct	s_sectorlist
{
	int					corner_count;
	t_vec2list			*wall_list;
	struct s_sectorlist	*member_sectors[MAX_MEMBER_SECTORS];
	int					member_links[MAX_MEMBER_SECTORS];
	struct s_sectorlist	*parent_sector;
	int					light;
	double				floor_height;
	double				ceil_height;
	int					floor_tex;
	int					floor_tex_offset;
	int					ceil_tex;
	int					ceil_tex_offset;
	t_vec2list			*floor_slope_wall;
	t_vec2list			*floor_slope_opposite;
	double				floor_slope_height;
	t_vec2list			*ceil_slope_wall;
	t_vec2list			*ceil_slope_opposite;
	double				ceil_slope_height;
	struct s_sectorlist	*next;
} t_sector_lst;

/**
 * Struct for the application.
 */
typedef struct s_app
{
	int					keystates;
	int					toggle_help;
	int					zoom_range;
	SDL_Window			*win;
	SDL_Surface			*surface;
	TTF_Font			*font;
	SDL_Surface			*sprite;
	double				divider;
	t_vector2			view_pos;
	t_vector2			view_size;
	t_vector2			zoom_area;
	t_vector2			mouse_click;
	t_sector_lst		*sectors;
	t_sector_lst		*active_sector;
	t_vec2list			*active;
	t_vec2list			*active_last;
	t_bool				list_creation;
	t_bool				list_ongoing;
	t_bool				portal_selection;
	t_bool				ceiling_edit;
	t_bool				floor_edit;
	t_bool				light_edit;
	int					sectorcount;
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
 * Helper functions
 */
int			get_pixel_color(SDL_Surface *surface, int x, int y);

typedef struct s_exportsector
{
	int				corner_count;
	t_vector2		corners[MAX_SECTOR_CORNERS];
	int				wall_types[MAX_SECTOR_CORNERS];
	int				wall_textures[MAX_SECTOR_CORNERS];
	int				member_sectors[MAX_MEMBER_SECTORS];
	int				parent_sector;
	int				light;
	double			floor_height;
	double			ceil_height;
	int				floor_tex;
	int				floor_tex_offset;
	int				ceil_tex;
	int				ceil_tex_offset;
	double			floor_slope_height;
	int				floor_slope_position;
	int				floor_slope_opposite;
	double			ceil_slope_height;
	int				ceil_slope_position;
	int				ceil_slope_opposite;
}	t_exportsector;

/**
 * Map Editor functions
 * 
 */
typedef struct	s_line
{
	t_point	dif;
	t_point	pos;
	int		d;
	int		err;
}	t_line;

t_bool			complete_sector(t_app *app);
t_bool			valid_point(t_app *app);
t_vector2		*nearest_point_cursor(t_app *app);
int				del_vector_list(t_vec2list **list);
int				put_to_vector_list(t_vec2list **list, t_vec2list *new);
t_vec2list		*new_vector_list(t_vector2 *point);
void			handle_movement(t_app *app);
void			render_grid(t_app *app, double divider, int color);
void			draw_list_lines(t_app *app, t_vec2list *a, t_vec2list *b, int color);
void			render_sectors(t_app *app);
void			render_sector(t_app *app, t_vec2list *sector_start);
void			draw_line(t_app *app, t_vector2 *a, t_vector2 *b, int color);
void			zoom_slider(t_app *app);
void			snap_to_nearest(t_app *app, t_point *mouse_pos, t_vector2 *snap_pos, double divider);
t_sector_lst	*put_sector_lst(t_app *app, t_sector_lst* new);
t_sector_lst	*new_sector_list(t_vec2list *wall_list);
int				file_open(t_app *app, char *path);
int				import_file(t_app *app, char *path);
void			change_walls_tex(t_vec2list *walls, int wall_tex);
int				inside_sector_check(t_app *app, t_sector_lst *sector);
t_sector_lst	*click_sector(t_app *app);
t_sector_lst	*find_parent_sector(t_app *app, t_sector_lst *sector);
void			change_selected_wall_tex(t_app *app, t_vec2list *wall, int wall_id);
t_sector_lst	*sector_pop(t_app *app, t_sector_lst **pop, void (*del)(void *, size_t));
void			sector_delone(t_sector_lst **sector, void (*del)(void*, size_t));
int				get_sector_id(t_app *app, t_sector_lst *sector);
void			relink_member_sectors(t_app *app);
void			link_wall_to_sector(t_app *app);
void			render_fill_active_sector(t_app *app);
void			sector_edit(t_app *app, SDL_Keycode key);
void			render_selection_point(t_app *app, t_vec2list *point, int size);
t_vec2list		*find_opposite_point(t_sector_lst *sector, t_vec2list *point);
void			render_sector_points(t_app *app);
void			change_walls_type(t_app *app, t_sector_lst *sector);

#endif