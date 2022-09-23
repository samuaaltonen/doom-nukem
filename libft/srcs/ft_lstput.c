/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:35:55 by saaltone          #+#    #+#             */
/*   Updated: 2021/12/03 15:09:36 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstput(t_list **alst, t_list *new)
{
	t_list	*iterator;

	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	iterator = *alst;
	while (iterator->next)
		iterator = iterator->next;
	iterator->next = new;
}
