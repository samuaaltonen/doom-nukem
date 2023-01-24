/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_change_level.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:23:24 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/24 15:56:56 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Initializes import level file name.
 * 
 * @param app 
 * @param level 
 */
void	import_init_level(t_app *app, const char *level)
{
	int	i;
	int	level_number;

	i = 0;
	while (level && level[i])
	{
		if (level[i] < '0' || level[i] > '9')
			exit_error(MSG_ERROR_LEVEL_NUMBER);
		i++;
	}
	ft_bzero((t_uint8 *)&app->filename, FILE_NAME_LENGTH);
	if (!level)
	{
		ft_memcpy((t_uint8 *)&app->filename, DEFAULT_LEVEL,
			ft_strlen(DEFAULT_LEVEL));
		return ;
	}
	level_number = ft_atoi(level);
	if (level_number < 0 || level_number > MAX_LEVEL)
		exit_error(MSG_ERROR_LEVEL_NUMBER);
	ft_memcpy((t_uint8 *)&app->filename, LEVEL_IDENTIFIER,
		ft_strlen(LEVEL_IDENTIFIER));
	ft_memcpy((t_uint8 *)&app->filename + ft_strlen(LEVEL_IDENTIFIER), level,
		ft_strlen(level));
}

/**
 * @brief Changes level.
 * 
 * @param app 
 * @param level 
 */
void	import_change_level(t_app *app, int level_number)
{
	char	*level;

	if (level_number < 0 || level_number > MAX_LEVEL)
		exit_error(MSG_ERROR_LEVEL_NUMBER);
	level = ft_itoa(level_number);
	if (!level)
		exit_error(MSG_ERROR_ALLOC);
	ft_memcpy((t_uint8 *)&app->filename + ft_strlen(LEVEL_IDENTIFIER), level,
		ft_strlen(level));
	free(level);
	free(app->sectors);
	load_data(app);
	level_validation(app);
	app->conf->keystates = 0;
	init_enemies(app);
	init_bullets(app);
}
