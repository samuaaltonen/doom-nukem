/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:04:04 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/13 14:00:16 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Based on the object type, highlights the correct movement type (moves,
 * follows, in place) on the help menu sidebar.
*/
static void	render_object_movement_type(t_app *app, int movement)
{
	change_font(app, 11, TEXT);
	if (movement == 1)
	{
		render_text(app, (t_rect){121, 185, 120, 15}, "MOVES");
		render_text(app, (t_rect){175, 185, 120, 15}, "FOLLOWS");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){35, 185, 120, 15}, "- IN PLACE -");
	}
	else if (movement == 2)
	{
		render_text(app, (t_rect){45, 185, 120, 15}, "IN PLACE");
		render_text(app, (t_rect){175, 185, 120, 15}, "FOLLOWS");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){111, 185, 120, 15}, "- MOVES -");
	}
	else
	{
		render_text(app, (t_rect){45, 185, 120, 15}, "IN PLACE");
		render_text(app, (t_rect){121, 185, 120, 15}, "MOVES");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){165, 185, 120, 15}, "- FOLLOWS -");
	}
}

/**
 * Renders object related texts on the help menu sidebar.
*/
static void	render_object_texts(t_app *app)
{
	int	pickable;
	int	movement;
	int	type;

	type = 1;
	pickable = 0;
	movement = 0;
	if (type < 5 || type == 10 || type > 15)
		pickable = 1;
	if (type < 9 || type == 14 || type == 16)
		movement = 1;
	if (type == 12 || type < 16)
		movement = 1;
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){113, 120, 120, 15}, "MONSTER");
	render_text(app, (t_rect){40, 140, 120, 15}, "HEALTH");
	render_text(app, (t_rect){210, 140, 120, 15}, "100");
	render_text(app, (t_rect){40, 155, 120, 15}, "DAMAGE");
	render_text(app, (t_rect){210, 155, 120, 15}, "10");
	if (pickable)
	{
		render_text(app, (t_rect){50, 170, 120, 15}, "UNPICKABLE");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){155, 170, 120, 15}, "- PICKABLE -");
	}
	else
	{
		render_text(app, (t_rect){165, 170, 120, 15}, "PICKABLE");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){40, 170, 120, 15}, "- UNPICKABLE -");
	}
	render_object_movement_type(app, movement);
}

/**
* Renders object staticbars on the help menu sidebar.
*/
void	render_object_statics(t_app *app)
{
	int		x;
	int		y;

	y = 140;
	while (y < 250)
	{
		x = 100;
		while (x < 220)
		{
			if (x < 100 + 100 && y < 150)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			if (x < 10 + 100 && y > 153 && y < 163)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			x++;
		}
		y++;
	}
	render_object_texts(app);
}

/**
 * Renders object specific information on the help menu sidebar.
*/
void	object_edit_menu(t_app *app)
{
	int			id;
	t_point		screen_pos;

	SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 40, 50, 20}, "OBJECTS");
	change_font(app, 11, TEXT);
	render_arrows(app, (t_point){10, 67}, (t_point){265, 67});
	render_icons(app, (t_point){25, 60}, app->current_object->type,
		app->assets.objects);
	render_object_statics(app);
	change_font(app, 11, TEXT);
	id = find_object_interaction(app);
	render_current_interaction_status(app, screen_pos, 210, id);
}
