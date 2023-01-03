/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:22:32 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/02 13:58:01 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

size_t	ft_lstlen(t_sector_lst *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/**
 * Returns element out the link at the index.
*/
t_vec2_lst	*ft_lstindex(t_vec2_lst *lst, size_t index)
{
	size_t		i;
	t_vec2_lst	*temp;

	i = 0;
	temp = lst;
	if (index == 0)
		return (lst);
	if (temp == NULL)
		return (NULL);
	while (i < index)
	{
		if (temp->next)
			temp = temp->next;
		else
			return (NULL);
		i++;
	}
	return (temp);
}

/**
 * Cancels the ungoing list creation and deletes the incomplete sector list.
*/
void	cancel_list_creation(t_app *app)
{
	del_vector_list(&(app->active));
	app->active = NULL;
	app->active_last = NULL;
	app->active_sector = NULL;
	app->list_ongoing = FALSE;
	app->list_creation = FALSE;
}
