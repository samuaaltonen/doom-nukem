/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quickslots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:00:41 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/07 14:31:21 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	quickslot_cooldown(t_app *app, t_rect rect, char *amount,
				SDL_Surface *sprite);

void	hud_quickslot(t_app *app, t_rect rect, char *slot)
{
	SDL_Surface	*sprite;
	char		*amount;

	if (slot[0] == 'Q')
	{
		sprite = app->assets.hp;
		amount = ft_itoa(app->player.inventory.potion);
	}
	if (slot[0] == 'E')
	{
		sprite = app->assets.shield;
		amount = ft_itoa(app->player.inventory.armor_pack);
	}
	if (!check_timer(&app->item_timer))
		slot = ft_itoa((int)(app->item_timer.seconds
					- app->item_timer.delta_seconds));
	if (!slot || !amount || !sprite)
		exit_error(MSG_ERROR_ALLOC);
	render_text_prompt(app, rect, 1, slot);
	if (slot[0] != 'Q' && slot[0] != 'E')
		free(slot);
	if (check_timer(&app->item_timer))
		quickslot_cooldown(app, rect, amount, sprite);
	free(amount);
}

static void	quickslot_cooldown(t_app *app, t_rect rect, char *amount,
		SDL_Surface *sprite)
{
	rect = (t_rect){rect.x + 8, rect.y + 32, rect.w / 3, rect.h / 3};
	render_ui_element(app, sprite, rect);
	rect = (t_rect){rect.x + 32, rect.y + 6, rect.w * 3, rect.h * 3};
	render_text(app, rect, amount);
}
