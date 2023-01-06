/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_compress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:03:01 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/06 16:11:24 by saaltone         ###   ########.fr       */
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
void	set_sequence(unsigned char *compressed, int *compressed_bytes,
	t_uint8 *sequence_length, unsigned char byte)
{
	compressed[*compressed_bytes - *sequence_length] = byte;
	compressed[*compressed_bytes - *sequence_length + 1] = byte;
	*(t_uint8 *)&compressed[*compressed_bytes - *sequence_length + 2]
		= *sequence_length;
	*compressed_bytes -= *sequence_length - 3;
	*sequence_length = 1;
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
void	compress_batch(int target_fd, unsigned char *source_data, int len)
{
	unsigned char	compressed[MAX_COMPRESS_BATCH];
	int				i;
	int				size;
	t_uint8			sequence;

	sequence = 0;
	size = 0;
	i = -1;
	while (++i < len && i < MAX_UNCOMPRESS_BATCH && size < MAX_COMPRESS_BATCH)
	{
		if (i == 0 || (source_data[i] == source_data[i - 1] && sequence < 255))
			sequence++;
		else if (sequence >= 2)
			set_sequence((unsigned char *)&compressed, &size, &sequence,
				source_data[i - 1]);
		else
			sequence = 1;
		compressed[size] = source_data[i];
		size++;
	}
	if (sequence >= 2)
		set_sequence((unsigned char *)&compressed, &size, &sequence,
			source_data[i - 1]);
	if (write(target_fd, &compressed, size) == -1)
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
	if (!source_data)
		return ;
	target_fd = open(source, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (target_fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	i = 0;
	while (i < source_length)
	{
		if (i + MAX_UNCOMPRESS_BATCH < source_length)
			read_bytes = MAX_UNCOMPRESS_BATCH;
		else
			read_bytes = source_length - i;
		compress_batch(target_fd, source_data + i, read_bytes);
		i += MAX_UNCOMPRESS_BATCH;
	}
	free(source_data);
	close(target_fd);
}
