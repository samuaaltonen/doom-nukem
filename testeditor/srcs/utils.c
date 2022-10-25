/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:48:10 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/25 11:25:35 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void	map_coordinates(t_rect *src, t_rect *dst, t_point *point)
{
	point->x = point->x * ((float)dst->w / (float)src->w) + dst->x;
	point->y = point->y * ((float)dst->h / (float)src->h) + dst->y;
}
