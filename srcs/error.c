/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:18:47 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/05 16:17:05 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
