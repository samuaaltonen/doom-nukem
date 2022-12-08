/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textmodal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:26:54 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/06 15:03:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Get the text prompt size object
 * 
 * @param app 
 * @param char_count 
 * @param total 
 * @return t_rect 
 */
static t_rect	get_text_prompt_size(int char_count, int total)
{
	t_rect	area;

	area.w = total * 10;
	if (area.w > WIN_W / 2)
		area.w = WIN_W / 2;
	area.w += 24;
	area.h = (char_count * 10 / (WIN_W / 2) + 2) * 20;
	area.x = (WIN_W - area.w) / 2;
	area.y = WIN_H / 8;
	return (area);
}

/**
 * @brief Renders textmodals.
 * 
 * @param app 
 */
void	render_textmodals(t_app *app)
{
	int	char_count;
	int	char_save;

	if (!app->textmodal.duration)
		return ;
	char_count = (int)(app->textmodal.progress / ANIMATION_DURATION_TEXT);
	if (char_count >= app->text_lengths[app->textmodal.text] - 1)
		char_count = app->text_lengths[app->textmodal.text] - 1;
	if (char_count <= 0)
		return ;
	char_save = app->texts[app->textmodal.text][char_count];
	app->texts[app->textmodal.text][char_count] = 0;
	render_text_prompt(app, get_text_prompt_size(
			char_count, app->text_lengths[app->textmodal.text]), 1,
		app->texts[app->textmodal.text]);
	app->texts[app->textmodal.text][char_count] = char_save;
}
