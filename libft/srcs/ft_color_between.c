/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_between.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:05:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/01/28 11:50:25 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_red(int i)
{
	return ((i >> 16) & 255);
}

static int	get_green(int i)
{
	return ((i >> 8) & 255);
}

static int	get_blue(int i)
{
	return (i & 255);
}

/* 
 * Gets color value in between 2 colors. Pos should be from 0 to 1
 * For example ft_color_between(0.5, 0xFFFFFF, 0x000000) = 0x7F7F7F
*/
int	ft_color_between(float pos, int start, int end)
{
	int	red;
	int	green;
	int	blue;

	if (pos < 0)
		pos = 0;
	if (pos > 1)
		pos = 1;
	red = (get_red(end) - get_red(start)) * pos + get_red(start);
	green = (get_green(end) - get_green(start)) * pos + get_green(start);
	blue = (get_blue(end) - get_blue(start)) * pos + get_blue(start);
	return (ft_rgbtoint(red, green, blue));
}
