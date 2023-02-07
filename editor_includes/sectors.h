/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:00:44 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/07 18:34:46 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTORS_H
# define SECTORS_H
# define MAX_SECTOR_COUNT 4096

typedef struct s_wall_list
{
	t_vector2			point;
	int					type;
	int					tex;
	int					decor;
	t_vector2			decor_offset;
	struct s_wall_list	*next;
}	t_wall_list;

typedef struct s_sector_list
{
	int					corner_count;
	t_wall_list			*wall_list;
	struct s_sector_list	*member_sectors[MAX_MEMBER_SECTORS];
	int					member_links[MAX_MEMBER_SECTORS];
	struct s_sector_list	*parent_sector;
	int					light;
	double				floor_height;
	double				ceil_height;
	int					floor_tex;
	int					floor_tex_offset;
	int					ceil_tex;
	int					ceil_tex_offset;
	t_wall_list			*floor_slope_wall;
	t_wall_list			*floor_slope_opposite;
	double				floor_slope_height;
	t_wall_list			*ceil_slope_wall;
	t_wall_list			*ceil_slope_opposite;
	double				ceil_slope_height;
	struct s_sector_list	*next;
}	t_sector_list;

typedef struct s_template
{
	double				ceil_height;
	double				floor_height;
	int					ceil_tex;
	int					floor_tex;
	int					wall_tex;
	int					light;
}	t_template;

#endif