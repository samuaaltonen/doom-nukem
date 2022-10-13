/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:48:08 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/12 22:40:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void        render_char(t_app *app, t_point position, SDL_Rect src);
static SDL_Rect    get_char(char *str, int c);

void    render_text(t_app *app, t_point position, char *text)
{
    char    *str;
    char    c;
    int     i;

    str = "abcdefghijklmnopqrstuvwxyz0123456789.,:;'\"!?-_()/|\\";
    i = 0;
    while (text[i] != '\0')
    {
        c = ft_tolower(text[i]);
        if (ft_strchr(str, c))
            render_char(app, position, get_char(str, c));
        position.x += app->font.size - 2;
        i++;
    }
}

static void    render_char(t_app *app, t_point position, SDL_Rect src)
{
    SDL_Rect    dst;

    dst.x = position.x;
    dst.y = position.y;
    dst.w = app->font.size;
    dst.h = app->font.size;
    SDL_BlitSurface(app->font.font, &src, app->surface, &dst);
}

static SDL_Rect  get_char(char *str, int c)
{
    SDL_Rect    src;
    int         font_offset;
    int         i;

    font_offset = 0;
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
    app->font.font = SDL_LoadBMP("fonts/doom-nukem_font.bmp");
    if (!app->font.font)
        exit_error("Could not load font");
    app->font.size = 14;
}

void    color_font(t_app *app, int color)
{
    int     x;
    int     y;
    int		pixel_pos;
	char	*pixel;

    x = 0;
    y = 0;
    while (y < app->font.font->h)
    {
        while (x < app->font.font->w)
        {
            pixel_pos = (y * app->font.font->pitch) + (x * IMAGE_PIXEL_BYTES);
            pixel = app->font.font->pixels + pixel_pos;
            if ((*(int *)pixel & 0xFF000000) != 0x00000000)
                put_pixel_to_surface(app->font.font, x, y, color);
            x++;
        }
        x = 0;
        y++;
    }
}