/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:57:35 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/20 12:43:52 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Expands data pointer allocation.
 * 
 * @param data 
 * @param length 
 * @param allocated 
 */
void	expand_data(t_uint8 **data, int *length, int *allocated)
{
	int		new_size;
	t_uint8	*expanded;

	new_size = 2 * *allocated;
	if (new_size < *allocated + MAX_UNCOMPRESS_BATCH)
		new_size = *allocated + MAX_UNCOMPRESS_BATCH;
	expanded = (t_uint8 *)malloc(new_size);
	if (!expanded)
		exit_error(MSG_ERROR_ALLOC);
	ft_memcpy(expanded, *data, *length);
	if (*data)
		free(*data);
	*data = expanded;
	*allocated = new_size;
}

/**
 * @brief Reads source file into dynamically allocated pointer.
 * 
 * @param source 
 * @param source_length 
 * @return t_uint8* 
 */
t_uint8	*read_source(const char *source, int *source_length)
{
	t_uint8	*source_data;
	int		source_fd;
	int		allocated;
	int		read_bytes;

	source_fd = open(source, O_RDONLY);
	if (source_fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	allocated = 0;
	read_bytes = 1;
	source_data = NULL;
	*source_length = 0;
	while (read_bytes > 0)
	{
		while (allocated <= *source_length + MAX_UNCOMPRESS_BATCH)
			expand_data(&source_data, source_length, &allocated);
		read_bytes = read(source_fd, source_data + *source_length,
				MAX_UNCOMPRESS_BATCH);
		if (read_bytes < 0)
			exit_error(MSG_ERROR_FILE_READ);
		*source_length += read_bytes;
	}
	if (close(source_fd) < 0)
		exit_error(MSG_ERROR_FILE_CLOSE);
	return (source_data);
}
