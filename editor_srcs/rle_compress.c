/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_compress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:03:01 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/01 15:46:03 by saaltone         ###   ########.fr       */
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
void	set_sequence(t_uint8 *compressed, int *compressed_bytes,
	t_uint8 *sequence_length, t_uint8 byte)
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
void	compress_batch(int target_fd, t_uint8 *source_data, int len)
{
	t_uint8	compressed[MAX_COMPRESS_BATCH];
	int		i;
	int		size;
	t_uint8	sequence;

	sequence = 0;
	size = 0;
	i = -1;
	while (++i < len && i < MAX_UNCOMPRESS_BATCH && size < MAX_COMPRESS_BATCH)
	{
		if (i == 0 || (source_data[i] == source_data[i - 1] && sequence < 255))
			sequence++;
		else if (sequence >= 2)
			set_sequence((t_uint8 *)&compressed, &size, &sequence,
				source_data[i - 1]);
		else
			sequence = 1;
		compressed[size] = source_data[i];
		size++;
	}
	if (sequence >= 2)
		set_sequence((t_uint8 *)&compressed, &size, &sequence,
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
void	rle_compress(t_import_info *info, const char *source)
{
	t_uint8	*source_data;
	int		read_bytes;
	int		target_fd;

	source_data = read_source(source, &info->compressed_length);
	if (!source_data)
		return ;
	target_fd = open(source, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (target_fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	info->uncompressed = 0;
	while (info->uncompressed < info->compressed_length)
	{
		compression_update_progress(info);
		if (info->uncompressed + MAX_UNCOMPRESS_BATCH < info->compressed_length)
			read_bytes = MAX_UNCOMPRESS_BATCH;
		else
			read_bytes = info->compressed_length - info->uncompressed;
		compress_batch(target_fd, source_data + info->uncompressed, read_bytes);
		info->uncompressed += MAX_UNCOMPRESS_BATCH;
	}
	free(source_data);
	if (close(target_fd) < 0)
		exit_error(MSG_ERROR_FILE_CLOSE);
}
