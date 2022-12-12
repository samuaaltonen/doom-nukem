/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:57:31 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/12 13:08:04 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_titlescreen(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	change_font(app, 80, BLACK);
	render_text(app, (t_rect){484, 214, 400, 800}, "AWAKE");
	change_font(app, 80, DARK_RED);
	render_text(app, (t_rect){490, 210, 320, 800}, "AWAKE");
	change_font(app, 32, WHITE);
	render_text(app, (t_rect){504, WIN_H - 170, 800, 800}, "PRESS SPACE");
	load_font(app);
	play_music(app, MUSIC_PATH);
}

void	render_mainmenu(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	render_ui_frame(app, (t_rect){28, 78, 300, 428}, 1, DARK_GREY);
	change_font(app, 70, DARK_RED);
	render_text(app, (t_rect){50, 100, 800, 800}, "AWAKE");
	button_function(app,
		render_button(app, (t_rect){50, 180, 256, 64}, 1,
		"START GAME"), start_game);
	button_function(app,
		render_button(app, (t_rect){50, 260, 256, 64}, 1,
		"LEVEL EDITOR"), do_nothing);
	button_function(app,
		render_button(app, (t_rect){50, 340, 256, 64}, 1,
		"OPTIONS"), main_options);
	button_function(app,
		render_button(app, (t_rect){50, 420, 256, 64}, 1,
		"QUIT GAME"), exit_game);
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}

static void update_states(t_app *app)
{
	int	i;

	(void)app;
	i = -1;
	while (++i < app->conf->header.object_count)
	{
		if(app->objects[i].type == MONSTER1)
		{
			ft_printf("test\n");
			app->object_states[i] += 5.f * app->conf->delta_time;
			if(app->object_states[i] > 2)
				app->object_states[i] = 0.f;
		}
		else if(app->objects[i].type == MONSTER2)
		{
			app->object_states[i] += 5.f * app->conf->delta_time;
			if(app->object_states[i] > 10)
				app->object_states[i] = 0.f;
		}
	}

}

void	render_game(t_app *app)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	handle_movement(app);
	update_states(app);
	render_sectors(app);
	render_objects(app);
	render_ui(app);
}

void	render_pausemenu(t_app *app)
{	
	SDL_SetRelativeMouseMode(SDL_FALSE);
	render_sectors(app);
	render_ui_frame(app, (t_rect){28,78,300,428}, 1, DARK_GREY);
	button_function(app,
		render_button(app, (t_rect){50, 100, 256, 64}, 1, "MAIN MENU"), main_menu);
	button_function(app,
		render_button(app, (t_rect){50, 180, 256, 64}, 1, "CONTINUE"), pause_game);
	button_function(app,
		render_button(app, (t_rect){50, 260, 256, 64}, 1, "LEVEL EDITOR"), do_nothing);
	button_function(app,
		render_button(app, (t_rect){50, 340, 256, 64}, 1, "OPTIONS"), game_options);
	button_function(app,
		render_button(app, (t_rect){50, 420, 256, 64}, 1, "QUIT GAME"), exit_game);
	render_ui(app);
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}

void	render_options(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	if (app->status == STATUS_MAINOPTIONS)
		blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	else if (app->status == STATUS_GAMEOPTIONS)
		render_sectors(app);
	render_ui_frame(app, (t_rect){320, 132, 224, 64}, 1, DARK_GREY);
	change_font(app, 32, DARK_RED);
	render_text(app, (t_rect){336, 146, 800, 800}, "OPTIONS");
	render_ui_frame(app, (t_rect){320, 180, 640, 360}, 1, DARK_GREY);
	button_function(app,
		render_button(app, (t_rect){340, 200, 160, 32}, 1, "FULLSCREEN"), fullscreen);
	if (app->status == STATUS_MAINOPTIONS)
	button_function(app,
		render_button(app, (t_rect){880, 488, 60, 32}, 1, "Back"), main_menu);
	if (app->status == STATUS_GAMEOPTIONS)
	button_function(app,
		render_button(app, (t_rect){880, 488, 60, 32}, 1, "Back"), pause_game);
	change_font(app, 16, CYAN);
	render_text(app, (t_rect){336, 250, 800, 800}, "Random long text with a lot of words to see how it looks");
	render_text(app, (t_rect){336, 270, 800, 800}, "An equally long text with the numbers 7, 9, 5 and even 5");
	render_text(app, (t_rect){336, 290, 800, 800}, "With a few (Symbols) and 'quotes'...? and 0 FUCKS given");
	render_text(app, (t_rect){336, 310, 800, 800}, "And now an extra line\nwith an extra line!");
	render_text(app, (t_rect){336, 350, 300, 100}, "For the finale: A text that doesn' fit horizontally in the given rectangle AND that doesn't fit vertically so this sentence will be mostly unfinished");

	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}