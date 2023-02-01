/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fill_sector_points_sort.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:55:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/01 17:16:23 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Set wall angles compared to the first wall.
 * 
 * @param array 
 * @param count 
 * @param angles 
 */
static void	set_angles(t_vector2 *array, int *count, double *angles)
{
	int		i;

	i = 0;
	while (i < *count)
	{
		if (array[i].y < array[0].y
			|| (array[i].y == array[0].y && array[i].x >= array[0].x))
			ft_vec2_swap(&(array[0]), &(array[i]));
		i++;
	}
	i = 0;
	angles[0] = 0.f;
	while (i < *count)
	{
		angles[i] = ft_vector_angle((t_vector2){-1.f, 0.f},
				ft_vector2_sub(array[i], array[0]));
		i++;
	}
}

/**
 * @brief Sorts point array.
 * 
 * @param array 
 * @param count 
 */
void	sort_point_array(t_vector2 *array, int *count)
{
	double		angles[MAX_SECTOR_CORNERS + 4];
	int			i;
	int			k;

	set_angles(array, count, (double *)&angles);
	i = -1;
	while (++i < *count - 1)
	{
		k = -1;
		while (++k < *count - i - 1)
		{
			if (angles[k] > angles[k + 1])
			{
				ft_double_swap(&(angles[k]), &(angles[k + 1]));
				ft_vec2_swap(&(array[k]), &(array[k + 1]));
			}
			else if (angles[k] == 0.f && angles[k] == angles[k + 1]
				&& array[k].x < array[k + 1].x)
				ft_vec2_swap(&(array[k]), &(array[k + 1]));
		}
	}
}
