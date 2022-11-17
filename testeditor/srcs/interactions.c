/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:39 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/17 17:39:06 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void link_interaction(t_app *app)
{
	if(app->interaction_select == FALSE)
	{
		app->interaction_select = TRUE;
	}
	if(app->object_edit && app->objects[app->object_type].type != 0)
	{
		//object
	}
	else if(app->active_sector)
	{
		if(app->active)
		{
			//wall decor
		}
		else
		{
			//sector
		}
	}
}
