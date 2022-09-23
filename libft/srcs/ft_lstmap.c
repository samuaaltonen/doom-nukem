/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:05:34 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/10 15:05:40 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*mapped;
	t_list	*mapped_next;

	if (!lst || !f)
		return (NULL);
	mapped = f(lst);
	if (!mapped)
		return (NULL);
	if (lst->next)
	{
		mapped_next = ft_lstmap(lst->next, f);
		if (!mapped_next)
		{
			free(mapped);
			return (NULL);
		}
		mapped->next = mapped_next;
	}
	return (mapped);
}
