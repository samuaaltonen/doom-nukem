/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:23:25 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/10 20:22:16 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Frees given superint struct and its int array.
*/
void	ft_superint_destroy(t_superint **superint)
{
	if (!superint || !(*superint))
		return ;
	if ((*superint)->numbers)
		free((*superint)->numbers);
	free(*superint);
}
