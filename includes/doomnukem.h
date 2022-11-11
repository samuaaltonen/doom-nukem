/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:40:49 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/11 12:19:10 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_H
# define DOOMNUKEM_H

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
# include "engine.h"
# include "error.h"
# include "events.h"
# include "geometry.h"
# include "player.h"

//STATUS MACROS
# define STATUS_TITLESCREEN 0
# define STATUS_MAINMENU 1
# define STATUS_GAME 2
# define STATUS_PAUSEMENU 3

//BUTTON MACROS
# define BUTTON_IDLE 0
# define BUTTON_SELECT 1
# define BUTTON_PRESS 2

/**
 * Integer type definitions
 */
typedef unsigned char	t_uint8;

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
	t_wallstack		wallstack;
	t_thread_data	thread_info[THREAD_COUNT];
	t_player		player;
	t_sector		*sectors;
}	t_app;

/**
 * init.c
 */
void		sdl_init(t_app *app);
void		app_init(t_app **app);
int			config_init(t_app *app);
void		load_assets(t_app *app);

/**
 * error.c
 */
void		exit_error(char *message);

/**
 * Configuration
 */
void		init_thread_info(t_app *app);
void		init_camera_plane(t_app *app);

/**
 * Application
 */
void		render_frame(t_app *app);
void		app_loop(t_app *app);
void		render_game(t_app *app);
void		update_fps_counter(t_app *app);

/**
 * Images
 */
SDL_Surface	*create_surface(int x, int y);
SDL_Surface	*load_texture(char *path);
void		put_pixel_to_surface_depth(t_app *app, t_point point, int color,
				double distance);
void		put_pixel_to_surface_check(t_app *app, t_point point, int color,
				double distance);

/**
 * Events
 */
int			events_keyup(int keycode, t_app *app);
int			events_keydown(int keycode, t_app *app);
int			events_mouse_motion(t_app *app);
int			events_mouse_down(int mouse_button, t_app *app);
int			events_mouse_up(int mouse_button, t_app *app);
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
 * Helper functions
 */
double		get_radial_direction(t_vector2 *vector);
void		clamp_distance(double *distance);
int			get_pixel_color(SDL_Surface *surface, int x, int y);
double		distortion_correction(double angle, double distance);

/**
 * Sectors
 */
t_line			get_wall_line(t_app *app, int sector_id, int wall_id);
void			sector_visible_walls(t_app *app);
void			sector_walls_prepare(t_app *app, t_wall *walls, int wall_count);
void			sector_walls_order(t_app *app, t_wall *walls, int wall_count);
void			sector_walls_raycast(t_app *app, t_thread_data *thread, t_wall *wall, int start_x, int end_x);
void			sector_stack_render(t_app *app, t_thread_data *thread, int stack_id, int start_x, int end_x);
void			*sector_render_thread(void *data);
void			render_sectors(t_app *app);

/**
 * Sector draw
*/
void			set_wall_vertical_positions(t_app *app, t_rayhit *hit);
void			draw_wall(t_app *app, int x, t_rayhit *hit, int occlusion);
void			draw_floor(t_app *app, int x, t_rayhit *hit);
void			draw_ceiling(t_app *app, int x, t_rayhit *hit);
void			draw_portal_partial(t_app *app, int x, t_rayhit *hit);
void			draw_portal_partial_parent(t_app *app, int x, t_rayhit *hit);
void			draw_portal_partial_hole(t_app *app, int x, t_rayhit *hit);

/**
 * Font
 */
void        load_font(t_app *app);
void		change_font(t_app *app, int size, int color);
void    	render_text(t_app *app, t_point position, char *text);

/**
 * UI
 */
void		render_ui(t_app *app);
t_rect    	render_button(t_app *app, t_point pos, int size, char *text);

int			check_mouse(t_app *app, t_rect rect);
void		button_function(t_app *app, t_rect button, void (*f)(t_app *app));
void		start_game(t_app *app);
void		pause_game(t_app *app);
void		exit_game(t_app *app);
void		main_menu(t_app *app);
void		do_nothing(t_app *app);

void		render_mainmenu(t_app *app);
void		render_titlescreen(t_app *app);
void		render_pointer(t_app *app, int x, int y);
void		render_game(t_app *app);
void		render_pausemenu(t_app *app);
/*
* AUDIO.C
*/
void    	play_music(t_app *app, char *file);
void		play_sound(t_app *app, char *file);
void		pause_audio(t_app *app);
void		unpause_audio(t_app *app);
void		stop_audio(t_app *app);

/**
 * utils_sdl
 */
void		put_pixel_to_surface(SDL_Surface *surface, int x, int y, int color);
void		flush_surface(SDL_Surface *surface);
void		blit_surface(SDL_Surface *src, t_rect *src_rect,
	SDL_Surface *dst, t_rect *dst_rect);
int			check_blit(SDL_Surface *src, t_rect *src_rect,
	SDL_Surface *dst, t_rect *dst_rect);
void		rect_from_surface(SDL_Surface *surface, t_rect *rect);
/**
 * utils
 */
void		map_coordinates(t_rect *src, t_rect *dst, t_point *point);

/**
 * maps 
 */
int	import_file(t_app *app, char *path);

#endif
