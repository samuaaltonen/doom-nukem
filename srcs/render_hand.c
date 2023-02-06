/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:47:59 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/01 19:42:56 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	hand_init(t_app *app)
{
	app->hand.target = (t_vector2){WIN_W / 2 - WEAPON_SIZE / 2, WIN_H / 4};
	app->hand.current = app->hand.target;
	app->hand.velocity = (t_vector2){0.f, 0.f};
	app->wave = 0.f;
}

void	add_fire_movement(t_app *app)
{
	app->hand.velocity = ft_vector2_add(app->hand.velocity,
			(t_vector2){0, HAND_FIRE_SPEED});
}

static void	add_player_movement(t_app *app, double *angle_sin,
		double *angle_cos)
{
	double	angle;

		angle = ft_vector_angle_left(app->player.dir, app->player.move_vector);
	if (angle < M_PI)
		angle = -angle;
	else
		angle = M_PI - (angle - M_PI);
	if (!app->player.flying)
	{
		*angle_cos = cos(angle) * ft_vector_length(app->player.move_vector)
			+ sin(app->wave * 2) * ft_vector_length(app->player.move_vector);
		*angle_sin = sin(angle) * ft_vector_length(app->player.move_vector)
			+ sin(app->wave) * ft_vector_length(app->player.move_vector);
	}
	else
	{
		*angle_cos = cos(angle) * ft_vector_length(app->player.move_vector);
		*angle_sin = sin(angle) * ft_vector_length(app->player.move_vector);
	}
}

void	update_hand(t_app *app)
{
	t_hand	*hand;
	double	angle_sin;
	double	angle_cos;

	hand = &app->hand;
	app->wave += 10 * app->conf->delta_time;
	if (app->wave >= PI_PI)
		app->wave = fmod(app->wave, PI_PI);
	hand->velocity = ft_vec2_mult(
			ft_vector2_sub(hand->target, hand->current), HAND_SPEED);
	add_player_movement(app, &angle_sin, &angle_cos);
	hand->velocity = ft_vector2_add(hand->velocity,
			ft_vector2_add(ft_vec2_mult((t_vector2){-angle_sin,
					angle_cos * 0.5f + app->player.elevation_velocity},
					HAND_MOVE_SPEED),
				(t_vector2){-app->mouse_delta.x * HAND_TURN_SPEED,
				-app->mouse_delta.y * HAND_TURN_SPEED}));
}

void	render_hand(t_app *app)
{
	t_rect	dst;
	t_rect	src;

	if(app->status == STATUS_GAME)
		app->hand.current = ft_vector2_add(app->hand.current,
			ft_vec2_mult(app->hand.velocity, app->conf->delta_time));
	rect_from_surface(app->assets.weapon[app->hand.equipped], &src);
	dst.x = app->hand.current.x;
	dst.y = app->hand.current.y;
	dst.w = WEAPON_SIZE;
	dst.h = WEAPON_SIZE;
	blit_surface(app->assets.weapon[app->hand.equipped],
			&src, app->surface, &dst);
	app->mouse_delta = (t_point){0, 0};
}
