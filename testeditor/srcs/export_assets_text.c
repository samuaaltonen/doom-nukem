/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_assets_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:02:41 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 21:04:16 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Exports texts.
 * 
 * @param info 
 * @param fd 
 */
void	export_texts(t_import_info *info, int fd)
{
	unsigned char	buffer[MAX_TEXT_LINES * MAX_TEXT_LINE_LENGTH];
	int				length;
	int				texts_fd;

	texts_fd = open(TEXTS_PATH, O_RDONLY);
	if (texts_fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	length = read(texts_fd, &buffer, MAX_TEXT_LINES * MAX_TEXT_LINE_LENGTH);
	if (length < 0)
		exit_error(MSG_ERROR_FILE_READ);
	info->header.asset_info[EXPORT_TEXTS].size = length;
	if (write(fd, &buffer, length) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	info->imported = 500;
	export_update_progress(info);
}
