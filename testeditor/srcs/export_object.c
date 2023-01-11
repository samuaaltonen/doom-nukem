/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:30:49 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 20:41:39 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Exports game objects.
 * 
 * @param app 
 * @param fd 
 */
void	export_objects(t_app *app, int fd)
{
	t_export_object	objects[MAX_OBJECTS];
	t_export_object	temp;
	int				i;

	ft_bzero(&objects, sizeof(t_export_object) * MAX_OBJECTS);
	i = 0;
	while (i < MAX_OBJECTS)
	{
		temp.pos = app->objects[i].position;
		if (app->objects[i].sector)
			temp.elevation = app->objects[i].sector->floor_height;
		else
			temp.elevation = 0.f;
		temp.sector = get_sector_id(app, app->objects[i].sector);
		temp.type = app->objects[i].type;
		temp.var = app->objects[i].var;
		objects[i] = temp;
		i++;
	}
	if (write(fd, objects, sizeof(t_export_object) * MAX_OBJECTS) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
}
