/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:20:36 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/23 21:56:27 by saaltone         ###   ########.fr       */
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
# define MSG_ERROR_MOUSE "Could not set mouse cursor relative to the window."
# define THREAD_COUNT 8
# define IMAGE_PIXEL_BYTES 4
# define IMAGE_PIXEL_BITS 32
# define COLLISION_OFFSET 0.25f
# define DIRECTION_START_X -1.f
# define DIRECTION_START_Y 0.f
# define FOV 66
# define DEG_IN_RADIAN 0.01745f
# define RADIAN_IN_DEG 57.29578f
# define ROTATION_SPEED 1.8f
# define MOVEMENT_SPEED 3.2f
# define MAX_RAY_DISTANCE 25.f
# define TEX_SIZE 64
# define MOUSE_SENSITIVITY 10.f
# define TEXTURE_PANELS "./assets/texture_spritesheet.xpm"
# define TEXTURE_BACKGROUND "./assets/bg.xpm"
# define MAX_POLYGON_CORNERS 6
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <pthread.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include "libft.h"
# include "liblinearalgebra.h"

/**
 * Integer type definitions
 */
typedef unsigned char	t_uint8;

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
 * Polygons
*/
typedef struct s_poly
{
	t_vector2	corners[MAX_POLYGON_CORNERS];
	int			corner_count;
	double		bottom;
	double		top;
}	t_poly;

/**
 * Struct for images.
 */
typedef struct s_image
{
	int				line_size;
	int				width;
	int				height;
	SDL_Surface		*surface;
	char			*data;
}	t_image;

/**
 * Struct for configuration variables of the application.
 */
typedef struct s_conf
{
	int				toggle_help;
	int				fps;
	struct timespec	fps_clock;
	double			delta_time;
	double			skybox_offset;
	int				fov;
	int				keystates;
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
}	t_player;

/**
 * Struct for the application.
 */
typedef struct s_app
{
	t_conf			*conf;
	SDL_Window		*win;
	SDL_Surface		*surface;
	t_image			*image;
	t_image			*depthmap;
	t_thread_data	thread_info[THREAD_COUNT];
	t_player		player;
	t_image			*sprite;
	t_image			*bg;
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
t_image		*init_image(int x, int y);
t_image		*init_xpm_image(char *path);
void		put_pixel_to_image(t_image *image, int x, int y, int color);
void		put_pixel_to_image_depth(t_app *app, t_point point, int color,
				float distance);
void		put_pixel_to_image_check(t_app *app, t_point point, int color,
				float distance);
void		flush_image(t_image *image);

/**
 * Events
 */
int			events_keyup(int keycode, t_app *app);
int			events_keydown(int keycode, t_app *app);
int			events_mouse_track(t_app *app);
int			events_window_destroy(void);
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
 * Walls
*/
void		*render_polygons(void *data);

/**
 * Helper functions
 */
double		get_radial_direction(t_vector2 *vector);
void		clamp_distance(double *distance);
int			get_pixel_color(t_image *image, int x, int y);

#endif

/**
 * TESTDATA globals
*/
extern t_poly test_polygons[];
extern int test_polygon_count;