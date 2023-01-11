/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_assets_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:47:29 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 18:52:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Imports text data.
 * 
 * @param app 
 * @param thread 
 * @param info 
 */
void	import_texts(t_app *app, t_thread_data *thread, t_import_info *info)
{
	t_export_asset	asset_info;
	char			buffer[MAX_TEXT_LINES * MAX_TEXT_LINE_LENGTH + 1];
	int				i;

	asset_info = info->header.asset_info[EXPORT_TEXTS];
	if (asset_info.size > info->length - info->imported)
		exit_error(MSG_ERROR_IMPORT_TEXT);
	ft_memcpy(&buffer, info->data + info->imported,
		asset_info.size);
	app->texts = ft_strsplit((char *)buffer, '\n');
	i = 0;
	while (app->texts[i])
	{
		app->text_lengths[i] = ft_strlen(app->texts[i]);
		i++;
	}
	import_update_progress(app, thread, info);
}
