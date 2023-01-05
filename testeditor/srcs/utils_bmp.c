/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:22:28 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/05 12:23:03 by saaltone         ###   ########.fr       */
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
t_bool	check_header(t_point *size, unsigned char *header)
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
t_bool	read_pixels(SDL_Surface *surface, int fd)
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
		|| !check_header(&size, (unsigned char *)&header))
		return (NULL);
	surface = SDL_CreateRGBSurface(0, size.x, size.y,
			IMAGE_PIXEL_BITS, 0, 0, 0, 0);
	if (!surface)
		return (NULL);
	if (read(fd, surface->pixels, *(t_uint32 *)&header[10] - 54) < 0)
		return (NULL);
	if (!read_pixels(surface, fd))
	{
		SDL_FreeSurface(surface);
		return (NULL);
	}
	return (surface);
}
