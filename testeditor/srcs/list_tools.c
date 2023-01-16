/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:22:32 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/13 15:27:46 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Calculates how many nodes does the given list have.
 * 
 * @param lst
 * @return size_t
*/
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
 * @brief Returns element out the link at the index.
 * 
 * @param lst
 * @param index
 * @return t_vec2_lst
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
 * @brief Cancels the ungoing list creation and deletes the incomplete
 * sectorlist.
 * 
 * @param app
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

/**
 * @brief Check if clicked point is already part of the same list.
 * 
 * @param app 
 * @return t_bool 
 */
t_bool	valid_point(t_app *app)
{
	t_vec2_lst	*tmp;

	tmp = app->active;
	while (tmp)
	{
		if (tmp->point.x == app->mouse_track.x
			&& tmp->point.y == app->mouse_track.y)
			return (FALSE);
		if (tmp->next && ft_line_side((t_line)
				{tmp->point, tmp->next->point}, app->mouse_track))
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}
