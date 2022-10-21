/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:33:06 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:33:37 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Changes the selected wall texture to given id
 * 
 * @param app 
 * @param wall 
 * @param wall_id 
 */
void	change_selected_wall_tex(t_app *app, t_vec2list *wall, int wall_id)
{
	(void)app;
	wall->wall_texture = wall_id;
}