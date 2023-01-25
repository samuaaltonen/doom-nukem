/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_options_menu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:22:31 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/25 16:23:43 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	fullscreen(t_app *app)
{
	if (!(SDL_GetWindowFlags(app->win) & SDL_WINDOW_FULLSCREEN))
	{
		SDL_DestroyWindow(app->win);
		app->win = SDL_CreateWindow(WIN_NAME, 0, 0,
				WIN_W, WIN_H, SDL_WINDOW_FULLSCREEN);
	}
	else if (SDL_GetWindowFlags(app->win) & SDL_WINDOW_FULLSCREEN)
	{
		SDL_DestroyWindow(app->win);
		app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, 0);
	}	
	app->surface = SDL_GetWindowSurface(app->win);
}

void	controls(t_app *app)
{
	app->status = STATUS_CONTROLS;
}
