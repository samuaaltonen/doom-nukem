/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_equipment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:40:28 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/10 17:44:13 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	hud_keys(t_app *app, t_rect area);
static void	hud_jetpack(t_app *app, t_rect area);
static void	hud_weapon(t_app *app, t_rect rect);
static void	choose_weapon_sprite (t_app *app);

void	render_equipment(t_app *app)
{
	hud_quickslot(app, (t_rect){960, 624, 64, 64}, "Q");
	hud_quickslot(app, (t_rect){1040, 624, 64, 64}, "E");
	hud_weapon(app, (t_rect){1120, 592, 128, 96});
	hud_jetpack(app, (t_rect){860, 592, 96, 96});
	hud_keys(app, (t_rect){960, 544, 32, 32});
}

static void	hud_keys(t_app *app, t_rect area)
{
	t_rect	src;
	char	*key_str;
	int		i;

	src.x = 0;
	src.y = 128;
	src.w = 128;
	src.h = 128;
	key_str = ft_itoa(app->player.inventory.key);
	i = app->player.inventory.key;
	if (i > 7)
	{
		i = 7;
		render_text_prompt(app, (t_rect){1208, area.y, 40, 32}, 1, key_str);
	}
	while (i > 0)
	{
		blit_surface(app->assets.object_icon, &src, app->surface, &area);
		area.x += 34;
		i--;
	}
	free(key_str);
}

static void	hud_jetpack(t_app *app, t_rect area)
{
	t_rect	src;

	src.x = 0;
	src.y = 128 * 4;
	src.w = 128;
	src.h = 128;
	if (app->player.inventory.jetpack)
		blit_surface(app->assets.object_icon, &src, app->surface, &area);
}

static void	hud_weapon(t_app *app, t_rect rect)
{
	int		i;
	char	*ammo;

	i = 0;
	render_ui_frame(app, rect, 1, DARK_GREY);
//	render_ui_element(app, app->assets.pistol, (t_rect){1152, 630, 64, 64});
	choose_weapon_sprite(app);
	rect.x += 16;
	rect.y += 16;
	rect.w = 4;
	rect.h = 8;
	while (i < app->player.equipped_weapon.magazine)
	{
		color_surface(app->assets.bullet, CYAN);
		if (i >= app->player.equipped_weapon.ammo)
			color_surface(app->assets.bullet, GREY);
		render_ui_element(app, app->assets.bullet, rect);
		rect.x += 6;
		i++;
	}
	ammo = ft_itoa(app->player.inventory.ammo);
	if (!ammo)
		return ;
	render_text(app, (t_rect){1136, 626, 64, 64}, ammo);
	free(ammo);
}

static void choose_weapon_sprite(t_app *app)
{
	t_rect	src;
	t_rect	dst;

	dst = (t_rect){1152, 630, 64, 64};
	printf("%d \n", app->hand.equipped);
	if (app->hand.equipped == 1)
		src = (t_rect){0, 128 * 5, 128, 128};
	else if (app->hand.equipped == 2)
		src = (t_rect){0, 128 * 6, 128, 128};
	else if (app->hand.equipped == 3)
		src = (t_rect){0, 128 * 7, 128, 128};
	else
 		src = (t_rect){0, 0, 0, 0};
	blit_surface(app->assets.object_icon, &src, app->surface, &dst);
}