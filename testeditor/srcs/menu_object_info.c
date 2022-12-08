/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:04:04 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/02 16:51:50 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders object related texts on the help menu sidebar.
*/
static void	render_object_texts(t_app *app)
{
	int	pickable;
	int	mode;
	int	type;

	type = 1;
	pickable = 0;
	mode = 0;
	if (type < 5 || type == 10 || type > 15)
		pickable = 1;
	if (type < 9 || type == 14 || type == 16)
		mode = 1;
	if (type == 12 || type < 16)
		mode = 1;
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){113, 120, 120, 15}, "MONSTER");
	render_text(app, (t_rect){40, 140, 120, 15}, "HEALTH");
	render_text(app, (t_rect){210, 140, 120, 15},"100");
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
	change_font(app, 11, TEXT);
	if (mode == 1)
	{
		render_text(app, (t_rect){121, 185, 120, 15}, "MOVES");
		render_text(app, (t_rect){175, 185, 120, 15}, "FOLLOWS");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_rect){35, 185, 120, 15}, "- IN PLACE -");
	}
	else if (mode == 2)
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
 * Loops through the interaction array to find if the current object
 * has an interaction or not. Returns array id if it finds one and
 * -1 if not.
*/
int	find_object_interaction(t_app *app)
{
	int		index;

	index = 0;
	while (index <= app->interaction_count)
	{
		if (app->interactions[index].activation_object == app->current_object)
		{
			return (index);
		}
		index++;
	}
	return (-1);
}

/**
* Renders object staticbars on the help menu sidebar.
*/
void	render_object_statics(t_app *app)
{
	int		x;
	int		y;
	int		id;
	t_point	screen_pos;

	SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
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
	change_font(app, 11, TEXT);
	id = find_object_interaction(app);
	render_current_interaction_status(app, screen_pos, 210, id);
}

static int	find_max(t_app *app, SDL_Surface *asset)
{
	if (asset == app->assets.sprite)
		return (MAX_OBJECTS);
	return (0);
}

/**
 * Renders object icons on the help menu sidebar.
*/
void	render_icons(t_app *app, t_point point, int id, SDL_Surface *asset)
{
	t_rect		src;
	t_rect		icon;
	t_point		size;
	int			index;
	int			tex;

	index = 0;
	while (index < 5)
	{
		if (index == 2)
		{
			size = (t_point){ICON_SIZE, ICON_SIZE};
			point.y -= 14;
		}
		else
			size = (t_point){ICON_SIZE / 2, ICON_SIZE / 2};
		tex = ICON_SIZE * ((index + id - 2) % (find_max(app, asset) + 1));
		set_icon_rect(&src, (t_point){tex, 0}, size);
		set_icon_rect(&icon, point, size);
		blit_surface(asset, &src, app->surface, &icon);
		point.x += (ICON_SIZE / 2) + 10;
		if (index == 2)
		{
			point.x += (ICON_SIZE / 2);
			point.y += 14;
		}
		index++;
	}
	render_ui_frame(app, (t_rect){108, point.y - 14, 66, 66}, 1, 0);
}
