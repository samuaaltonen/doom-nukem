/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_compression.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:03:01 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/05 16:54:29 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

int	compress_batch(unsigned char *buffer, int length)
{
	unsigned char	compressed[MAX_COMPRESSION_BATCH_SIZE];
	unsigned char	byte;
	int				i;
	int				j;
	t_uint8			sequence_length;

	sequence_length = 0;
	i = 0;
	j = 0;
	while (i < length
		&& i < MAX_UNCOMPRESSION_BATCH_SIZE && j < MAX_COMPRESSION_BATCH_SIZE)
	{
		if (!sequence_length)
			byte = buffer[i];
		if (buffer[i] == byte && i < length - 1 && sequence_length < 255)
			sequence_length++;
		else if (sequence_length >= 2)
		{
			compressed[j - sequence_length] = byte;
			compressed[j - sequence_length + 1] = byte;
			*(t_uint8 *)&compressed[j - sequence_length + 2] = sequence_length;
			j -= sequence_length - 3;
			sequence_length = 0;
		}
		else
		{
			sequence_length = 1;
			byte = buffer[i];
		}
		compressed[j] = buffer[i];
		i++;
		j++;
	}
	ft_memcpy(buffer, &compressed, (size_t)j);
	return (j);
}

/**
 * @brief Compresses file using RLE (Run Length Encoding) algorithm, which finds
 * byte sequences of similar bytes that are longer than 3 bytes and compresses
 * that sequence into uint8 (1 byte) + byte. Int contains information of how
 * many bytes were compressed in that sequence.
 * 
 * @param source 
 * @param target 
 */
void	rle_compress(const char *source, char *target)
{
	unsigned char	buffer[MAX_COMPRESSION_BATCH_SIZE];
	int				source_fd;
	int				target_fd;
	int				read_bytes;
	int				compressed_bytes;

	source_fd = open(source, O_RDONLY | O_CREAT, 0755);
	target_fd = open(target, O_WRONLY | O_CREAT, 0755);
	if (source_fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	if (target_fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	while (TRUE)
	{
		read_bytes = read(source_fd, &buffer, MAX_UNCOMPRESSION_BATCH_SIZE);
		if (read_bytes < 0)
			exit_error(MSG_ERROR_FILE_READ);
		if (read_bytes == 0)
			break ;
		compressed_bytes = compress_batch((unsigned char *)&buffer, read_bytes);
		if (write(target_fd, &buffer, compressed_bytes) == -1)
			exit_error(MSG_ERROR_FILE_WRITE);
	}
	close(source_fd);
	close(target_fd);
}
