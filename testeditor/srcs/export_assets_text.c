/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_assets_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:02:41 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 20:03:31 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Exports textfile.
 * 
 * @param header 
 * @param index 
 * @param fd 
 * @param path 
 */
void	export_texts(t_level_header *header, int fd)
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
	header->asset_info[EXPORT_TEXTS].size = length;
	if (write(fd, &buffer, length) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
}
