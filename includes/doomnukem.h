/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:40:49 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/10 13:41:28 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_H
# define DOOMNUKEM_H
# ifdef linux
#  define USING_LINUX 1
# else
#  define USING_LINUX 0
# endif
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <pthread.h>
# include <stdlib.h>
# include <SDL.h>
# include "libft.h"
# include "liblinearalgebra.h"
# include "assets.h"
# include "config.h"
# include "error.h"
# include "events.h"
# include "geometry.h"
# include "engine.h"
# include "player.h"
# include "interactions.h"

//STATUS MACROS
# define STATUS_TITLESCREEN 0
# define STATUS_MAINMENU 1
# define STATUS_GAME 2
# define STATUS_PAUSEMENU 3
# define STATUS_MAINOPTIONS 4
# define STATUS_GAMEOPTIONS 5
# define STATUS_GAMEOVER 6

//BUTTON MACROS
# define BUTTON_IDLE 0
# define BUTTON_SELECT 1
# define BUTTON_PRESS 2

//COLORS
# define WHITE 0xFFFFFFFF
# define BLACK 0xFF000000
# define DARK_RED 0xFFD50000
# define DARK_GREY 0xFF242424
# define GREY 0xFF9A9A9A
# define CYAN 0xFF00FFFF
# define GREEN 0xFF8CFF00

/**
 * Integer type definitions
 */
typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;

typedef struct s_audio
{
	SDL_AudioDeviceID	device_id;
	SDL_AudioSpec		wav_spec;
	SDL_AudioSpec		sound_spec;
	Uint8				*music;
	Uint32				music_length;
	Uint8				*sound;
	Uint32				sound_length;
}	t_audio;

enum e_enemy_states
{
	IDLE,
	ATTACK,
	DEATH,
	WALK
};

/**
 * @brief enemy definition states 
 * 0 idle
 * 1 attack
 * 2 death
 * 3 walk
 * 
 * 
 * 
 * if object doesn't have death, it won't have walk either and so on
 * state count implies if it has just idle(0) or idle and attack(1) and so on
 * states[4][2] 4 states, state sheet start and animation frame duration 
 */
typedef struct s_enemy_def
{
	int		state_count;
	double	range;
	double	speed;
	double	attack_speed;
	float	states[4][3];
}	t_enemy_def;

typedef struct s_enemy_state
{
	int			id;
	t_vector2	pos;
	t_vector2	dir;
	t_bool		dead;
	t_bool		agressive;
	int			state;
	int			next;
}	t_enemy_state;

typedef struct s_projectile
{
	t_vector2	start;
	double		start_z;
	t_vector2	end;
	double		end_z;
	double		timer;
	int			type;
	int			sector;
}	t_projectile;

typedef struct s_render_object
{
	int			id;
	int			tex_size;
	int			frame;
	double		dist;
	t_point		start;
	t_point		draw_start;
	t_point		end;
	t_vector2	size;
	t_vector2	step;
}	t_render_object;

typedef struct s_objectstack
{
	int				visible_count;
	t_render_object	objects[MAX_VISIBLE_WALLS];
}	t_objectstack;

typedef struct s_color
{
	int	a;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_timer
{
	struct timespec	start;
	double			seconds;
}	t_timer;

/**
 * Struct for the application.
 */
typedef struct s_app
{
	t_conf			*conf;
	SDL_Window		*win;
	SDL_Surface		*surface;
	SDL_Event		event;
	t_uint8			status;
	t_assets		assets;
	t_audio			audio;
	t_point			mouse_pos;
	int				occlusion_top[WIN_W];
	int				occlusion_bottom[WIN_W];
	float			depthmap[WIN_H / 2][WIN_W];
	t_bool			depthmap_fill_switch;
	t_wallstack		wallstack;
	t_objectstack	objectstack;
	t_player		player;
	t_sky			sky;
	t_sector		*sectors;
	t_gameobject	objects[MAX_OBJECTS];
	float			object_states[MAX_OBJECTS];
	t_projectile	projectiles[MAX_TEMP_OBJECTS];
	t_enemy_state	enemies[MAX_OBJECTS];
	t_enemy_def		enemy_def[MAX_ENEMY_TYPES];
	t_interaction	interactions[MAX_INTERACTIONS];
	t_animation		animations[MAX_CONCURRENT_ANIMATIONS];
	int				animation_count;
	char			**texts;
	int				text_lengths[MAX_TEXT_LINES];
	t_textmodal		textmodal;
	t_timer			regen_timer;
	t_timer			shoot_timer;
	t_timer			item_timer;
}	t_app;

/**
 * init.c
 */
void		sdl_init(t_app *app);
void		app_init(t_app **app);
int			config_init(t_app *app);
void		load_assets(t_app *app);
void		load_texts(t_app *app);

/**
 * error.c
 */
void		exit_error(char *message);

/**
 * Configuration
 */
void		init_thread_info(t_app *app);

/**
 * Application
 */
void		render_frame(t_app *app);
void		app_loop(t_app *app);
void		render_game(t_app *app);

void		update_fps_counter(t_app *app);
void		start_timer(t_timer *timer, double seconds);
int			check_timer(t_timer *timer);

/**
 * Events
 */
int			events_keyup(int keycode, t_app *app);
int			events_keydown(int keycode, t_app *app);
int			events_mouse_motion(t_app *app);
int			events_mouse_down(int mouse_button, t_app *app);
int			events_mouse_up(int mouse_button, t_app *app);
int			events_mouse_wheel(int wheel_dir, t_app *app);
int			events_window_destroy(void);
int			events_window_other(int windowevent, t_app *app);
int			dispatch_event(t_app *app, SDL_Event *event);
void		handle_movement(t_app *app);

/**
 * Multithreading
 */
void		threads_init(t_app *app, t_thread_data *threads_data);
void		threads_create(t_thread_data *threads_data,
				void *(*renderer)(void *));
void		threads_work(t_thread_data *threads_data);

/**
 * Player
 */
void		player_init(t_app *app);
void		player_control(t_app *app);
void		player_rotate(t_app *app, double angle);
void		player_horizon(t_app *app, double change);
void		player_move(t_app *app, t_movement movement, double speed);
void		player_elevate(t_app *app, t_movement movement, double speed);
void		update_position(t_app *app);
void		update_elevation(t_app *app);
void		player_shoot(t_app *app);
void		player_reload(t_app *app);
void		jetpack(t_app *app);
void		init_camera_plane(t_app *app);
void		init_skybox_plane(t_app *app);
void		heal(t_app *app);
void		shield(t_app *app);
void		regen(t_app *app, int *value);
void		damage(t_app *app, int dmg);

/**
 * Collisions
 */
void		collisions_check(t_app *app);
t_vector2	collisions_apply(t_app *app);
t_bool		collision_sector(t_app *app, int sector_id, int *visited);
t_collision	collision_wall(t_app *app, int sector_id, int wall_id,
				int portal_id);
void		collision_slope(t_app *app, int sector_id);
t_bool		collision_possible(t_vector2 start_pos, t_vector2 end_pos,
				t_line wall, t_bool is_member);
t_vector2	get_possible_movement_point(t_line wall, t_vector2 coord, int side);
t_bool		portal_can_enter(t_app *app, t_vector3 pos, double height, t_line wall, int source_sector,
				int target_sector);
void		portal_enter(t_app *app, int sector_id);
t_bool		inside_sector(t_app *app, int sector_id, t_vector2 coord);
void		check_player_sector(t_app *app);
int			enemy_move_check(t_app *app, t_move new, int sector_id, t_enemy_state *enemy);
void		object_collision(t_app *app);
t_bool		in_range(t_vector2 pos, t_vector2 obj, double epsilon);
t_bool		in_range_height(double pos, double obj, double epsilon);

/**
 * Sectors
 */
double		sector_floor_height(t_app *app, int sector_id, t_vector2 pos);
double		sector_ceil_height(t_app *app, int sector_id, t_vector2 pos);
double		sector_vertical_space(t_app *app, int sector_id, t_vector2 pos);
t_line		get_wall_line(t_app *app, int sector_id, int wall_id);
void		sector_wallstack_build(t_app *app);
void		sector_visible_walls(t_app *app, t_wallstack *wallstack, int index,
				int sector_id);
void		sector_walls_prepare(t_app *app, t_wall *walls, int wall_count);
void		sector_walls_order(t_app *app, t_wall *walls, int wall_count);
void		sector_stack_render(t_app *app, t_thread_data *thread,
				int stack_id, t_limit limit);
void		*sector_render_thread(void *data);
void		render_sectors(t_app *app);

/**
 * Sector raycast
 */
void		sector_walls_raycast(t_app *app, t_thread_data *thread,
				t_raycast_info info);
void		sector_walls_raycast_transparent(t_app *app, t_thread_data *thread,
				t_raycast_info info);
t_bool		raycast_hit(t_app *app, t_line wall, t_rayhit *hit, int x);
t_bool		raycast_decor(t_app *app, t_line wall, t_rayhit *hit);

/**
 * Sector draw
*/
void		set_wall_vertical_positions(t_app *app, t_rayhit *hit);
void		draw_wall(t_app *app, int x, t_rayhit *hit, int occlusion);
void		draw_wall_decor(t_app *app, int x, t_rayhit *hit);
void		draw_floor(t_app *app, int x, t_rayhit *hit);
void		draw_ceiling(t_app *app, int x, t_rayhit *hit);
void		draw_portal_partial(t_app *app, int x, t_rayhit *hit);
void		draw_portal_partial_parent(t_app *app, int x, t_rayhit *hit);
void		draw_portal_partial_hole(t_app *app, int x, t_rayhit *hit);

/**
 * Interactions
 */
void		interaction_check(t_app *app);
void		interaction_check_portal(t_app *app, int sector_id);
void		interaction_trigger(t_app *app, int interaction_index);

/**
 * Animations
 */
t_bool		animation_create(t_app *app, t_animation animation);
void		progress_animations(t_app *app);

/**
 * Textmodal animations
 */
void		render_textmodals(t_app *app);

/**
 * Sky
 */
int			get_sky_pixel(t_app *app, int x, int y);

/**
 * Font
 */
void		load_font(t_app *app);
void		change_font(t_app *app, int size, int color);
void		render_text(t_app *app, t_rect frame, char *text);

/**
 * UI
 */
void		render_ui_frame(t_app *app, t_rect area, int size, int background);
void		render_ui(t_app *app);
void		render_player_status(t_app *app);
void		render_equipment(t_app *app);
void		hud_weapon(t_app *app, t_rect rect);
void		hud_quickslot(t_app *app, t_rect rect, char *slot);
void		render_pointer(t_app *app, int x, int y);
void		render_crosshair(t_app *app);
t_rect		render_button(t_app *app, t_rect area, int size, char *text);
void		render_text_prompt(t_app *app, t_rect area, int size, char *text);
void		render_ui_element(t_app *app, SDL_Surface *elem, t_rect area);
int			check_mouse(t_app *app, t_rect rect);

/**
* Button Functions
*/

void		button_function(t_app *app, t_rect button, void (*f)(t_app *app));
void		start_game(t_app *app);
void		pause_game(t_app *app);
void		exit_game(t_app *app);
void		main_menu(t_app *app);
void		do_nothing(t_app *app);
void		main_options(t_app *app);
void		game_options(t_app *app);
void		fullscreen(t_app *app);

/**
 * Render Game Status
 */
void		render_mainmenu(t_app *app);
void		render_titlescreen(t_app *app);
void		render_game(t_app *app);
void		render_pausemenu(t_app *app);
void		render_options(t_app *app);
void		render_gameover(t_app *app);
void		render_hand(t_app *app, int x, int y);

/*
* AUDIO.C
*/
void		load_music(t_app *app, char *file);
void		play_music(t_app *app);
void		play_sound(t_app *app, char *file);
void		pause_audio(t_app *app);
void		unpause_audio(t_app *app);
void		stop_audio(t_app *app);

/**
 * utils_sdl
 */
int			get_pixel_color(SDL_Surface *surface, int x, int y);
int			shade_color(int color, int shade);
void		put_pixel_to_surface(SDL_Surface *surface, int x, int y, int color);
void		put_pixel_to_surface_check(t_app *app, t_point point, int color,
				float distance);
void		blit_surface(SDL_Surface *src, t_rect *src_rect,
				SDL_Surface *dst, t_rect *dst_rect);
int			check_blit(SDL_Surface *src, t_rect *src_rect,
				SDL_Surface *dst, t_rect *dst_rect);
void		rect_from_surface(SDL_Surface *surface, t_rect *rect);
void		color_surface(SDL_Surface *surface, int color);
int			blend_pixel(t_color base, t_color top);
t_color		int_to_argb(int color);
int			argb_to_int(t_color color);
SDL_Surface *bmp_to_surface(const char *path);
void		fill_fog(t_app *app);
int			shade_depth(int color, float shade);

/**
 * utils
 */
void		map_coordinates(t_rect *src, t_rect *dst, t_point *point);
void		clamp_int(int *number, int min, int max);

/**
 * maps 
 */
int			import_file(t_app *app, char *path);

/**
 * objects
 */
void		render_objects(t_app *app);
void		init_enemies(t_app *app);
void		update_enemy_states(t_app *app);
void		define_enemies(t_app *app);
void		fire(t_app *app, t_vector3 target_dir, t_vector3 start_pos, t_point info);
void		update_projectiles(t_app *app);

#endif
