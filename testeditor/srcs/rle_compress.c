/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_compress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:03:01 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/06 12:52:04 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void	set_compression_sequence(unsigned char *compressed,
	int *compressed_bytes, t_uint8 *sequence_length, unsigned char byte)
{
	compressed[*compressed_bytes - *sequence_length] = byte;
	compressed[*compressed_bytes - *sequence_length + 1] = byte;
	*(t_uint8 *)&compressed[*compressed_bytes - *sequence_length + 2]
		= *sequence_length;
	*compressed_bytes -= *sequence_length - 3;
	*sequence_length = 0;
}

/**
 * @brief Finds byte sequences that are similar by 2 or more bytes. Counts those
 * bytes and compresses that area to 3 bytes (2 of that byte and 1 for count in
 * uint8)
 * 
 * @param buffer 
 * @param length 
 * @return int 
 */
int	compress_batch(unsigned char *buffer, int length)
{
	unsigned char	compressed[MAX_COMPRESSION_BATCH_SIZE];
	unsigned char	byte;
	int				i;
	int				compressed_bytes;
	t_uint8			sequence_length;

	sequence_length = 0;
	i = 0;
	compressed_bytes = 0;
	byte = buffer[i];
	while (i < length
		&& i < MAX_UNCOMPRESSION_BATCH_SIZE
		&& compressed_bytes < MAX_COMPRESSION_BATCH_SIZE)
	{
		if (!sequence_length)
			byte = buffer[i];
		if (buffer[i] == byte && sequence_length < 255)
			sequence_length++;
		else if (sequence_length >= 2)
		{
			set_compression_sequence((unsigned char *)&compressed,
				&compressed_bytes, &sequence_length, byte);
			sequence_length = 1;
			byte = buffer[i];
		}
		else
		{
			sequence_length = 1;
			byte = buffer[i];
		}
		compressed[compressed_bytes] = buffer[i];
		i++;
		compressed_bytes++;
	}
	if (sequence_length >= 2)
		set_compression_sequence((unsigned char *)&compressed,
			&compressed_bytes, &sequence_length, byte);
	ft_memcpy(buffer, &compressed, (size_t)compressed_bytes);
	return (compressed_bytes);
}

/**
 * @brief Compresses file using RLE (Run Length Encoding) algorithm, which finds
 * byte sequences of similar bytes that are 2 bytes or longer.
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
	target_fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0755);
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
