/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:18 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/05 14:12:50 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Initializes application struct.
 */
int	app_init(t_app **app)
{
	*app = (t_app *)malloc(sizeof(t_app));
	if (!(*app))
		return (FALSE);
	ft_bzero(*app, sizeof(t_app));
	return (TRUE);
}

/**
 * Prepares the application to be rendered:
 * Creates window, loads assets, adds event hooks and sets
 * initial player position / direction.
 */
void	app_prepare(t_app *app)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		exit_error(MSG_ERROR_SDL_INIT);
	app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!app->win)
		exit_error(MSG_ERROR_WINDOW);
	app->surface = SDL_GetWindowSurface(app->win);
	if (!app->surface)
		exit_error(MSG_ERROR_WINDOW_SURFACE);
	app->aspect_ratio = ((double)app->surface->h / (double)app->surface->w)
		* -100;
	app->view_pos = (t_vector2){-50.0, 50.0};
	app->zoom_area = (t_vector2){100.0, app->aspect_ratio};
	app->view_size = (t_vector2){app->view_pos.x + app->zoom_area.x,
		app->view_pos.y + app->zoom_area.y};
	app->divider = 1.0f;
	app->zoom_range = 5;
	app->player_edit = TRUE;
	app->player.health = 200;
	app->player.armor = 100;
	app->movement_speed = 4;
	load_assets(app);
	load_font(app);
	weapons_init(app);
	SDL_ShowCursor(SDL_ENABLE);
}

static void	app_render_helper(t_app *app)
{
	if (app->active)
	{
		render_sector(app, app->active);
		render_point(app, app->active->point, 3, POINT);
	}
	if (app->interaction_menu && app->current_interaction)
		render_target_sector_lines(app);
	render_sector_points(app);
	if (app->list_ongoing)
	{
		if (valid_point(app))
			draw_line(app, &app->active_last->point, &app->mouse_track, LINE_A);
		else
			draw_line(app, &app->active_last->point, &app->mouse_track, LINE_B);
	}
}

/**
 * Rendering function to be called in loop hook. Calls individual renderers and
 * draws resulting image(s) to the window.
 */
void	app_render(t_app *app)
{
	flush_surface(app->surface);
	handle_movement(app);
	app->view_size.x = app->view_pos.x + app->zoom_area.x;
	app->view_size.y = app->view_pos.y + app->zoom_area.y;
	render_fill_active_sector(app);
	render_divider(app);
	render_sectors(app);
	app_render_helper(app);
	render_objects(app);
	render_player(app);
	zoom_slider(app);
	render_help_menu(app);
	if (app->object_new)
		draw_object_icon(app, app->mouse_track, app->current_object->type);
	SDL_UpdateWindowSurface(app->win);
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
		ft_printf("x=%f, y=%f modes:c%i,o%i,p%i,r%i,f%i,s%i,n%i,i%p,object_menu%i,player%i\n", app->mouse_track.x, app->mouse_track.y, app->list_creation, app->list_ongoing, app->portal_selection, app->ceiling_edit, app->floor_edit, app->slope_edit, app->object_new, app->current_interaction, app->object_menu, app->player_edit);
		if (app->active_sector)
		{
			if (app->object_menu)
				ft_printf("selected object id:%i, type:%i, var:%f ",get_object_id(app, app->current_object), app->current_object->type, app->current_object->var);
			if (app->current_interaction)
				ft_printf("current interaction event_id:%i, variable: %f, targer: %i ", app->current_interaction->event_id, app->current_interaction->variable, app->current_interaction->target_sector);
			ft_printf("inside = %i, floor: h:%f,tex:%i,o:%i, ceil: h:%f,tex:%i,o:%i, light:%i\n has members: ", app->active_sector, app->active_sector->floor_height, app->active_sector->floor_tex, app->active_sector->floor_tex_offset, app->active_sector->ceil_height, app->active_sector->ceil_tex, app->active_sector->ceil_tex_offset, app->active_sector->light);
			for (int i = 0; i < 4 && app->active_sector->member_sectors[i]; ++i)
				ft_printf("%i ", get_sector_id(app, app->active_sector->member_sectors[i]));
			ft_printf("\n");
			if (app->active_sector->parent_sector)
				ft_printf("parent id %i, ", app->active_sector->parent_sector);
			if (app->active_sector->ceil_slope_wall)
				ft_printf("ceiling slopes from %i to %i, height %f, ", app->active_sector->ceil_slope_wall, app->active_sector->ceil_slope_opposite, app->active_sector->ceil_slope_height);
			if (app->active_sector->floor_slope_wall)
				ft_printf("floor slopes from %i to %i, height %f", app->active_sector->floor_slope_wall, app->active_sector->floor_slope_opposite, app->active_sector->floor_slope_height);
			ft_printf("\n");
		}
		if (app->active)
			ft_printf("selected point x:%f, y:%f, tex:%i, type:%i, decor:%i, decor offset: %f,%f\n", app->active->point.x, app->active->point.y, app->active->tex, app->active->type, app->active->decor, app->active->decor_offset.x, app->active->decor_offset.y);
		// for (int index = 0; index < 10; index++)
		// {
		// 	ft_printf("INDEX %i\n", index);
		// 	ft_printf("ID %i VARIABLE %f TARGET %i SECTOR %i WALL %i OBJECT %i\n\n", app->interactions[index].event_id, app->interactions[index].variable, app->interactions[index].target_sector, app->interactions[index].activation_sector, app->interactions[index].activation_wall, app->interactions[index].activation_object);
		// }
		// for (int index = 0; index < 10; index++)
		// {
		// 	ft_printf("COUNT %i\n", app->object_count);
		// 	ft_printf("INDEX %i\n", index);
		// 	ft_printf("TYPE %i SECTOR %i\n\n", app->objects[index].type, app->objects[index].sector);
		// }
		// for(int i = 0; i < MAX_INTERACTIONS; i++)
		// 	ft_printf("read interactions id %i, activation sector%i, wall%i, object%i\n",app->interactions[i].event_id, app->interactions[i].activation_sector, app->interactions[i].activation_wall, app->interactions[i].activation_object);
		// ft_printf("\n");
		app_render(app);
	}
}
