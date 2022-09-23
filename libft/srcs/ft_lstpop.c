/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:47:50 by saaltone          #+#    #+#             */
/*   Updated: 2021/12/08 14:49:28 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Removes an element from the list and attaches the remaining list parts 
together. If needed, changes the start of the list (in case when first element 
is popped) */
void	ft_lstpop(t_list **start, t_list **pop, void (*del)(void*, size_t))
{
	t_list	*prev;
	t_list	*iterator;

	if (!start || !pop || !(*start) || !(*pop) || !del)
		return ;
	prev = NULL;
	iterator = *start;
	while (iterator->next && iterator != *pop)
	{
		prev = iterator;
		iterator = iterator->next;
	}
	if (iterator == *pop)
	{
		if (prev)
			prev->next = (*pop)->next;
		if (iterator == *start)
			*start = (*pop)->next;
		ft_lstdelone(pop, del);
	}
}
