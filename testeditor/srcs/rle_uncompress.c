/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_uncompress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:11:34 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/06 13:00:56 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Writes RLE compressed sequence as uncompressed byte sequence to data
 * pointer.
 * 
 * @param data 
 * @param length 
 * @param source_data 
 * @param index 
 */
void	write_sequence(unsigned char **data, int *length,
	unsigned char *source_data, int *index)
{
	t_uint8	i;

	i = 0;
	while (i < source_data[*index + 2])
	{
		(*data)[*length + i] = source_data[*index];
		i++;
	}
	*length += i;
	*index += 3;
}

/**
 * @brief Expands data pointer allocation.
 * 
 * @param data 
 * @param length 
 * @param allocated 
 */
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

/**
 * @brief Reads source file into dynamically allocated pointer.
 * 
 * @param source 
 * @param source_length 
 * @return unsigned char* 
 */
unsigned char	*read_source(const char *source, int *source_length)
{
	unsigned char	*source_data;
	int				source_fd;
	int				allocated;
	int				read_bytes;

	source_fd = open(source, O_RDONLY);
	if (source_fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	allocated = 0;
	read_bytes = 1;
	source_data = NULL;
	*source_length = 0;
	while (read_bytes > 0)
	{
		while (allocated <= *source_length)
			expand_data(&source_data, source_length, &allocated);
		read_bytes = read(source_fd, source_data + *source_length,
				MAX_COMPRESSION_BATCH_SIZE);
		if (read_bytes < 0)
			exit_error(MSG_ERROR_FILE_READ);
		*source_length += read_bytes;
	}
	if (close(source_fd) < 0)
		exit_error(NULL);
	return (source_data);
}

/**
 * @brief Checks for RLE sequence (consist of 2 byte sequence with 1 byte length
 * identifier).
 * 
 * @param index 
 * @param source_length 
 * @param length 
 * @param source_data 
 * @return t_bool 
 */
t_bool	found_sequence(int index, int source_length, int length,
	unsigned char *source_data)
{
	return (index < source_length - 2
		&& source_data[index] == source_data[index + 1]
		&& length % MAX_UNCOMPRESSION_BATCH_SIZE + 2
		<= MAX_UNCOMPRESSION_BATCH_SIZE);
}

/**
 * @brief Uncompressed RLE compressed file into data pointer and writes
 * uncompressed data length to length int pointer.
 * 
 * @param source 
 * @param data 
 * @param length 
 */
void	rle_uncompress_data(const char *source, unsigned char **data,
	int *length)
{
	unsigned char	*source_data;
	int				source_length;
	int				i;
	int				allocated;

	source_data = read_source(source, &source_length);
	allocated = 0;
	*length = 0;
	i = 0;
	while (i < source_length)
	{
		if (found_sequence(i, source_length, *length, source_data))
		{
			while (allocated <= *length + source_data[i + 2])
				expand_data(data, length, &allocated);
			write_sequence(data, length, source_data, &i);
			continue ;
		}
		while (allocated <= *length)
			expand_data(data, length, &allocated);
		(*data)[*length] = source_data[i];
		*length += 1;
		i++;
	}
	free(source_data);
}

/**
 * @brief Uncompresses RLE compressed file.
 * 
 * @param source 
 */
void	rle_uncompress(const char *source)
{
	unsigned char	*data;
	int				read_length;
	int				length;
	int				fd;
	int				i;

	data = NULL;
	rle_uncompress_data(source, &data, &length);
	fd = open(source, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	i = 0;
	while (i < length)
	{
		if (i + MAX_UNCOMPRESSION_BATCH_SIZE < length)
			read_length = MAX_UNCOMPRESSION_BATCH_SIZE;
		else
			read_length = length - i;
		if (write(fd, data + i, read_length) == -1)
			exit_error(MSG_ERROR_FILE_WRITE);
		i += MAX_UNCOMPRESSION_BATCH_SIZE;
	}
	free(data);
}
