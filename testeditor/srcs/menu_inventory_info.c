/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_inventory_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:09:50 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/12 16:19:17 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Toggles the selection button on the inventory, checking that
 * mouse is inside button rectangle.
*/
void	select_inventory(t_app *app, t_point screen_pos)
{
	int		index;
	int		x;
	int		y;

	index = 0;
	y = 309;
	x = 0;
	while (index < INVENTORY_SIZE)
	{
		if (index % 5 == 0 && index != 0)
		{
			y += 41;
			x = 0;
		}
		if (check_mouse(screen_pos, (t_rect){(SMALL_ICON) * (x + 1)
				+ (10 * (x + 1)) - 3, y, 35, 35}))
			app->selected[index] = ft_toggle(app->selected[index]);
		index++;
		x++;
	}
}

/**
 * Renders inventory related texts and item capacity on the help menu sidebar.
*/
static void	render_inventory_texts(t_app *app, int x, int y)
{
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 288, 150, 20}, "INVENTORY");
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){x, y + 1, 30, 20},
		ft_itoa(app->player.inventory.ammo));
	render_text(app, (t_rect){x + 42, y + 1, 30, 20},
		ft_itoa(app->player.inventory.special_ammo));
	render_text(app, (t_rect){x + 84, y + 1, 30, 20},
		ft_itoa(app->player.inventory.potion));
	render_text(app, (t_rect){x + 128, y + 1, 30, 20},
		ft_itoa(app->player.inventory.antidote));
	render_text(app, (t_rect){x + 170, y + 1, 30, 20},
		ft_itoa(app->player.inventory.key));
	render_text(app, (t_rect){x, y + 44, 30, 20},
		ft_itoa(app->player.inventory.jetpack));
	// render_text(app, (t_rect){x + 42, y + 44, 30, 20},
	// 	ft_itoa(app->player.inventory.item1));
	// render_text(app, (t_rect){x + 84, y + 44, 30, 20},
	// 	ft_itoa(app->player.inventory.item2));
	// render_text(app, (t_rect){x + 128, y + 44, 30, 20},
	// 	ft_itoa(app->player.inventory.item3));
	// render_text(app, (t_rect){x + 170, y + 44, 30, 20},
	// 	ft_itoa(app->player.inventory.item4));
	render_text(app, (t_rect){30, y + 90, 255, 50}, "LEFT CLICK ITEMS AND USE \
ARROW KEYS TO CHANGE THE AMOUNT.");
}

/**
 * Renders the start inventory icons and selection frame to the help menu
 * sidebar.
*/
void	render_inventory(t_app *app)
{
	int		index;
	int		y;
	int		x;

	render_player_icons(app, app->assets.sprite, (t_point){40, 310},
		INVENTORY_SIZE + 1);
	index = 0;
	y = 309;
	x = 0;
	while (index < INVENTORY_SIZE)
	{
		if (index % 5 == 0 && index != 0)
		{
			y += 41;
			x = 0;
		}
		if (app->selected[index])
		{
			render_ui_frame(app, (t_rect){(SMALL_ICON) * (x + 1)
				+ (10 * (x + 1)) - 3, y, 35, 35}, 1, 0);
		}
		index++;
		x++;
	}
	render_inventory_texts(app, 53, 311);
}
