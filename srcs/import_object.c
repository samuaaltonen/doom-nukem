/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:17:07 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/21 16:18:24 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Imports object data.
 * 
 * @param app 
 * @param data 
 * @param available 
 * @return int 
 */
void	import_objects(t_app *app, t_import_info *info)
{
	t_object	import;
	int			i;

	if (sizeof(t_object) * MAX_OBJECTS
		>= (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_OBJECT);
	i = -1;
	while (++i < MAX_OBJECTS)
	{
		ft_memcpy(&import, info->data + info->imported, sizeof(t_object));
		info->imported += sizeof(t_object);
		app->objects[i].position = import.position;
		app->objects[i].sector = import.sector;
		app->objects[i].elevation = sector_floor_height(app, import.sector,
				import.position);
		app->objects[i].type = import.type;
		app->objects[i].var = import.var;
		app->objects[i].rot = ft_random_double(app, PI_PI);
	}
	init_bullets(app);
	import_update_progress(info);
}
