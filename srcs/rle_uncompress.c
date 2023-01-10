/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_uncompress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:11:34 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/10 15:54:39 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Writes RLE compressed sequence as uncompressed byte sequence to data
 * pointer.
 * 
 * @param data 
 * @param length 
 * @param source_data 
 * @param index 
 */
static void	write_sequence(unsigned char **data, int *length,
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
 * @brief Checks for RLE sequence (consist of 2 byte sequence with 1 byte length
 * identifier).
 * 
 * @param index 
 * @param source_length 
 * @param length 
 * @param source_data 
 * @return t_bool 
 */
static t_bool	found_sequence(int index, int source_length, int length,
	unsigned char *source_data)
{
	return (index < source_length - 2
		&& source_data[index] == source_data[index + 1]
		&& length % MAX_UNCOMPRESS_BATCH + 2 <= MAX_UNCOMPRESS_BATCH);
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