/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:30:42 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/12 16:25:54 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Copies interaction data into exportable format.
 * 
 * @param app 
 * @param interactions 
 */
static void	write_interactions(t_app *app, t_export_interaction *interactions)
{
	t_export_interaction	temp;
	int						i;

	i = -1;
	while (++i < MAX_INTERACTIONS)
	{
		temp.activation_object = get_object_id(app,
				app->interactions[i].activation_object);
		temp.activation_sector = get_sector_id(app,
				app->interactions[i].activation_sector);
		if (temp.activation_sector != -1
			&& app->interactions[i].activation_wall)
			temp.activation_wall = get_wall_id(
					app->interactions[i].activation_sector->wall_list,
					app->interactions[i].activation_wall);
		else
			temp.activation_wall = -1;
		temp.event_id = app->interactions[i].event_id;
		temp.target_sector = get_sector_id(app,
				app->interactions[i].target_sector);
		temp.variable = app->interactions[i].variable;
		temp.editable = app->interactions[i].editable;
		temp.requires_key = app->interactions[i].requires_key;
		interactions[i] = temp;
	}
}

/**
 * @brief Exports game interactions.
 * 
 * @param app 
 * @param fd 
 */
void	export_interactions(t_app *app, int fd)
{
	t_export_interaction	interactions[MAX_INTERACTIONS];

	ft_bzero(&interactions, sizeof(t_export_interaction) * MAX_INTERACTIONS);
	write_interactions(app, (t_export_interaction *)&interactions);
	if (write(fd, interactions,
			sizeof(t_export_interaction) * MAX_INTERACTIONS) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
}
