/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:40:17 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/13 15:34:09 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Exits the application when window is destroyed.
 * 
 * @return int
 */
int	events_window_destroy(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * @brief Exits the program and prints an error message to stderr (either with
 * perror or from variable).
 * 
 * @param message
 */
void	exit_error(char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	else
		perror(MSG_ERROR);
	exit(EXIT_FAILURE);
}

/**
 * @brief Start of application.
*/
int	main(void)
{
	t_app	*app;

	if (!app_init(&app))
		exit_error(MSG_ERROR_ALLOC);
	app_prepare(app);
	app_loop(app);
	return (0);
}
