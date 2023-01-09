/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:00:44 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/05 13:02:38 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTORS_H
# define SECTORS_H

typedef struct s_vec2_lst
{
	t_vector2			point;
	int					type;
	int					tex;
	int					decor;
	t_vector2			decor_offset;
	struct s_vec2_lst	*next;
}	t_vec2_lst;

typedef struct s_sectorlist
{
	int					corner_count;
	t_vec2_lst			*wall_list;
	struct s_sectorlist	*member_sectors[MAX_MEMBER_SECTORS];
	int					member_links[MAX_MEMBER_SECTORS];
	struct s_sectorlist	*parent_sector;
	int					light;
	double				floor_height;
	double				ceil_height;
	int					floor_tex;
	int					floor_tex_offset;
	int					ceil_tex;
	int					ceil_tex_offset;
	t_vec2_lst			*floor_slope_wall;
	t_vec2_lst			*floor_slope_opposite;
	double				floor_slope_height;
	t_vec2_lst			*ceil_slope_wall;
	t_vec2_lst			*ceil_slope_opposite;
	double				ceil_slope_height;
	struct s_sectorlist	*next;
}	t_sector_lst;

#endif