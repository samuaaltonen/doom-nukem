/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:40:17 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/11 12:53:30 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"


/**
 * Exits the application when window is destroyed.
 */
int	events_window_destroy(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * Exits the program and prints an error message to stderr (either with perror
 * or from variable).
 */
void	exit_error(char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	else
		perror(MSG_ERROR);
	exit(EXIT_FAILURE);
}

int	add_sector_lst(t_app *app, t_sectorlist* new)
{
	t_sectorlist *iter;

	if(new)
	{
		
	}
	iter = *app->sectors;
	return (0);
}

int main(void)
{
	t_app	*app;
	t_sectorlist **sectors;

	sectors = ft_memalloc(sizeof(t_sectorlist *));
	if(!sectors)
		return (0);

	if (!app_init(&app))
		exit_error(NULL);
	app_prepare(app);
	app_loop(app);
	return (0);
}