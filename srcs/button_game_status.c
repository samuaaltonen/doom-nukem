/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_game_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:54:15 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/25 16:23:27 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	main_menu(t_app *app)
{
	app->status = STATUS_MAINMENU;
}

void	main_options(t_app *app)
{
	app->status = STATUS_MAINOPTIONS;
}

void	game_options(t_app *app)
{
	app->status = STATUS_GAMEOPTIONS;
}

void	select_level(t_app *app)
{
	app->status = STATUS_SELECTLEVEL;
}

void	pause_game(t_app *app)
{
	if (app->status == STATUS_GAME || app->status == STATUS_GAMEOPTIONS)
		app->status = STATUS_PAUSEMENU;
	else if (app->status == STATUS_PAUSEMENU)
		app->status = STATUS_GAME;
}
