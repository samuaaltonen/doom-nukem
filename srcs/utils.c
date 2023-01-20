/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:48:10 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/20 11:28:33 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Maps the point given from the source rectangle to the appropiate 
 * coordinates on the destination rectangle.
 * 
 * @param src 
 * @param dst 
 * @param point 
 */
void	map_coordinates(t_rect *src, t_rect *dst, t_point *point)
{
	point->x = point->x * ((float)dst->w / (float)src->w) + dst->x;
	point->y = point->y * ((float)dst->h / (float)src->h) + dst->y;
}

/**
 * @brief Clamps given number to the range from min to max.
 * 
 * @param number 
 * @param min 
 * @param max 
 */
void	clamp_int(int *number, int min, int max)
{
	if (*number < min)
		*number = min;
	if (*number > max)
		*number = max;
}
