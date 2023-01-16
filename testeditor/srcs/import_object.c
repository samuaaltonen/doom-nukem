/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:30:44 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 19:30:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Imports objects.
 * 
 * @param app 
 * @param info 
 */
void	import_objects(t_app *app, t_import_info *info)
{
	t_export_object	objects[MAX_OBJECTS];
	t_object		temp;
	int				i;

	if (sizeof(t_export_object) * MAX_OBJECTS
		> (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_OBJECT);
	ft_memcpy(&objects, info->data + info->imported,
		sizeof(t_export_object) * MAX_OBJECTS);
	info->imported += (int) sizeof(t_export_object) * MAX_OBJECTS;
	i = -1;
	while (++i < MAX_OBJECTS)
	{
		temp.position = objects[i].pos;
		if (objects[i].sector < 0 || objects[i].sector >= app->sector_count)
			exit_error(MSG_ERROR_IMPORT_OBJECT);
		temp.sector = sector_by_index(app, objects[i].sector);
		temp.type = objects[i].type;
		if (!temp.sector || temp.type < 0 || temp.type > MAX_SMALL_OBJECTS
			+ MAX_BIG_OBJECTS + MAX_ENEMY_TYPES)
			exit_error(MSG_ERROR_IMPORT_OBJECT);
		temp.var = objects[i].var;
		(app->objects[i]) = temp;
	}
}
