/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:32:08 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/12 12:54:10 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_color(char *str, char *color)
{
	if (!str || !color)
		return ;
	if (!ft_strcmp(color, "BLACK"))
		ft_putstr("\033[0;30m");
	if (!ft_strcmp(color, "RED"))
		ft_putstr("\033[0;31m");
	if (!ft_strcmp(color, "GREEN"))
		ft_putstr("\033[0;32m");
	if (!ft_strcmp(color, "YELLOW"))
		ft_putstr("\033[0;33m");
	if (!ft_strcmp(color, "BLUE"))
		ft_putstr("\033[0;34m");
	if (!ft_strcmp(color, "PURPLE"))
		ft_putstr("\033[0;35m");
	if (!ft_strcmp(color, "CYAN"))
		ft_putstr("\033[0;36m");
	if (!ft_strcmp(color, "WHITE"))
		ft_putstr("\033[0;37m");
	ft_putstr(str);
	ft_putstr("\033[0m");
}
