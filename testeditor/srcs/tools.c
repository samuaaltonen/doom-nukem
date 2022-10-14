/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:27:15 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/14 16:50:12 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void	change_all_wall_tex(t_vec2list *walls, int wall_tex)
{
	t_vec2list *tmp;

	tmp = walls;
	while(tmp)
	{
		tmp->wall_texture = wall_tex;
		tmp = tmp->next;
		if(tmp == walls)
			break;
	}
}