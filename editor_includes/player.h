/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:58:29 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/07 18:34:46 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_weapon
{
	t_bool			enabled;
	int				damage;
	int				range;
	int				fire_rate;
	int				magazine;
}	t_weapon;

typedef struct s_inventory
{
	int				ammo;
	int				special_ammo;
	int				potion;
	int				armor_pack;
	int				key;
	t_bool			jetpack;
}	t_inventory;

typedef struct s_player
{
	t_vector2		position;
	t_vector2		direction;
	t_sector_list	*sector;
	int				health;
	int				selected_weapon;
	int				selected_armor;
	t_weapon		weapons[MAX_WEAPONS];
	int				armor;
	t_inventory		inventory;
}	t_player;

#endif