/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:48:08 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/11 11:48:13 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void        render_char(t_app *app, t_point position, SDL_Rect src);
SDL_Rect    get_char(int c);
void        load_font(t_app *app);

void    render_text(t_app *app, t_point position, char *text)
{
    //SDL_Surface *text_surface;
    int len;
    int i;

    len = ft_strlen(text);
    i = 0;
    while (text[i] != '\0')
    {
        ft_putchar(text[i]);
        render_char(app, position, get_char(text[i]));
        position.x += app->my_font.size;
        i++;
    }
}

void    render_char(t_app *app, t_point position, SDL_Rect src)
{
    SDL_Rect    dst;

    dst.x = position.x;
    dst.y = position.y;
    dst.w = app->my_font.size;
    dst.h = app->my_font.size;
    SDL_BlitSurface(app->my_font.font, &src, app->surface, &dst);
}

SDL_Rect  get_char(int c)
{
    SDL_Rect    src;
    char        *str;
    int         font_offset;
    int         i;
    str = "abcdefghijklmnopqrstuvwxyz0123456789.,:;'!?-_()/|";
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            font_offset = i;
        i++;
    }
    src.x = 14 * font_offset;
    src.y = 0;
    src.w = 14;
    src.h = 14;
    return (src);
}

void    load_font(t_app *app)
{
    app->my_font.font = SDL_LoadBMP("font/doom-nukem_font.bmp");
    if (!app->my_font.font)
        exit_error("Could not load font");
    app->my_font.size = 14;
}
