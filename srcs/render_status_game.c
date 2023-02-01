/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status_game.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:51:22 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/01 16:43:41 by htahvana         ###   ########.fr       */
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
	progress_animations(app);
	update_hand(app);
	player_control(app);
	object_collision(app);
	update_enemy_states(app);
	update_bullets(app);
	bullet_enemy_collisions(app);
	bullet_player_collision(app);
	render_sectors(app);
	render_objects(app);
	render_textmodals(app);
	render_hand(app);
	render_ui(app);
	if (app->player.hp == 0)
		app->status = STATUS_GAMEOVER;
}
