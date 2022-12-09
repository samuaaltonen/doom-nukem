 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/11 14:11:58 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Checks wall collisions for given position.
 */
static int	is_collision(t_app *app, t_vector2 pos)
{
	(void)app;
	(void)pos;
	/* if (pos.x >= app->map_size.x || pos.y >= app->map_size.y)
		return (1);
	if (pos.x < 0 || pos.y < 0)
		return (1);
	if (app->map[(int)pos.y][(int)pos.x][0] > 'A'
		&& app->map[(int)pos.y][(int)pos.x][0] != DOOR_MAP_ID_MOVING)
		return (1); */
	return (0);
}

static t_bool	is_wall_collision(t_app *app, t_move new)
{
	int	i;
	int	wall_id;

	i = 0;
	while (i < app->sectors[app->player.current_sector].corner_count)
	{
		if(ft_line_side(get_wall_line(app, app->player.current_sector,i), new.pos) != 0)
		{
			/**
			 * Quick fix for portals that are parallel to other walls.
			 * TODO: Remove this
			 */
			t_line line = get_wall_line(app, app->player.current_sector,i);
			if (ft_vector_length(ft_vector2_sub(app->player.pos, app->sectors[app->player.current_sector].corners[i])) > ft_vector_length(ft_vector2_sub(line.a, line.b)))
			{
				i++;
				continue ;
			}

			wall_id = app->sectors[app->player.current_sector].wall_types[i];
			if(wall_id < 0 || (new.elevation + 0.2f < app->sectors[wall_id].floor_height ||
				app->sectors[wall_id].ceil_height - app->sectors[wall_id].floor_height < 0.6f))
				return (FALSE);
			else
			{
				if (app->sectors[app->player.current_sector].wall_textures[i] == PARTIALLY_TRANSPARENT_PORTAL_TEXTURE_ID)
					return (FALSE);
				app->player.current_sector = wall_id;
				return (TRUE);
			}
		}
		i++;
	}
	return (TRUE);

}

/**
 * Updates player's position if possible.
 */
static void	update_position(t_app *app, t_vector2 new)
{
	if(!is_wall_collision(app, (t_move){new, app->player.elevation}))
		return ;
	if (!is_collision(app, (t_vector2){new.x - COLLISION_OFFSET,
			app->player.pos.y - COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){new.x - COLLISION_OFFSET,
			app->player.pos.y + COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){new.x + COLLISION_OFFSET,
			app->player.pos.y - COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){new.x + COLLISION_OFFSET,
			app->player.pos.y + COLLISION_OFFSET}))
		app->player.pos.x = new.x;
	if (!is_collision(app, (t_vector2){app->player.pos.x - COLLISION_OFFSET,
			new.y - COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){app->player.pos.x - COLLISION_OFFSET,
			new.y + COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){app->player.pos.x + COLLISION_OFFSET,
			new.y - COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){app->player.pos.x + COLLISION_OFFSET,
			new.y + COLLISION_OFFSET}))
		app->player.pos.y = new.y;
}

/**
 * Moves player to given direction if there is no collision.
 */
void	player_move(t_app *app, t_movement movement, double speed)
{
	t_vector2	perpendicular;
	t_vector2	new;

	if (!(movement == FORWARD || movement == BACKWARD
			|| movement == LEFTWARD || movement == RIGHTWARD 
			|| movement == UPWARD || movement == DOWNWARD))
		return ;
	new = app->player.pos;
	if (movement == FORWARD)
		new = (t_vector2){app->player.pos.x + app->player.dir.x * speed,
			app->player.pos.y + app->player.dir.y * speed};
	if (movement == BACKWARD)
		new = (t_vector2){app->player.pos.x - app->player.dir.x * speed,
			app->player.pos.y - app->player.dir.y * speed};
	if (movement == LEFTWARD || movement == RIGHTWARD)
	{
		perpendicular = ft_vector_perpendicular(app->player.dir);
		if (movement == LEFTWARD)
			new = (t_vector2){app->player.pos.x - perpendicular.x * speed,
				app->player.pos.y - perpendicular.y * speed};
		if (movement == RIGHTWARD)
			new = (t_vector2){app->player.pos.x + perpendicular.x * speed,
				app->player.pos.y + perpendicular.y * speed};
	}
	//----DEBUG FLY
	if (movement == UPWARD)
	{
		app->player.elevation += speed;
		new = (t_vector2){app->player.pos.x, app->player.pos.y};
	}

	if (movement == DOWNWARD)
	{
		app->player.elevation -= speed;
		new = (t_vector2){app->player.pos.x, app->player.pos.y};
	}
	//----
	update_position(app, new);
}

void	heal(t_app *app)
{
	if (app->player.inventory.potion > 0)
	{
		app->player.inventory.potion--;
		app->player.hp += 40;
	}
}

void	shield(t_app *app)
{
	if (app->player.inventory.antidote > 0)
	{
		app->player.inventory.antidote--;
		app->player.shield = MAX_HP;
	}
}

void	regen(t_app *app, int *value)
{
	if (check_timer(&app->timer) && *value % 40 != 0)
			(*value)++;

}

void	damage(t_app *app, int dmg)
{	
	int	to_shield;
	int	to_hp;

	to_shield = (dmg * app->player.shield) / MAX_HP;
	if (to_shield < dmg / 5)
		to_shield = dmg / 5;
	to_hp = dmg - to_shield;
	app->player.shield -= to_shield;
	if (app->player.shield < 0)
		app->player.shield = 0;
	app->player.hp -= to_hp;
	if (app->player.hp < 0)
		app->player.hp = 0;
		start_timer(&app->timer, 5);
}
