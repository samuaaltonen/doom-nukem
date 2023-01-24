/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status_game.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:51:22 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/24 15:51:35 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Renders the game.
 * 
 * @param app 
 */
void	render_game(t_app *app)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	update_enemy_states(app);
	update_bullets(app);
	progress_animations(app);
	player_control(app);
	object_collision(app);
	bullet_enemy_collisions(app);
	bullet_player_collision(app);
	render_sectors(app);
	render_objects(app);
	render_textmodals(app);
	render_hand(app, WIN_W / 2 - 256, 320);
	render_ui(app);
	if (app->player.hp == 0)
		app->status = STATUS_GAMEOVER;
}
