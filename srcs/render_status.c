/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:57:31 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/13 11:45:15 by dpalacio         ###   ########.fr       */
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
	update_states(app);
	progress_animations(app);
	handle_movement(app);
	update_position(app);
	render_sectors(app);
	render_objects(app);
	render_textmodals(app);
	render_ui(app);
	regen(app, &app->player.hp);
	regen(app, &app->player.shield);
	if (app->player.hp == 0)
		app->status = STATUS_GAMEOVER;
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
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}

void	render_gameover(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	change_font(app, 80, BLACK);
	render_text(app, (t_rect){WIN_W / 2 - 120, 214, 320, 800}, "GAME OVER");
	change_font(app, 80, DARK_RED);
	render_text(app, (t_rect){WIN_W / 2 - 116, 210, 320, 800}, "GAME OVER");
	change_font(app, 32, WHITE);
	render_text(app, (t_rect){504, WIN_H - 170, 800, 800}, "You suck at this!");
	load_font(app);
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}