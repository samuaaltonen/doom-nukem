/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:22:32 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/07 17:28:51 by htahvana         ###   ########.fr       */
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
 * @brief returns vec2_list len, protection for loops
 * 
 * @param lst_start 
 * @return size_t 
 */
size_t	vec2_lstlen(t_vec2_lst *lst_start)
{
	size_t		count;
	t_vec2_lst	*head;

	if (!lst_start)
		return (0);
	head = lst_start;
	count = 1;
	while (head->next && head->next != lst_start)
	{
		count++;
		head = head->next;
	}
	return (count);
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

static void	check_angles(t_app *app, t_vec2_lst *tmp, double *angle,
	t_vector2 *last)
{
	if (tmp != app->active && tmp->next)
			*angle += ft_vector_angle(ft_vector2_sub(tmp->next->point,
					tmp->point), *last);
	else if (tmp != app->active)
		*angle += ft_vector_angle(ft_vector2_sub(app->mouse_track,
					app->active_last->point), *last);
	if (tmp->next)
		*last = ft_vector2_sub(tmp->next->point, tmp->point);
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
	t_vector2	last;
	double		angle;

	tmp = app->active;
	angle = 0.f;
	while (tmp)
	{
		check_angles(app, tmp, &angle, &last);
		if (ft_vector_compare(tmp->point, app->mouse_track) || (tmp->next
				&& ft_line_side((t_line){tmp->point, tmp->next->point},
				app->mouse_track)))
			return (FALSE);
		tmp = tmp->next;
	}
	if (vec2_lstlen(app->active) >= MAX_SECTOR_CORNERS)
		return (FALSE);
	if (app->active->next)
		angle += ft_vector_angle(ft_vector2_sub(app->active->next->point,
					app->active->point), ft_vector2_sub(app->active->point,
					app->active_last->point));
	if (angle > M_PI * 2)
		return (FALSE);
	return (TRUE);
}
