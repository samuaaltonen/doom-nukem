/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:52:07 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/24 12:05:10 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doomnukem.h"

int	game_status(t_app *app)
{
	if (app->status.title_screen)
		return(STATUS_TITLE);
	else if (app->status.title_menu)
		return(STATUS_MENU);
	else if (app->status.game_active)
		return (STATUS_GAME);
	else if (app->status.game_pause)
		return (STATUS_PAUSE);
	else
		return (-1);
}