/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem_editor.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:40:49 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/18 16:46:47 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_EDITOR_H
# define DOOMNUKEM_EDITOR_H
# define WIN_NAME "Doom Nukem Editor"
# define WIN_W 1280
# define WIN_H 720
# define HELP_MENU_W 280
# define ICON_SIZE 64
# define OBJECT_SCREEN_SIZE 16
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
# define MSG_ERROR_FILE_READ "Could not read from a file."
# define MSG_ERROR_FILE_WRITE "Could not write to a file."
# define THREAD_COUNT 2
# define IMAGE_PIXEL_BYTES 4
# define IMAGE_PIXEL_BITS 32
# define MAX_TEX_COUNT 128
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 8
# define MAX_WEAPONS 5
# define MAX_ARMOR 5
# define INVENTORY_SIZE 6
# define MAX_OBJECTS 64
# define MAX_UNIQUE_OBJECTS 64
# define MAX_INTERACTIONS 64
# define DEG_IN_RADIAN 0.01745f
# define PI_HALF 1.57079632679
# define RADIAN_IN_DEG 57.29578f
# define MAP_SPEED 0.85f
# define HEIGHT_INC 0.125f
# define PANELS_PATH "../assets/textures/minecraft_spritesheet.bmp"
# define UI_FRAME_PATH "../assets/ui/ui_frame.bmp"
# define FONT_FILE "../assets/legacy/SpaceMono-Regular.ttf"
# define FONT_TX "../assets/fonts/sci-fi_font.bmp"
# define FILE_PATH "./test.test"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <stdlib.h>
# include <SDL.h>
# include "libft.h"
# include "liblinearalgebra.h"

/**
 * Integer type definitions
 */
typedef unsigned char	t_uint8;

/**
 * Texture type enumeration.
*/
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
	FLOOR_ROTATE = 0x777777,
	BG_LIGHT = 0x888888,
	BG_DARK = 0x424242,
	TEXT = 0xFF111111,
	ACTIVE_TEXT = 0xFFFF0000,
	PLAYER = 0x00FF00,
	LINE_A = 0xAABBCC,
	LINE_B = 0xFF4444,
	UI_FRAME = 0xFF00FFFF,
	POINT = 0xFF00FF
};

/**
 * Struct for integer coordinate point.
 */
typedef struct s_point
{
	int				x;
	int				y;
}	t_point;

typedef struct s_vec2_lst
{
	t_vector2			point;
	int					type;
	int					tex;
	struct s_vec2_lst	*next;
}	t_vec2_lst;

typedef struct s_draw_line
{
	t_point	dif;
	t_point	pos;
	int		d;
	int		err;
}	t_draw_line;

typedef struct s_weapon
{
	int		damage;
	int		range;
	int		fire_rate;
	int		magazine;
}	t_weapon;

typedef struct s_armor
{
	int		offence;
	int		defence;
}	t_armor;

typedef struct s_inventory
{
	int		ammo;
	int		potion;
	int		antidote;
	int		key;
	int		jetpack;
	int		selected[INVENTORY_SIZE];
}	t_inventory;

typedef struct s_sectorlist
{
	int					corner_count;
	t_vec2_lst			*wall_list;
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
	t_vec2_lst			*floor_slope_wall;
	t_vec2_lst			*floor_slope_opposite;
	double				floor_slope_height;
	t_vec2_lst			*ceil_slope_wall;
	t_vec2_lst			*ceil_slope_opposite;
	double				ceil_slope_height;
	struct s_sectorlist	*next;
}	t_sector_lst;

typedef struct s_player
{
	t_vector2		position;
	t_vector2		direction;
	t_sector_lst	*sector;
	int				health;
	int				selected_weapon;
	int				selected_armor;
	t_weapon		weapons[MAX_WEAPONS];
	t_armor			armor[MAX_ARMOR];
	t_inventory		inventory;
}	t_player;

/**
 * @brief array of objects per entire level
 * 
 */
typedef struct s_object
{
	int				type;
	int				var;
	t_vector2		position;
	t_sector_lst	*sector;
}	t_object;

/**
 * @brief Array of interactions for entire level
 * 		if event_id is 1-4, use target_sector & variable for height/light
 * 		if event_id is 5, use variable as the line which to read from text file
 * 		if event_id is 6, use variable as the sound id(cast to int)
 * 1 activate floor height
 * 2 activate ceil height
 * 3 activate ceil&floor height
 * 4 set light level
 * 5 open text pop-up
 * 6 activate sound
 * 7 activate end level
 * 0 no events, array delimited by 0
 * 
 * if activation_sector is NULL/-1, activator will be the activator_id in the object array
 * if activation_sector is set & activation_id is -1, the sector itself is the activator
 * if active_sector is set & activation_id is set, the activator is the decor on the wall_id declared by activation_id in active sector
 * if the activator is in the object array & the type of the object is an enemy, it only triggers when the enemy dies
 * target_sector & target_id will be the same in saves
 */
typedef struct s_interaction
{
	int				event_id;
	double 			variable;
	t_sector_lst	*activation_sector;
	int				activation_id;
	t_sector_lst	*target_sector;
}	t_interaction;

/**
 * Struct for font.
 */
typedef struct s_font
{
	SDL_Surface	*font;
	int			size;
}	t_font;

/**
 * Struct for all assets.
 */
typedef struct s_assets
{
	t_font			font;
	SDL_Surface		*ui_frame;
	SDL_Surface		*button_texture;
	SDL_Surface		*title_screen_image;
	SDL_Surface		*sprite;
	SDL_Surface		*bg;
}	t_assets;

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
	SDL_Surface			*sprite;
	double				divider;
	t_vector2			view_pos;
	t_vector2			view_size;
	t_vector2			zoom_area;
	t_vector2			mouse_click;
	t_vector2			mouse_track;
	t_sector_lst		*sectors;
	t_sector_lst		*active_sector;
	t_vec2_lst			*active;
	t_vec2_lst			*active_last;
	t_bool				list_creation;
	t_bool				list_ongoing;
	t_bool				portal_selection;
	t_bool				wall_edit;
	t_bool				ceiling_edit;
	t_bool				floor_edit;
	t_bool				light_edit;
	t_bool				slope_edit;
	t_bool				player_edit;
	t_bool				player_menu;
	t_bool				interaction_select;
	t_bool				object_edit;
	t_bool				object_menu;
	int					object_type;
	t_bool				mouse_down;
	int					sectorcount;
	int					movement_speed;
	t_assets			assets;
	t_player			player;
	t_object			objects[MAX_OBJECTS];
	int					object_count;
	t_interaction		interactions[MAX_INTERACTIONS];
}	t_app;

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
 * Struct for integer coordinate rectangule.
 */
typedef struct s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
}	t_rect;

/**
 * Messages
 */
void			exit_error(char *message);

/**
 * Configuration
 */

/**
 * Application
 */
int				app_init(t_app **app);
void			app_prepare(t_app *app);
void			app_render(t_app *app);
void			app_loop(t_app *app);

/**
 * Images
 */
SDL_Surface		*init_image(int x, int y);
void			put_pixel_to_surface(SDL_Surface *surface, int x,
					int y, int color);
void			flush_surface(SDL_Surface *surface);
int				get_pixel_color(SDL_Surface *surface, int x, int y);

/**
 * Events
 */
int				events_keyup(int keycode, t_app *app);
int				events_keydown(int keycode, t_app *app);
int				events_mouse_track(t_app *app);
int				events_mouse_click(t_app *app, SDL_Event *event);
int				events_window_destroy(void);
int				events_window_other(int windowevent, t_app *app);
int				dispatch_event(t_app *app, SDL_Event *event);
int				events_mouse_drag(t_app *app);

/**
 * Map Editor functions
 * 
 */
t_point			world_to_screen(t_app *app, t_vector2 pos);
t_vector2		screen_to_world(t_app *app, t_point pos);

/**
 * Render functions
 * 
 */
void			render_divider(t_app *app);
void			render_grid(t_app *app, double divider, int color);
void			render_sector(t_app *app, t_vec2_lst *sector_start);
void			render_sectors(t_app *app);
void			render_point(t_app *app, t_vector2 point, int size, int color);
void			render_sector_points(t_app *app);
void			render_fill_active_sector(t_app *app);
void			draw_list_lines(t_app *app, t_vec2_lst *a,
					t_vec2_lst *b, int color);
void			draw_line(t_app *app, t_vector2 *a, t_vector2 *b, int color);
void			linedraw_low(t_app *app, t_point *a, t_point *b, int color);
void			linedraw_high(t_app *app, t_point *a, t_point *b, int color);
int				check_borders(t_app *app, t_point *a, t_point *b);

/**
 * Sector Functions
 */
t_sector_lst	*new_sector_list(t_vec2_lst *wall_list);
t_sector_lst	*put_sector_lst(t_app *app, t_sector_lst *new);
t_bool			complete_sector(t_app *app);
t_sector_lst	*sector_pop(t_app *app, t_sector_lst **pop,
					void (*del)(void *, size_t));
void			sector_delone(t_sector_lst **sector,
					void (*del)(void*, size_t));
size_t			ft_lstlen(t_sector_lst *lst);
t_sector_lst	*sector_by_index(t_app *app, int index);
int				inside_sector_check(t_sector_lst *sector, t_vector2 *mouse);
t_sector_lst	*click_sector(t_app *app);
void			sector_edit(t_app *app, SDL_Keycode key);
t_sector_lst	*find_parent_sector(t_app *app, t_sector_lst *sector);
t_sector_lst	*find_child_sector(t_app *app);
int				get_sector_id(t_app *app, t_sector_lst *sector);
void			cancel_list_creation(t_app *app);
void			add_member_sector(t_sector_lst *parent, t_sector_lst *child);

/**
 * Point/Wall/Wall_list Functions
 */
t_vec2_lst		*new_vector_list(t_vector2 *point);
int				put_to_vector_list(t_vec2_lst **list, t_vec2_lst *new);
int				del_vector_list(t_vec2_lst **list);
t_bool			valid_point(t_app *app);
t_vec2_lst		*ft_lstindex(t_vec2_lst *lst, size_t index);
t_vec2_lst		*find_clicked_vector(t_app *app);
void			reverse_vector_list(t_vec2_lst **head);

/**
 * UI functions
 */
void			zoom_slider(t_app *app);
void			handle_movement(t_app *app);
void			snap_to_nearest(t_app *app, t_point *mouse_pos,
					t_vector2 *snap_pos, double divider);
void			move_divider(t_app *app, SDL_Keycode keycode);
void			activate_slope(t_app *app, SDL_Keycode keycode);

/**
 * Edit Functions
 */
void			change_walls_tex(t_vec2_lst *walls, int wall_tex);
void			change_selected_wall_tex(t_app *app, t_vec2_lst *wall,
					int wall_id);
void			link_wall_to_sector(t_app *app);
void			change_walls_type(t_app *app, t_sector_lst *sector);
t_vec2_lst		*find_opposite_point(t_sector_lst *sector, t_vec2_lst *point);

/**
 * Import
 */
int				import_file(t_app *app, char *path);
void			relink_member_sectors(t_app *app);

/**
 * Export
 */
int				export_file(t_app *app, char *path);
int				get_line_id(t_vec2_lst *list, t_vec2_lst *wall);

/**
 * Font
*/
void			toggle_active_color(t_app *app, int active, char *text,
					t_point point);
void			change_font(t_app *app, int size, int color);
void			load_font(t_app *app);
void			render_text(t_app *app, t_point position, char *text);
void			rect_from_surface(SDL_Surface *surface, t_rect *rect);
int				check_blit(SDL_Surface *src, t_rect *src_rect,
					SDL_Surface *dst, t_rect *dst_rect);
void			blit_surface(SDL_Surface *src, t_rect *src_rect,
					SDL_Surface *dst, t_rect *dst_rect);

/**
 * Help menu
*/
void			render_help_menu(t_app *app);
void			set_icon_rect(t_rect *rect, t_point point, t_point size);
void			load_assets(t_app *app);
void			render_texture_icons(t_app *app);
void			render_sector_info(t_app *app);
void			render_icons(t_app *app, SDL_Surface *asset, t_point point, int max);
void			render_healthbar(t_app *app);
void			render_arrows(t_app *app, t_point left, t_point right);
void			render_ui_frame(t_app *app,t_rect area, int size, int background);
void			color_surface(SDL_Surface *surface, int color);
void			change_item_amount(t_app *app, SDL_Keycode key);
void			render_weapon_statics(t_app *app);
void			render_armor_statics(t_app *app);
void			render_inventory(t_app *app);
void			select_inventory(t_app *app, t_point screen_pos);
int				check_mouse(t_point screen_pos, t_rect rect);
int				check_selected_inventory(t_app *app);

/**
 * Player
*/
void			render_player(t_app *app);
void			weapons_init(t_app *app);
void			armor_init(t_app *app);
void			inventory_init(t_app *app);
void			check_player_position(t_app *app);

/**
 * Objects
 * 
 */
int				new_object(t_app *app);
void			change_object_id(t_app *app, int keycode);
void			del_object(t_app *app, int object_id);
void			link_interaction(t_app *app);
void			draw_object_icon(t_app *app, t_vector2 world_pos, int id);
void			render_objects(t_app *app);
t_bool			valid_object(t_app *app);
t_bool			find_object(t_app *app);

#endif