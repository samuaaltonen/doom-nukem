/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:30:17 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/12 14:32:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Get wall pointer by index.
 * 
 * @param sector 
 * @param index 
 * @return t_vec2_lst* 
 */
static t_vec2_lst	*line_by_index(t_sector_lst *sector, int index)
{
	int			i;
	t_vec2_lst	*head;

	i = 0;
	if (!sector || index == -1)
		return (NULL);
	head = sector->wall_list;
	while (i < MAX_SECTOR_CORNERS)
	{
		if (i == index)
			return (head);
		head = head->next;
		i++;
	}
	return (NULL);
}

/**
 * @brief Copies interaction data to main interaction array.
 * 
 * @param app 
 * @param interactions 
 */
static void	read_interactions(t_app *app, t_export_interaction *interactions)
{
	t_interaction	temp;
	int				i;

	i = -1;
	while (++i < MAX_INTERACTIONS)
	{
		temp.event_id = interactions[i].event_id;
		if (temp.event_id)
			app->interaction_count++;
		temp.variable = interactions[i].variable;
		temp.editable = interactions[i].editable;
		temp.activation_sector = sector_by_index(app,
				interactions[i].activation_sector);
		temp.activation_wall = line_by_index(temp.activation_sector,
				interactions[i].activation_wall);
		if (interactions[i].activation_object == -1)
			temp.activation_object = NULL;
		else
			temp.activation_object
				= &(app->objects[interactions[i].activation_object]);
		temp.target_sector = sector_by_index(app,
				interactions[i].target_sector);
		app->interactions[i] = temp;
	}
}

/**
 * @brief Imports interactions.
 * 
 * @param app 
 * @param info 
 */
void	import_interactions(t_app *app, t_import_info *info)
{
	t_export_interaction	interactions[MAX_INTERACTIONS];

	if (sizeof(t_export_interaction) * MAX_INTERACTIONS
		> (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_INTERACTION);
	ft_memcpy(&interactions, info->data + info->imported,
		sizeof(t_export_interaction) * MAX_INTERACTIONS);
	info->imported += (int) sizeof(t_export_interaction) * MAX_INTERACTIONS;
	read_interactions(app, (t_export_interaction *)&interactions);
}
