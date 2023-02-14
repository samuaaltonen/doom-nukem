/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:04:04 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/14 15:32:47 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Based on the object type, highlights the correct movement type (moves,
 * follows, in place) on the help menu sidebar.
 * 
 * @param app
 * @param movement
*/
static void	render_object_movement_type(t_app *app, t_bool movement)
{
	change_font(app, 11, TEXT);
	if (movement == TRUE)
	{
		render_text(app, (t_rect){168, 185, 120, 15}, "IN PLACE");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){30, 185, 120, 15}, "- FOLLOWS -");
	}
	else
	{
		render_text(app, (t_rect){40, 185, 120, 15}, "FOLLOWS");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){158, 185, 120, 15}, "- IN PLACE -");
	}
}

/**
 * @brief Based on the object type, displays the correct statics on the help
 * menu sidebar.
 * 
 * @param app
*/
static void	render_object_type_statics(t_app *app)
{
	change_font(app, 11, TEXT);
	if (app->current_object->type <= MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS)
	{
		render_text(app, (t_rect){120, 120, 120, 15}, "OBJECT");
		render_text(app, (t_rect){40, 140, 120, 15}, "HEALTH");
		render_text(app, (t_rect){210, 140, 120, 15}, "0");
		render_text(app, (t_rect){40, 155, 120, 15}, "DAMAGE");
		render_text(app, (t_rect){210, 155, 120, 15}, "0");
	}
	else if (app->current_object->type == MAX_UNIQUE_OBJECTS - 1)
	{
		render_text(app, (t_rect){113, 120, 120, 15}, "MONSTER");
		render_text(app, (t_rect){40, 140, 120, 15}, "HEALTH");
		render_text(app, (t_rect){210, 140, 120, 15}, "75");
		render_text(app, (t_rect){40, 155, 120, 15}, "DAMAGE");
		render_text(app, (t_rect){210, 155, 120, 15}, "25");
	}
	else if (app->current_object->type <= MAX_UNIQUE_OBJECTS)
	{
		render_text(app, (t_rect){113, 120, 120, 15}, "MONSTER");
		render_text(app, (t_rect){40, 140, 120, 15}, "HEALTH");
		render_text(app, (t_rect){210, 140, 120, 15}, "100");
		render_text(app, (t_rect){40, 155, 120, 15}, "DAMAGE");
		render_text(app, (t_rect){210, 155, 120, 15}, "20");
	}
}

/**
 * @brief Renders object related texts on the help menu sidebar.
 * 
 * @param app
*/
static void	render_object_texts(t_app *app)
{
	t_bool	pickable;
	t_bool	movement;

	pickable = FALSE;
	movement = FALSE;
	if (app->current_object->type <= MAX_SMALL_OBJECTS)
		pickable = TRUE;
	else if (app->current_object->type <= MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS)
		movement = FALSE;
	else if (app->current_object->type <= MAX_UNIQUE_OBJECTS)
		movement = TRUE;
	render_object_type_statics(app);
	if (pickable)
	{
		render_text(app, (t_rect){40, 170, 120, 15}, "UNPICKABLE");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){155, 170, 120, 15}, "- PICKABLE -");
	}
	else
	{
		render_text(app, (t_rect){165, 170, 120, 15}, "PICKABLE");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){30, 170, 130, 15}, "- UNPICKABLE -");
	}
	render_object_movement_type(app, movement);
}

/**
 * @brief Renders object staticbars on the help menu sidebar.
 * 
 * @param app
*/
void	render_object_statics(t_app *app, int health, int damage)
{
	int		x;
	int		y;

	y = 139;
	while (++y < 250)
	{
		x = 99;
		while (++x < 220)
		{
			if (app->current_object->type > MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS)
				health = 100;
			if (app->current_object->type > MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS)
				damage = 20;
			if (app->current_object->type == MAX_UNIQUE_OBJECTS - 1)
				health = 75;
			if (app->current_object->type == MAX_UNIQUE_OBJECTS - 1)
				damage = 25;
			if (x < (health + 100) && y < 150)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			if (x < (damage + 100) && y > 153 && y < 163)
				put_pixel_to_surface(app->surface, x, y, TEXT);
		}
	}
	render_object_texts(app);
}

/**
 * @brief Renders object specific information on the help menu sidebar.
 * 
 * @param app
*/
void	object_edit_menu(t_app *app)
{
	int			id;
	t_point		mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 40, 50, 20}, "OBJECTS");
	change_font(app, 11, TEXT);
	render_arrows(app, (t_point){10, 67}, (t_point){265, 67});
	render_icons(app, (t_point){25, 60}, app->current_object->type - 1,
		app->assets.objects);
	render_object_statics(app, 1, 1);
	change_font(app, 11, TEXT);
	if (!app->current_interaction)
		id = find_object_interaction(app, 0, 1);
	else
		id = find_object_interaction(app, find_interaction(app), 1);
	render_current_interaction_status(app, mouse, 210, id);
	render_text(app, (t_rect){42, 290, 260, 15}, "DELETE OBJECT ( BACKSPACE )");
}
