/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:39:35 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/27 15:45:19 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

int	blend_pixel_half(t_colors base, t_colors top)
{
	t_colors	color;

	color.b = base.b / 2 + top.b / 2;
	color.g = base.g / 2 + top.g / 2;
	color.r = base.r / 2 + top.r / 2;
	color.a = 255;
	return (color.color);
}