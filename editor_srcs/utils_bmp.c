/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:22:28 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/19 14:31:02 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Checks BMP header data. Checks that image size is reasonable and there
 * is no compression and bit count is IMAGE_PIXEL_BITS.
 * 
 * @param size 
 * @param header 
 * @return t_bool 
 */
static t_bool	check_header(t_point *size, t_uint8 *header)
{
	size->x = *(t_uint32 *)&header[18];
	size->y = *(t_uint32 *)&header[22];
	if (size->x <= 0
		|| size->y <= 0
		|| size->x > MAX_BMP_WIDTH
		|| size->y > MAX_BMP_HEIGHT
		|| *(t_uint32 *)&header[10] < 54
		|| *(t_uint8 *)&header[28] != IMAGE_PIXEL_BITS
		|| (*(t_uint32 *)&header[30] != 0 && *(t_uint32 *)&header[30] != 3))
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Reads pixels from file into surface.
 * 
 * @param surface 
 * @param fd 
 * @return t_bool 
 */
static t_bool	read_pixels(SDL_Surface *surface, int fd)
{
	int	y;

	y = 0;
	while (y < surface->h)
	{
		if (read(fd, surface->pixels + ((surface->h - y - 1) * surface->pitch),
				surface->w * IMAGE_PIXEL_BYTES)
			!= surface->w * IMAGE_PIXEL_BYTES)
			return (FALSE);
		y++;
	}
	return (TRUE);
}

/**
 * @brief Skips offset after header.
 * 
 * @param fd 
 * @param offset_length 
 * @return t_bool 
 */
static t_bool	skip_offset(int fd, int offset_length)
{
	t_uint8	*offset_data;

	if (!offset_length)
		return (TRUE);
	if (offset_length < 0 || offset_length > MAX_BMP_OFFSET)
		return (FALSE);
	offset_data = (t_uint8 *)malloc(offset_length);
	if (!offset_data)
		return (FALSE);
	if (read(fd, offset_data, offset_length) < 0)
	{
		free(offset_data);
		return (FALSE);
	}
	free(offset_data);
	return (TRUE);
}

/**
 * @brief Reads BMP file and returns pixels as SDL_Surface. Only supports
 * uncompressed IMAGE_PIXEL_BITS bit BMP files.
 * 
 * @param path 
 * @return SDL_Surface* 
 */
SDL_Surface	*bmp_to_surface(const char *path)
{
	t_point		size;
	int			fd;
	char		header[54];
	SDL_Surface	*surface;

	fd = open(path, O_RDONLY);
	if (fd < 0
		|| read(fd, &header, 54) != 54
		|| header[0] != 'B' || header[1] != 'M'
		|| !check_header(&size, (t_uint8 *)&header))
		return (NULL);
	if (!skip_offset(fd, *(t_uint32 *)&header[10] - 54))
		return (NULL);
	surface = SDL_CreateRGBSurface(0, size.x, size.y,
			IMAGE_PIXEL_BITS, 0, 0, 0, 0);
	if (!surface)
		return (NULL);
	if (!read_pixels(surface, fd))
	{
		SDL_FreeSurface(surface);
		return (NULL);
	}
	return (surface);
}
