/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:45:59 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/01 16:46:26 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

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
