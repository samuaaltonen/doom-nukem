/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:27:15 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 14:00:26 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

//check if list is convex, vertex_side from every point to every other point

/**
 * Finds and returns the wall in the sector that is furthest from the parallel line to selected point
 * 
 * ft_vector_length(c) * (sin(ft_vector_angle(line, c))
 * c = vector to iterated point
 */
t_vec2_lst	*find_opposite_point(t_sector_lst *sector, t_vec2_lst *point)
{
	t_vector2 c;
	t_vec2_lst *head;
	t_vec2_lst *selection;
	double	opposite;
	double	max;

	max = 0.0f;
	head = sector->wall_list;
	while (head->next != sector->wall_list )
	{
		c = (t_vector2){head->point.x - point->point.x, head->point.y - point->point.y};
		opposite = ft_vector_length(c) * sin(ft_vector_angle((t_vector2){point->next->point.x - point->point.x, point->next->point.y - point->point.y}, c));
		if(opposite > max)
		{
			max = opposite;
			selection = head;
		}
		head = head->next;
	}
		return (selection);
		//ft_printf(" opposite distance %f, \n", ft_vector_length(c) * ( sin(ft_vector_angle(line, c))));
}

//returns element out the link at the index
t_vec2_lst	*ft_lstindex(t_vec2_lst *lst, size_t index)
{
	size_t	i;
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

t_sector_lst	*sector_by_index(t_app *app, int index)
{
	t_sector_lst *head;
	int i;

	i = 0;
	head = app->sectors;
	while (head && i != index)
	{
		head = head->next;
		i++;
	}
	return (head);
}

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