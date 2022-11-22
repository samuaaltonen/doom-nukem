/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:04:04 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/22 15:47:41 by ssulkuma         ###   ########.fr       */
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
	render_text(app, (t_point){113, 120}, "MONSTER");
	render_text(app, (t_point){40, 140}, "HEALTH");
	render_text(app, (t_point){210, 140},"100");
	render_text(app, (t_point){40, 155}, "DAMAGE");
	render_text(app, (t_point){210, 155}, "10");
	if (pickable)
	{
		render_text(app, (t_point){50, 170}, "UNPICKABLE");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){155, 170}, "- PICKABLE -");
	}
	else
	{
		render_text(app, (t_point){165, 170}, "PICKABLE");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){40, 170}, "- UNPICKABLE -");
	}
	change_font(app, 11, TEXT);
	if (mode == 1)
	{
		render_text(app, (t_point){121, 185}, "MOVES");
		render_text(app, (t_point){175, 185}, "FOLLOWS");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){35, 185}, "- IN PLACE -");
	}
	else if (mode == 2)
	{
		render_text(app, (t_point){45, 185}, "IN PLACE");
		render_text(app, (t_point){175, 185}, "FOLLOWS");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){111, 185}, "- MOVES -");
	}
	else
	{
		render_text(app, (t_point){45, 185}, "IN PLACE");
		render_text(app, (t_point){121, 185}, "MOVES");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){165, 185}, "- FOLLOWS -");
	}
	change_font(app, 15, TEXT);
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
	render_interaction_texts(app, 220);
}

/**
 * Renders object icons on the help menu sidebar.
*/
void	render_object_icons(t_app *app, t_point point)
{
	t_rect		src;
	t_rect		icon;
	t_point		size;
	int			index;
	int			tex;
	int			object;

	object = 17;
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
		tex = ICON_SIZE * ((index + object - 2) % (MAX_OBJECTS + 1));
		set_icon_rect(&src, (t_point){tex, 0}, size);
		set_icon_rect(&icon, point, size);
		blit_surface(app->assets.sprite, &src, app->surface, &icon);
		point.x += (ICON_SIZE / 2) + 10;
		if (index == 2)
		{
			point.x += (ICON_SIZE / 2);
			point.y += 14;
		}
		index++;
	}
}
