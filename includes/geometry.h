
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:48:59 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/19 15:19:06 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "doomnukem.h"

# define DEG_IN_RADIAN 0.01745
# define RADIAN_IN_DEG 57.29578
# define PI_HALF 1.57079632679
# define PI_3_QUARTERS 2.35619449019

/**
 * Struct for integer coordinate point.
 */
typedef struct s_point
{
	int				x;
	int				y;
}	t_point;

/**
 * Matrix that contains 2 t_point columns.
 */
typedef	struct s_point_matrix
{
	t_point			a;
	t_point			b;
}	t_point_matrix;


/**
 * Struct for integer coordinate rectangule.
 */
typedef struct s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
}	t_rect;

/**
 * Polygons GOING TO BE REMOVED SOON
*/
typedef struct s_polygon_hit
{
	int		y_first_top;
	int		y_second_top;
	int		y_first_bottom;
	int		y_second_bottom;
	double	distance_first;
	double	distance_second;
}	t_polygon_hit;

typedef struct s_polygon
{
	t_vector2		corners[MAX_POLYGON_CORNERS];
	int				corner_count;
	double			bottom;
	double			top;
	int				texture;
	t_polygon_hit	*hits;
}	t_polygon;

#endif
