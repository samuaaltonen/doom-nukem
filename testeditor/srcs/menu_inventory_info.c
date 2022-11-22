/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_inventory_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:09:50 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/22 15:28:03 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Sets the start inventory's values.
*/
void	inventory_init(t_app *app)
{
	app->player.inventory.ammo = 10
		* app->player.weapons[app->player.selected_weapon].magazine;
	app->player.inventory.potion = 1;
	app->player.inventory.antidote = 1;
	app->player.inventory.key = 1;
	app->player.inventory.jetpack = 1;
}

/**
 * Checks how many items are seleted from the inventory.
*/
int	check_selected_inventory(t_app *app)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	while (index < (INVENTORY_SIZE - 1))
	{
		if (app->selected[index])
			count++;
		index++;
	}
	return (count);
}

/**
 * Toggles the selection button on the inventory, checking that
 * mouse is inside button rectangle and max 2 items are selected.
*/
void	select_inventory(t_app *app, t_point screen_pos)
{
	if (check_mouse(screen_pos, (t_rect){40, 340, 32, 32})
		&& (app->selected[5] < 2
		|| app->selected[0]))
		app->selected[0]
			= ft_toggle(app->selected[0]);
	if (check_mouse(screen_pos, (t_rect){82, 340, 32, 32})
		&& (app->selected[5] < 2
		|| app->selected[1]))
		app->selected[1]
			= ft_toggle(app->selected[1]);
	if (check_mouse(screen_pos, (t_rect){124, 340, 32, 32})
		&& (app->selected[5] < 2
		|| app->selected[2]))
		app->selected[2]
			= ft_toggle(app->selected[2]);
	if (check_mouse(screen_pos, (t_rect){166, 340, 32, 32})
		&& (app->selected[5] < 2
		|| app->selected[3]))
		app->selected[3]
			= ft_toggle(app->selected[3]);
	if (check_mouse(screen_pos, (t_rect){208, 340, 32, 32})
		&& (app->selected[5] < 2
		|| app->selected[4]))
		app->selected[4]
			= ft_toggle(app->selected[4]);
}

/**
 * Renders inventory related texts on the help menu sidebar.
*/
static void	render_inventory_texts(t_app *app)
{
	render_text(app, (t_point){10, 320}, "START INVENTORY");
	render_text(app, (t_point){185, 320},
		ft_itoa(app->selected[5]));
	render_text(app, (t_point){195, 320}, " / 2");
	change_font(app, 11, UI_FRAME);
	render_text(app, (t_point){58, 342}, ft_itoa(app->player.inventory.ammo));
	render_text(app, (t_point){105, 342},
		ft_itoa(app->player.inventory.potion));
	render_text(app, (t_point){147, 342},
		ft_itoa(app->player.inventory.antidote));
	render_text(app, (t_point){190, 342}, ft_itoa(app->player.inventory.key));
	render_text(app, (t_point){232, 342},
		ft_itoa(app->player.inventory.jetpack));
	change_font(app, 15, TEXT);
}

/**
 * Renders the start inventory to the help menu sidebar.
*/
void	render_inventory(t_app *app)
{
	int		index;

	render_icons(app, app->assets.sprite, (t_point){40, 340}, 5);
	index = 0;
	while (index < (INVENTORY_SIZE - 1))
	{
		if (app->selected[index])
		{
			render_ui_frame(app, (t_rect){(ICON_SIZE / 2) * (index + 1)
				+ (10 * (index + 1)) - 3, 339, 35, 35}, 1, 0);
		}
		index++;
	}
	app->player.inventory.ammo = 10
		* app->player.weapons[app->player.selected_weapon].magazine;
	render_inventory_texts(app);
}
