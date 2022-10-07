/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:42:06 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/07 16:35:22 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

//vector2d list for adding new vertices of a sector
t_vec2list	*new_vector_list(t_app *app)
{
	t_vec2list		*new;

	if (app->mouse_click.x < 0 || app->mouse_click.x > WIN_W
		|| app->mouse_click.y < 0 || app->mouse_click.y > WIN_H)
		return (NULL);
	new = malloc(sizeof(t_vec2list));
	if (!new)
		return (NULL);
	new->point.x = app->mouse_click.x;
	new->point.y = app->mouse_click.y;
	new->next = NULL;
	return (new);
}

void	add_vector_list(t_vec2list **list, t_vec2list *new)
{
	if (new)
	{
		new->next = *list;
		*list = new;
	}
}

int		del_sector_list(t_app *app, t_vec2list *list)
{
(void)app;
(void)list;
 return(0);
}