/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:16:26 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/24 16:45:09 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Imports interaction data.
 * 
 * @param app 
 * @param data 
 * @param available 
 * @return int 
 */
void	import_interactions(t_app *app, t_import_info *info)
{
	if (sizeof(t_interaction) * MAX_INTERACTIONS
		> (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_INTERACTION);
	ft_memcpy(app->interactions, info->data + info->imported,
		sizeof(t_interaction) * MAX_INTERACTIONS);
	info->imported += (int) sizeof(t_interaction) * MAX_INTERACTIONS;
	app->animation_count = 0;
	ft_bzero(&app->animations, sizeof(app->animations));
	import_update_progress(info);
}
