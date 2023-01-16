/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_assets_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:47:29 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 13:42:31 by saaltone         ###   ########.fr       */
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
void	import_texts(t_app *app, t_import_info *info)
{
	t_export_asset	asset_info;
	char			buffer[MAX_TEXT_LINES * MAX_TEXT_LINE_LENGTH + 1];
	int				i;

	ft_bzero(&buffer, MAX_TEXT_LINES * MAX_TEXT_LINE_LENGTH + 1);
	asset_info = info->header.asset_info[EXPORT_TEXTS];
	if (asset_info.size > info->length - info->imported
		|| asset_info.size > MAX_TEXT_LINES * MAX_TEXT_LINE_LENGTH)
		exit_error(MSG_ERROR_IMPORT_TEXT);
	ft_memcpy(&buffer, info->data + info->imported,
		asset_info.size);
	if (ft_strchr_count((char *)buffer, '\n') >= MAX_TEXT_LINES)
		exit_error(MSG_ERROR_IMPORT_TEXT);
	app->texts = ft_strsplit((char *)buffer, '\n');
	i = 0;
	while (app->texts[i])
	{
		app->text_lengths[i] = ft_strlen(app->texts[i]);
		i++;
	}
	import_update_progress(info);
}
