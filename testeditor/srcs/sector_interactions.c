/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_interactions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:21:14 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/05 14:09:25 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Deletes all interactions from the sector given, including the walls' 
 * decor interactions. Sets all target sectors matching the deleted sector to
 * their activation sector.
*/
int	del_all_sector_interactions(t_app *app, t_sector_lst **sector)
{
	int		id;

	if (!(*sector))
		return (FALSE);
	id = 0;
	while (id < MAX_INTERACTIONS)
	{
		if (app->interactions[id].activation_sector == (*sector))
			delete_interaction(app, id);
		if (app->interactions[id].target_sector == (*sector))
			app->interactions[id].target_sector
				= app->interactions[id].activation_sector;
		id++;
	}
	return (TRUE);
}
