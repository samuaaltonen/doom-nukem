/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_uncompress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:11:34 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/06 00:18:05 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void	write_sequence(unsigned char **data, int *length, unsigned char byte,
	t_uint8 count)
{
	t_uint8	i;

	i = 0;
	while (i < count)
	{
		(*data)[*length + i] = byte;
		i++;
	}
	*length += i;
}

void	expand_data(unsigned char **data, int *length, int *allocated)
{
	int				new_size;
	unsigned char	*expanded;

	new_size = 2 * *allocated;
	if (new_size < MAX_UNCOMPRESSION_BATCH_SIZE)
		new_size = MAX_UNCOMPRESSION_BATCH_SIZE;
	expanded = (unsigned char *)malloc(new_size);
	if (!expanded)
		exit_error(MSG_ERROR_ALLOC);
	ft_memcpy(expanded, *data, *length);
	if (*data)
		free(*data);
	*data = expanded;
	*allocated = new_size;
}

void	rle_uncompress(const char *source, unsigned char **data, int *length)
{
	unsigned char	buffer[MAX_COMPRESSION_BATCH_SIZE];
	int				i;
	int				read_bytes;
	int				source_fd;
	int				allocated;

	source_fd = open(source, O_RDONLY | O_CREAT, 0755);
	if (source_fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	allocated = 0;
	*length = 0;
	while (TRUE)
	{
		read_bytes = read(source_fd, &buffer, MAX_COMPRESSION_BATCH_SIZE);
		if (read_bytes < 0)
			exit_error(MSG_ERROR_FILE_READ);
		if (!read_bytes)
			break ;
		ft_printf("Read %d bytes\n", read_bytes);
		i = 0;
		while (i < read_bytes)
		{
			if (i < read_bytes - 2 && buffer[i] == buffer[i + 1]
				&& *length % MAX_UNCOMPRESSION_BATCH_SIZE
					< MAX_UNCOMPRESSION_BATCH_SIZE - 3)
			{
				while (allocated <= *length + buffer[i + 2])
					expand_data(data, length, &allocated);
				write_sequence(data, length, buffer[i], buffer[i + 2]);
				i += 3;
				continue ;
			}
			while (allocated <= *length)
				expand_data(data, length, &allocated);
			(*data)[*length] = buffer[i];
			*length += 1;
			i++;
		}
	}
}
