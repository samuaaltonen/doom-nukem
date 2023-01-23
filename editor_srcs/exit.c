/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:43:00 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/23 15:15:50 by saaltone         ###   ########.fr       */
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
 * @brief Exits the program and prints a message.
 * 
 * @param message
 */
void	exit_success(char *message)
{
	ft_printf("{cyan}%s{reset}\n", message);
	exit(EXIT_SUCCESS);
}
