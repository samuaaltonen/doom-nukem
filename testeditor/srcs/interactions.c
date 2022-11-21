/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:39 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/21 13:26:51 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void new_interaction(t_app *app)
{
	(void)app;
}

void link_interaction(t_app *app)
{
	if(app->interaction_select == FALSE)
	{
		app->interaction_select = TRUE;
		new_interaction(app);
		if(app->object_menu)
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
	else
	{
		//set interaction target
	}
	
}
