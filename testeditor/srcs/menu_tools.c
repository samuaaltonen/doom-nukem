/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_menu_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:41:10 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/08 16:58:38 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders upward pointing arrow in the size given to it.
*/
static void	up_arrow(t_app *app, t_point up, int size)
{
	int		x;
	int		y;
	int		index;

	y = up.y - 1;
	index = 0;
	while (++y < up.y + size)
	{
		x = up.x - 1;
		while (++x < up.x + size)
		{
			if (x <= up.x + index && x >= up.x + size - index)
				put_pixel_to_surface(app->surface, x, y, TEXT);
		}
		index++;
	}
}

/**
 * Renders downward pointing arrow in the size given to it.
*/
static void	down_arrow(t_app *app, t_point down, int size)
{
	int		x;
	int		y;
	int		index;

	y = down.y - 1;
	index = 0;
	while (++y < down.y + size)
	{
		x = down.x - 1;
		while (++x < down.x + size)
		{
			if (x > down.x + index && x < down.x + size - index)
				put_pixel_to_surface(app->surface, x, y, TEXT);
		}
		index++;
	}
}

/**
 * Renders up and down arrows to the points given and in the size given.
*/
void	render_up_and_down_arrows(t_app *app, t_point up,
									t_point down, int size)
{
	up_arrow(app, up, size);
	down_arrow(app, down, size);
}

/**
 * Renders arrows to the side of the icons on the help menu sidebar.
*/
void	render_arrows(t_app *app, t_point left, t_point right)
{
	t_point	screen_pos;

	SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	if ((left.x - 5) < screen_pos.x && (left.x + 10) > screen_pos.x
		&& left.y < screen_pos.y && (left.y + 10) > screen_pos.y)
		toggle_active_color(app, 1, "<", (t_rect){left.x, left.y, 15, 15});
	else
		toggle_active_color(app, 0, "<", (t_rect){left.x, left.y, 15, 15});
	if ((right.x - 5) < screen_pos.x && (right.x + 10) > screen_pos.x
		&& right.y < screen_pos.y && (right.y + 10) > screen_pos.y)
		toggle_active_color(app, 1, ">", (t_rect){right.x, right.y, 15, 15});
	else
		toggle_active_color(app, 0, ">", (t_rect){right.x, right.y, 15, 15});
}

/**
 * Toggles the color of the text between TEXT and ACTIVE_TEXT wether the
 * edit mode is active or not.
*/
void	toggle_active_color(t_app *app, int active, char *text, t_rect point)
{
	if (active == 1)
		change_font(app, 11, ACTIVE_TEXT);
	else
		change_font(app, 11, TEXT);
	render_text(app, point, text);
	change_font(app, 11, TEXT);
}
