/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_compress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:03:01 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/06 15:16:00 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Writes compressions sequence.
 * 
 * @param compressed 
 * @param compressed_bytes 
 * @param sequence_length 
 * @param byte 
 */
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
 * @param target_fd 
 * @param source_data 
 * @param length 
 */
void	compress_batch(int target_fd, unsigned char *source_data, int length)
{
	unsigned char	compressed[MAX_COMPRESSION_BATCH_SIZE];
	unsigned char	byte;
	int				i;
	int				compressed_bytes;
	t_uint8			sequence_length;

	sequence_length = 0;
	i = 0;
	compressed_bytes = 0;
	byte = source_data[i];
	while (i < length
		&& i < MAX_UNCOMPRESSION_BATCH_SIZE
		&& compressed_bytes < MAX_COMPRESSION_BATCH_SIZE)
	{
		if (!sequence_length)
			byte = source_data[i];
		if (source_data[i] == byte && sequence_length < 255)
			sequence_length++;
		else if (sequence_length >= 2)
		{
			set_compression_sequence((unsigned char *)&compressed,
				&compressed_bytes, &sequence_length, byte);
			sequence_length = 1;
			byte = source_data[i];
		}
		else
		{
			sequence_length = 1;
			byte = source_data[i];
		}
		compressed[compressed_bytes] = source_data[i];
		i++;
		compressed_bytes++;
	}
	if (sequence_length >= 2)
		set_compression_sequence((unsigned char *)&compressed,
			&compressed_bytes, &sequence_length, byte);
	if (write(target_fd, &compressed, compressed_bytes) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
}

/**
 * @brief Compresses file using RLE (Run Length Encoding) algorithm, which finds
 * byte sequences of similar bytes that are 2 bytes or longer.
 * 
 * @param source 
 */
void	rle_compress(const char *source)
{
	unsigned char	*source_data;
	int				source_length;
	int				read_bytes;
	int				target_fd;
	int				i;

	source_data = read_source(source, &source_length);
	target_fd = open(source, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (target_fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	i = 0;
	while (i < source_length)
	{
		if (i + MAX_UNCOMPRESSION_BATCH_SIZE < source_length)
			read_bytes = MAX_UNCOMPRESSION_BATCH_SIZE;
		else
			read_bytes = source_length - i;
		compress_batch(target_fd, source_data + i, read_bytes);
		i += MAX_UNCOMPRESSION_BATCH_SIZE;
	}
	free(source_data);
	close(target_fd);
}
