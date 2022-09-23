/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:54:24 by saaltone          #+#    #+#             */
/*   Updated: 2022/02/16 15:54:54 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_append_char(char **str, char append)
{
	int		last_empty;

	last_empty = 0;
	while ((*str)[last_empty])
		last_empty++;
	(*str)[last_empty] = append;
}
