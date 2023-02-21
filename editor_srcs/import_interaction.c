/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:30:17 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/21 14:57:56 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Checks for valid sector ids.
 * 
 * @param app 
 * @param interaction 
 * @return t_bool 
 */
static t_bool	has_invalid_sector_ids(t_app *app,
	t_export_interaction *interaction)
{
	return (interaction->activation_sector < -1
		|| interaction->activation_sector >= app->sector_count
		|| interaction->target_sector < -1
		|| interaction->target_sector >= app->sector_count
		|| !sector_by_index(app, interaction->target_sector));
}

/**
 * @brief Validates interaction data.
 * 
 * @param app 
 */
static void	level_validation_interactions(t_app *app,
	t_export_interaction *interactions)
{
	t_sector_list	*sector;
	int				i;

	i = -1;
	while (++i < MAX_INTERACTIONS)
	{
		if (!interactions[i].event_id)
			continue ;
		if (has_invalid_sector_ids(app, &interactions[i])
			|| interactions[i].interaction_link < -1
			|| interactions[i].interaction_link >= MAX_INTERACTIONS
			|| interactions[i].activation_wall < -1
			|| interactions[i].activation_object < -1)
			exit_error(MSG_ERROR_IMPORT_INTERACTION);
		if (interactions[i].activation_object != -1
			|| interactions[i].activation_object >= MAX_OBJECTS)
			continue ;
		sector = sector_by_index(app, interactions[i].activation_sector);
		if (!sector || (sector->corner_count
				<= interactions[i].activation_wall - 1))
			exit_error(MSG_ERROR_IMPORT_INTERACTION);
	}
}

/**
 * @brief Get wall pointer by index.
 * 
 * @param sector 
 * @param index 
 * @return t_wall_list* 
 */
static t_wall_list	*line_by_index(t_sector_list *sector, int index)
{
	int			i;
	t_wall_list	*head;

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
		temp.interaction_link = interactions[i].interaction_link;
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
		temp.requires_key = interactions[i].requires_key;
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
	level_validation_interactions(app, (t_export_interaction *)&interactions);
	read_interactions(app, (t_export_interaction *)&interactions);
}
