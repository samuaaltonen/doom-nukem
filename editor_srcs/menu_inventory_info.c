/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_inventory_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:09:50 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/07 14:06:36 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Toggles the selection button on the inventory, checking that
 * mouse is inside button rectangle.
 * 
 * @param app
 * @param mouse
*/
void	select_inventory(t_app *app, t_point mouse)
{
	int		index;
	int		x;
	int		y;

	index = 0;
	y = 309;
	x = 0;
	while (index < INVENTORY_SIZE - 1)
	{
		if (index % 5 == 0 && index != 0)
		{
			y += 41;
			x = 0;
		}
		if (check_mouse(mouse, (t_rect){(SMALL_ICON) * (x + 1)
				+ (10 * (x + 1)) - 3, y, 35, 35}))
			app->selected[index] = ft_toggle(app->selected[index]);
		index++;
		x++;
	}
}

/**
 * @brief Renders the item amount over the inventory icon matching it.
 * 
 * @param app
 * @param position
 * @param item
*/
void	render_amount_info(t_app *app, t_rect position, int item)
{
	char	*amount;

	amount = ft_itoa(item);
	if (!amount)
		return ;
	render_text(app, position, amount);
	free(amount);
}

/**
 * @brief Renders inventory related texts and item capacity on the help menu
 * sidebar.
 * 
 * @param app
 * @param x
 * @param y
*/
static void	render_inventory_texts(t_app *app, int x, int y)
{
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 288, 150, 20}, "INVENTORY");
	change_font(app, 11, TEXT);
	render_amount_info(app, (t_rect){x, y, 30, 20},
		app->player.inventory.antidote);
	render_amount_info(app, (t_rect){x + 42, y, 30, 20},
		app->player.inventory.key);
	render_amount_info(app, (t_rect){x + 84, y, 30, 20},
		app->player.inventory.ammo);
	render_amount_info(app, (t_rect){x + 126, y, 30, 20},
		app->player.inventory.potion);
	render_amount_info(app, (t_rect){x + 168, y, 30, 20},
		app->player.inventory.jetpack);
	render_text(app, (t_rect){30, y + 50, 255, 50}, "LEFT CLICK ITEMS AND USE \
ARROW KEYS TO CHANGE THE AMOUNT.");
}

/**
 * @brief Renders the start inventory icons and selection frame to the help menu
 * sidebar.
 * 
 * @param app
*/
void	render_inventory(t_app *app)
{
	int		index;
	int		y;
	int		x;

	render_player_icons(app, app->assets.objects, (t_point){40, 310},
		INVENTORY_SIZE - 1);
	index = 0;
	y = 309;
	x = 0;
	while (index < INVENTORY_SIZE - 1)
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
	render_inventory_texts(app, 53, 312);
}
