/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:57:03 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/05 18:45:03 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Loads text strings into text string array.
 * 
 * @param app 
 */
void	load_texts(t_app *app)
{
	int		fd;
	char	buffer[MAX_TEXT_LINES * MAX_TEXT_LINE_LENGTH + 1];
	ssize_t	count;

	fd = open(TEXTS_PATH, O_RDONLY, 0755);
	if(fd < 0)
		exit_error(MSG_ERROR_FILE_READ);
	count = read(fd, &buffer, MAX_TEXT_LINES * MAX_TEXT_LINE_LENGTH);
	if (count == -1)
		exit_error(MSG_ERROR_FILE_READ);
	buffer[count] = 0;
	app->texts = ft_strsplit((char *)buffer, '\n');
}