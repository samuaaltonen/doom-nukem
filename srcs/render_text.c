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

static void        render_char(t_app *app, t_point position, SDL_Rect src);
static SDL_Rect    get_char(int c);

void    render_text(t_app *app, t_point position, char *text)
{
    int len;
    int i;

    len = ft_strlen(text);
    i = 0;
    while (text[i] != '\0')
    {
        if (text[i] == ' ')
        {
            position.x += app->my_font.size - 2;
            i++;
        }
        render_char(app, position, get_char(text[i]));
        position.x += app->my_font.size - 2;
        i++;
    }
}

static void    render_char(t_app *app, t_point position, SDL_Rect src)
{
    SDL_Rect    dst;

    dst.x = position.x;
    dst.y = position.y;
    dst.w = app->my_font.size;
    dst.h = app->my_font.size;
    SDL_BlitSurface(app->my_font.font, &src, app->surface, &dst);
}

static SDL_Rect  get_char(int c)
{
    SDL_Rect    src;
    char        *str;
    int         font_offset;
    int         i;

    str = "abcdefghijklmnopqrstuvwxyz0123456789.,:;'\"!?-_()/|\\";
    i = 0;
    while (str[i] != '\0')
    {
        if (ft_tolower(str[i]) == c)
            font_offset = i;
        i++;
    }
    src.x = 12 * font_offset;
    src.y = 0;
    src.w = 14;
    src.h = 14;
    return (src);
}

void    load_font(t_app *app)
{
    app->my_font.font = SDL_LoadBMP("fonts/doom-nukem_font.bmp");
    if (!app->my_font.font)
    {    
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit_error("Could not load font");
    }
    app->my_font.size = 14;
}

void    color_font(t_app *app, int color)
{
    int     x;
    int     y;
    int		pixel_pos;
	char	*pixel;

    x = 0;
    y = 0;
    while (y < app->my_font.font->h)
    {
        while (x < app->my_font.font->w)
        {
            pixel_pos = (y * app->my_font.font->pitch) + (x * IMAGE_PIXEL_BYTES);
            pixel = app->my_font.font->pixels + pixel_pos;
            if ((*(int *)pixel & 0xFF000000) != 0x00000000)
            put_pixel_to_surface(app->my_font.font, x, y, color);
            x++;
        }
        x = 0;
        y++;
    }
}