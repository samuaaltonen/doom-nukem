/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:26:23 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/01 19:26:39 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Changes font color and size.
 * 
 * @param app 
 * @param size 
 * @param color 
 */
void	change_font(t_app *app, int size, int color)
{
	app->assets.font.size = size;
	color_surface(app->assets.font.font, color);
}
