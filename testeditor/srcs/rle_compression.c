/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_compression.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:03:01 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/05 14:29:28 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

int	compress_batch(unsigned char *buffer, int length)
{
	unsigned char	compressed[MAX_COMPRESSION_BATCH_SIZE];

}

/**
 * @brief Compresses file using RLE (Run Length Encoding) algorithm, which finds
 * byte sequences of similar bytes that are longer than 5 bytes and compresses
 * that sequence into int (4 bytes) + byte. Int contains information of how many
 * bytes were compressed in that sequence.
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
		read_bytes = read(source_fd, &buffer, MAX_COMPRESSION_BATCH_SIZE);
		if (read_bytes < 0)
			exit_error(MSG_ERROR_FILE_READ);
		if (read_bytes == 0)
			break ;
		compressed_bytes = compress_batch(&buffer, read_bytes);
		if (write(target_fd, &buffer, compressed_bytes) == -1)
			exit_error(MSG_ERROR_FILE_WRITE);
	}
	close(source_fd);
	close(target_fd);
}
