/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem_editor.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:40:49 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/22 12:51:51 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_EDITOR_H
# define DOOMNUKEM_EDITOR_H
# define WIN_NAME "Doom Nukem Editor"
# define WIN_W 1280
# define WIN_H 720
# define HELP_MENU_W 280
# define TEX_SIZE 128
# define SMALL_ICON 32
# define ICON_SIZE 64
# define OBJECT_SCREEN_SIZE 16
# define THREAD_COUNT 2
# define IMAGE_PIXEL_BYTES 4
# define IMAGE_PIXEL_BITS 32
# define MAX_TEX_COUNT 98
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 16
# define MAX_WEAPONS 3
# define MAX_UNIQUE_OBJECTS 18
# define MAX_INTERACTIONS 64
# define MAX_UNIQUE_INTERACTIONS 7
# define MAX_DECOR_COUNT 27
# define MAX_AMMO 999
# define MAX_ITEM_CAPACITY 99
# define MAX_OBJECTS 128
# define INVENTORY_SIZE 6
# define DEG_IN_RADIAN 0.01745f
# define PI_HALF 1.57079632679
# define PI_PI 6.28318530718
# define RADIAN_IN_DEG 57.29578f
# define MAP_SPEED 0.85f
# define HEIGHT_INC 0.125f
# define MAX_SEARCH_COUNT 100000
# define MAX_GRAVITY -1.0
# define MIN_GRAVITY -50.0
# define DEFAULT_GRAVITY -20.0
# define MAX_LEVEL 999
# define LEVEL_IDENTIFIER "level-"
# define FILE_NAME_LENGTH 9
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdlib.h>
# include <SDL.h>
# include "libft.h"
# include "liblinearalgebra.h"
# include "error.h"
# include "sectors.h"
# include "player.h"
# include "export.h"

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
	V_BUTTON = 0b1000000000,
	SHIFT_DOWN = 0b10000000000
};

enum e_colors {
	PORTAL = 0xFF0000,
	PORTAL_LINK = 0x008C00,
	PORTAL_LINK_TARGET = 0x001B00,
	WALL = 0x999999,
	CEILING_ROTATE = 0x888888,
	FLOOR_ROTATE = 0x777777,
	BG_LIGHT = 0x888888,
	BG_DARK = 0x424242,
	BG_MENU = 0x242424,
	TEXT = 0xFF00FFFF,
	ACTIVE_TEXT = 0xFFD50000,
	PLAYER = 0x00FF00,
	LINE_A = 0xAABBCC,
	LINE_B = 0xFF4444,
	UI_FRAME = 0xFF00FFFF,
	POINT = 0xFF00FF,
	INTERACTION = 0x5050FF,
	LINK = 0xF987C5,
	GREY = 0x202020
};

typedef struct s_draw_line
{
	t_point			dif;
	t_point			pos;
	int				d;
	int				err;
}	t_draw_line;

/**
 * @brief array of objects per entire level
 * 
 */
typedef struct s_object
{
	int				type;
	double			var;
	t_vector2		position;
	t_sector_list	*sector;
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
 * If activation_sector is NULL/-1, activator will be the activator_id in the
 * object array.
 * If activation_sector is set & activation_object is -1, the sector itself
 * is the activator.
 * If active_sector is set & activation_object is set, the activator is the
 * decor on the wall_id declared by activation_object in active sector.
 * If the activator is in the object array & the type of the object is an enemy,
 * it only triggers when the enemy dies.
 * target_sector & target_id will be the same in saves
 */
typedef struct s_interaction
{
	int				event_id;
	double			variable;
	int				interaction_link;
	t_sector_list	*activation_sector;
	t_wall_list		*activation_wall;
	t_object		*activation_object;
	t_sector_list	*target_sector;
	t_bool			requires_key;
}	t_interaction;

/**
 * Struct for font.
 */
typedef struct s_font
{
	SDL_Surface		*font;
	int				size;
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
	SDL_Surface		*objects;
	SDL_Surface		*bg;
}	t_assets;

/**
 * Struct for the application.
 */
typedef struct s_app
{
	int				keystates;
	int				zoom_range;
	SDL_Window		*win;
	SDL_Surface		*surface;
	double			divider;
	double			aspect_ratio;
	t_vector2		view_start;
	t_vector2		view_end;
	t_vector2		view_size;
	t_vector2		mouse_track;
	t_sector_list	*sectors;
	t_sector_list	*active_sector;
	t_wall_list		*active;
	t_wall_list		*active_last;
	t_bool			list_creation;
	t_bool			list_ongoing;
	t_bool			portal_selection;
	t_bool			wall_edit;
	t_bool			ceiling_edit;
	t_bool			floor_edit;
	t_bool			light_edit;
	t_bool			slope_edit;
	t_bool			player_edit;
	t_bool			player_menu;
	t_bool			object_new;
	t_bool			object_menu;
	t_bool			interaction_menu;
	t_bool			decor_edit;
	t_bool			linking_mode;
	t_interaction	*current_interaction;
	t_object		*current_object;
	t_bool			export_assets;
	t_bool			mouse_down;
	int				sector_count;
	int				movement_speed;
	int				event_id;
	t_assets		assets;
	t_player		player;
	t_object		objects[MAX_OBJECTS + 1];
	int				object_count;
	t_interaction	interactions[MAX_INTERACTIONS];
	int				interaction_count;
	int				selected[INVENTORY_SIZE - 1];
	char			filename[FILE_NAME_LENGTH];
	double			import_progress;
	double			gravity;
	t_template		template;
}	t_app;

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
void			exit_success(char *message);

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
void			put_pixel_to_surface(SDL_Surface *surface, int x,
					int y, int color);
void			flush_surface(SDL_Surface *surface);
int				get_pixel_color(SDL_Surface *surface, int x, int y);
SDL_Surface		*bmp_to_surface(const char *path);

/**
 * Events
 */
int				dispatch_event_minimal(SDL_Event *event);
int				events_keyup(t_app *app, int keycode);
int				events_keydown(t_app *app, int keycode);
int				events_mouse_wheel(t_app *app, SDL_Event *event);
int				events_mouse_track(t_app *app);
int				events_mouse_click(t_app *app, SDL_Event *event);
int				events_window_destroy(void);
int				events_window_other(int windowevent, t_app *app);
int				dispatch_event(t_app *app, SDL_Event *event);
int				events_mouse_drag(t_app *app);
void			player_menu_events(t_app *app, t_point	mouse);
void			interaction_menu_events(t_app *app, int start_y,
					t_point mouse);
void			activate_interaction_menu(t_app *app, t_point mouse);
void			edit_left_key_changes(t_app *app, SDL_Keycode keycode);
void			edit_right_key_changes(t_app *app, SDL_Keycode keycode);

/**
 * Map Editor functions
 * 
 */
t_point			world_to_screen(t_app *app, t_vector2 pos);
t_vector2		screen_to_world(t_app *app, t_point pos);

/**
 * Render functions
 */
void			render_divider(t_app *app);
void			render_grid(t_app *app, double divider, int color);
void			render_sector(t_app *app, t_wall_list *wall_start,
					t_sector_list *sector);
void			render_sectors(t_app *app);
void			render_point(t_app *app, t_vector2 point, int size, int color);
void			render_decor(t_app *app, t_wall_list *wall, int color);
void			render_sector_points(t_app *app);
void			render_fill_sector(t_app *app, t_sector_list *sector,
					int color);
void			draw_list_lines(t_app *app, t_wall_list *a,
					t_wall_list *b, int color);
void			draw_line(t_app *app, t_vector2 *a, t_vector2 *b, int color);
void			linedraw_low(t_app *app, t_point *a, t_point *b, int color);
void			linedraw_high(t_app *app, t_point *a, t_point *b, int color);
int				check_borders(t_app *app, t_point *a, t_point *b);
void			draw_circle(t_app *app, t_point pos, int rad, int color);

/**
 * Sector Functions
 */
t_sector_list	*new_sector_list(t_wall_list *wall_list);
t_sector_list	*put_sector_list(t_app *app, t_sector_list *new);
t_bool			complete_sector(t_app *app);
t_sector_list	*sector_pop(t_app *app, t_sector_list **pop);
void			sector_delone(t_sector_list **sector);
size_t			ft_lstlen(t_sector_list *lst);
t_sector_list	*sector_by_index(t_app *app, int index);
int				inside_sector_check(t_sector_list *sector, t_vector2 *mouse);
t_sector_list	*click_sector(t_app *app);
void			sector_edit(t_app *app, SDL_Keycode keycode);
t_sector_list	*find_child_sector(t_app *app);
t_sector_list	*find_child_target_sector(t_app *app, t_sector_list *parent);
int				get_sector_id(t_app *app, t_sector_list *sector);
void			cancel_list_creation(t_app *app);
void			add_member_sector(t_sector_list *parent, t_sector_list *child);
void			del_sector_portals(t_app *app, int deleted);
t_bool			valid_sector(t_app *app);
int				get_member_sector_count(t_sector_list *parent);
int				del_all_sector_interactions(t_app *app, t_sector_list **sector);
int				find_links(t_app *app, t_sector_list *new_list);
void			make_point_array(t_app *app, t_vector2 *array,
					t_sector_list *sector, int *count);
void			sort_point_array(t_vector2 *array, int *count);
void			update_sector_template(t_app *app);
void			sector_template_init(t_app *app);

/**
 * Point/Wall/Wall_list Functions
 */
t_wall_list		*new_vector_list(t_vector2 *point);
t_wall_list		*put_to_vector_list(t_wall_list **list, t_wall_list *new);
int				del_vector_list(t_wall_list **list);
t_bool			valid_point(t_app *app);
t_bool			check_last_point(t_app *app);
t_wall_list		*ft_lstindex(t_wall_list *lst, size_t index);
t_wall_list		*find_clicked_vector(t_app *app);
size_t			vec2_lstlen(t_wall_list *lst_start);

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
void			change_walls_tex(t_wall_list *walls, int wall_tex);
void			link_wall_to_sector(t_app *app);
void			change_walls_type(t_app *app, t_sector_list *sector);
t_wall_list		*find_opposite_point(t_sector_list *sector, t_wall_list *point);

/**
 * Import
 */
void			import_init(t_app *app, const char *level);
void			render_loading(t_app *app, double progress,
					t_bool dispatch_events);
void			uncompression_update_progress(t_import_info *info);
void			import_set_complete(t_import_info *info);
void			import_file(t_app *app);
void			import_level(t_app *app, t_thread_data *thread);
void			import_sectors(t_app *app, t_import_info *info);
void			import_player(t_app *app, t_import_info *info);
void			import_objects(t_app *app, t_import_info *info);
void			import_interactions(t_app *app, t_import_info *info);
void			relink_sectors(t_app *app);

/**
 * Data validation
 */
void			level_validation_sector(t_app *app, t_export_sector *sector);

/**
 * Export
 */
void			compression_update_progress(t_import_info *info);
void			export_update_progress(t_import_info *info);
void			export_set_complete(t_import_info *info);
int				get_wall_id(t_wall_list *list, t_wall_list *wall);
void			calculate_progress_assets(t_import_info *info, int index,
					int current_batch);
void			export_file(t_app *app);
void			export_level(t_app *app, t_thread_data *thread, char *path);
void			export_sectors(t_app *app, t_level_header header, int fd,
					t_import_info *info);
void			export_player(t_app *app, int fd, t_import_info *info);
void			export_objects(t_app *app, int fd, t_import_info *info);
void			export_interactions(t_app *app, int fd, t_import_info *info);
void			export_assets(t_import_info *info, int fd);
void			export_surfaces(t_import_info *info, int fd);
void			export_wavs(t_import_info *info, int fd);
void			export_texts(t_import_info *info, int fd);

/**
 * RLE compression
 */
void			expand_data(t_uint8 **data, int *length, int *allocated);
t_uint8			*read_source(const char *source, int *source_length);
void			rle_uncompress_data(t_import_info *info, const char *source,
					t_uint8 **data, int *length);
void			rle_compress(t_import_info *info, const char *source);

/**
 * Font
*/
void			toggle_active_color(t_app *app, int active, char *text,
					t_rect point);
void			change_font(t_app *app, int size, int color);
void			load_font(t_app *app);
void			render_text(t_app *app, t_rect frame, char *text);
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
void			render_player_icons(t_app *app, SDL_Surface *asset,
					t_point point, int max);
void			render_statusbar(t_app *app, t_point point, int statusbar,
					int color);
void			render_arrows(t_app *app, t_point left, t_point right);
void			render_up_and_down_arrows(t_app *app, t_point up, t_point down,
					int size);
void			render_ui_frame(t_app *app, t_rect area, int size,
					int background);
void			color_surface(SDL_Surface *surface, int color);
void			change_item_amount(t_app *app, SDL_Keycode key);
void			render_weapons(t_app *app);
void			render_object_statics(t_app *app, int health, int damage);
void			render_icons(t_app *app, t_point point, int id,
					SDL_Surface *asset);
t_bool			current_decor_interaction(t_app *app, t_point mouse, int id);
t_bool			current_object_interaction(t_app *app, t_point mouse, int id);
t_bool			current_sector_interaction(t_app *app, t_point mouse, int id);
void			interaction_edit_menu(t_app *app, int start_y,
					t_point mouse);
void			render_interaction_button(t_app *app, t_rect button,
					t_point mouse, char *text);
void			render_current_interaction_status(t_app *app,
					t_point mouse, int y, int id);
void			render_inventory(t_app *app);
void			select_inventory(t_app *app, t_point mouse);
void			select_weapons(t_app *app, t_point mouse);
void			object_edit_menu(t_app *app);
void			player_edit_menu(t_app *app);
void			wall_edit_menu(t_app *app, t_point mouse);
void			sector_edit_menu(t_app *app, t_point mouse, int y);
void			render_interaction_explanations(t_app *app, int start_y);
void			text_popup_explanation(t_app *app, int start_y, char *statics);
void			sound_explanation(t_app *app, int start_y, char *statics);
void			end_level_explanation(t_app *app, int start_y, char *statics);
int				check_mouse(t_point screen_pos, t_rect rect);
void			render_amount_info(t_app *app, t_rect position, int item);
void			gravity_menu(t_app *app);

/**
 * Player
*/
void			render_player(t_app *app);
void			weapons_init(t_app *app);
void			check_player_position(t_app *app);

/**
 * Objects & Interactions
 */
int				new_object(t_app *app);
void			change_object_id(t_app *app, int keycode);
void			del_object(t_app *app, int id);
void			del_all_objects_in_sector(t_app *app);
void			link_interaction(t_app *app);
void			draw_object_icon(t_app *app, t_vector2 world_pos, int id);
void			render_objects(t_app *app);
t_bool			valid_object(t_app *app);
t_bool			select_object(t_app *app);
int				get_object_id(t_app *app, t_object *object);
void			toggle_new_object(t_app *app, t_bool state);
void			interaction_edit(t_app *app, SDL_Keycode keycode);
int				interaction_sector_check(t_app *app, t_sector_list *sector);
int				interaction_wall_check(t_app *app, t_wall_list *wall);
int				interaction_object_check(t_app *app, int id);
int				find_decor_interaction(t_app *app, int start_id,
					t_bool direction);
int				find_object_interaction(t_app *app, int start_id,
					t_bool direction);
int				find_sector_interaction(t_app *app, int start_id,
					t_bool direction);
int				find_interaction(t_app *app);
void			delete_interaction(t_app *app, int id);
void			del_all_decor_interactions(t_app *app);
void			render_target_sector_lines(t_app *app);
void			render_link_interaction_info(t_app *app, int start_y,
					t_point mouse);
void			render_interaction_link_lines(t_app *app);
int				get_current_interaction_count(t_app *app, int interaction);
int				get_interaction_count(t_app *app);
void			fill_triangle(t_app *app, t_triangle triangle, int color);

#endif