/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/13 14:19:15 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void    render_button(t_app *app)
{
    SDL_Surface *button;
    SDL_Rect    clip;

    clip.x = 12;
    clip.y = 12;
    clip.w = 124;
    clip.h = 32;

	button = SDL_LoadBMP("assets/ui/button_iddle.bmp");
	SDL_BlitSurface(button, NULL, app->surface, &clip);
	SDL_FreeSurface(button);
}