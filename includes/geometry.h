/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:48:59 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/08 16:15:30 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# define DEG_IN_RADIAN 0.01745
# define RADIAN_IN_DEG 57.29578
# define PI_HALF 1.57079632679
# define PI_3_QUARTERS 2.35619449019

/**
 * Sturct for limits.
 */
typedef struct s_limit
{
	int				start;
	int				end;
}	t_limit;

/**
 * Matrix that contains 2 t_point columns.
 */
typedef struct s_point_matrix
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

#endif
