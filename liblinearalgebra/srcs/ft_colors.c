/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:39:35 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/27 18:26:17 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

int	blend_pixel_half(t_colors base, t_colors top)
{
	t_colors	color;

	color.s_bgra.b = base.s_bgra.b / 2 + top.s_bgra.b / 2;
	color.s_bgra.g = base.s_bgra.g / 2 + top.s_bgra.g / 2;
	color.s_bgra.r = base.s_bgra.r / 2 + top.s_bgra.r / 2;
	color.s_bgra.a = 255;
	return (color.color);
}
