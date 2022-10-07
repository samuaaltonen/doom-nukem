/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/07 14:23:17 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Exits the application when window is destroyed.
 */
int	events_window_destroy(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * Exits the program and prints an error message to stderr (either with perror
 * or from variable).
 */
void	exit_error(char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	else
		perror(MSG_ERROR);
	exit(EXIT_FAILURE);
}

/**
 * Initializes image.
 */
SDL_Surface	*init_image(int width, int height)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 
		IMAGE_PIXEL_BITS, SDL_PIXELFORMAT_ARGB8888);
	if (!surface)
		exit_error(MSG_ERROR_IMAGE_INIT);
	return (surface);
}

/**
 * Changes color of a specific pixel in image.
 */
void	put_pixel_to_surface(SDL_Surface *surface, int x, int y, int color)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (y * surface->pitch) + (x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || x >= surface->w || y >= surface->h)
		return ;
	pixel = surface->pixels + pixel_pos;
	*(int *)pixel = color;
}

/**
 * Flushes image (sets all pixels to black)
 */
void	flush_surface(SDL_Surface *surface)
{
	ft_bzero(surface->pixels, surface->h * surface->pitch);
}

/**
 * Initializes application struct.
 */
int	app_init(t_app **app)
{
	*app = (t_app *)malloc(sizeof(t_app));
	ft_bzero(*app, sizeof(t_app));
	if (!(*app))
		return (0);
	return (1);
}

/**
 * Prepares the application to be rendered:
 * Creates window, loads assets, adds event hooks and sets
 * initial player position / direction.
 */
void	app_prepare(t_app *app)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0 || TTF_Init() < 0)
		exit_error(MSG_ERROR_SDL_INIT);
	app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!app->win)
		exit_error(MSG_ERROR_WINDOW);
	app->surface = SDL_GetWindowSurface(app->win);
	if (!app->surface)
		exit_error(MSG_ERROR_WINDOW_SURFACE);
	app->font = TTF_OpenFont(FONT_FILE, 22);
	if (!app->font)
		exit_error(MSG_ERROR_FONT);
	app->view_pos = (t_vector2){-50.0,-50.0};
	app->zoom_area = (t_vector2){100.0,100.0};
	SDL_ShowCursor(SDL_ENABLE);
	//SDL_WarpMouseInWindow(app->win, WIN_W / 2, WIN_H / 2);
}

/**
 * Main game loop. Polls SDL event queue until it is empty and then 
 * proceeds to next frame.
 */
void	app_loop(t_app *app)
{
	SDL_Event	event;

	while (TRUE)
	{
		while (SDL_PollEvent(&event))
			dispatch_event(app, &event);
		app_render(app);
	}

}

/**
 * Tracks mouse position and changes player direction accordingly.
 */
int	events_mouse_track(t_app *app)
{
	(void)app;
	t_point	current_pos;
	
	SDL_GetMouseState(&current_pos.x, &current_pos.y);
	return (0);
}


int events_mouse_wheel(t_app *app, SDL_Event *event)
{
	if(event->wheel.y > 0)
	{
		app->zoom_area.x *= 2;
		app->zoom_area.y *= 2;
	}	
	else if(event->wheel.y < 0)
	{
		app->zoom_area.x /= 2;
		app->zoom_area.y /= 2;
	}
	return (0);
}

/**
 * Dispatches SDL2 event to event handler functions.
*/
int	dispatch_event(t_app *app, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		return events_window_destroy();
	if (event->type == SDL_KEYUP)
		return events_keyup(event->key.keysym.sym, app);
	if (event->type == SDL_KEYDOWN)
		return events_keydown(event->key.keysym.sym, app);
	if (event->type == SDL_MOUSEMOTION)
		return events_mouse_track(app);
	if (event->type == SDL_MOUSEWHEEL)
		return events_mouse_wheel(app, event);	
	return (0);
}



void	handle_movement(t_app *app)
{
	if (app->keystates & FORWARD_DOWN
		|| app->keystates & FORWARD_W_DOWN)
		app->view_pos.y -= MAP_SPEED;
	if (app->keystates & BACKWARD_DOWN
		|| app->keystates & BACKWARD_S_DOWN)
		app->view_pos.y += MAP_SPEED;
	if (app->keystates & LEFT_DOWN)
		app->view_pos.x -= MAP_SPEED;
	if (app->keystates & RIGHT_DOWN)
		app->view_pos.x += MAP_SPEED;
}

void render_grid(t_app *app)
{
	int x;
	int y;
	x = 0;
	y = 0;

	t_vector2 screen = (t_vector2){0.0,0.0};

	while (y < app->surface->h)
	{
		x = 0;
		while(x < app->surface->w)
		{
			screen.x = app->view_pos.x + (x / (double)app->surface->w) * app->zoom_area.x;
			screen.y = app->view_pos.y + (y / (double)app->surface->h) * app->zoom_area.y;

			t_vector2 value = (t_vector2){fabs(fmod(screen.x, 1)),fabs(fmod(screen.y, 1))};
			if(value.x > 0.9 || value.y > 0.9 || value.x < 0.1 || value.y < 0.1)
				put_pixel_to_surface(app->surface, x, y, 0x424242);
			x++;
		}
		y++;
	}
			//-50 + ( 0  / 1000) * 100
}

/**
 * Rendering function to be called in loop hook. Calls individual renderers and
 * draws resulting image(s) to the window.
 */
void	app_render(t_app *app)
{
	flush_surface(app->surface);
	/* SDL_Surface	*converted_surface; */
	SDL_Surface *text_surface;
	text_surface = TTF_RenderText_Solid(app->font, "app->conf->fps_info", (SDL_Color){255, 255, 255, 0});
	handle_movement(app);
	render_grid(app);
	SDL_BlitSurface(text_surface, NULL, app->surface, NULL);
	SDL_FreeSurface(text_surface);
	SDL_UpdateWindowSurface(app->win);
}

int main(void)
{
	t_app	*app;

	if (!app_init(&app))
		exit_error(NULL);
	app_prepare(app);
	app_loop(app);
	return (0);
}