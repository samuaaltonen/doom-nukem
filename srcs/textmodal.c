/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textmodal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:26:54 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/20 17:11:35 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Get the word index.
 * 
 * @param text 
 * @param index 
 * @return int 
 */
static int	get_modal_word_length(char *text, int index)
{
	int	length;

	length = 0;
	while (text[index] != ' ' && text[index] != '\0')
	{
		if (ft_islower(text[index]) || ft_isdigit(text[index]))
			length += 10;
		else
			length += 12;
		index++;
	}
	return (length);
}

/**
 * @brief Returns textmodal length.
 * 
 * @param app 
 * @param text 
 * @return int 
 */
static int	get_modal_line_count(char *text)
{
	int		i;
	int		pos;
	int		lines;

	pos = 0;
	lines = 1;
	i = 0;
	while (text[i] != '\0')
	{
		if (i > 0 && text[i - 1] == ' '
			&& pos + get_modal_word_length(text, i) > WIN_W / 2)
		{
			pos = 0;
			lines++;
			if (text[i] == ' ')
				i++;
		}
		if (ft_islower(text[i]) || ft_isdigit(text[i]))
			pos += 10;
		else
			pos += 12;
		i++;
	}
	return (lines);
}

/**
 * @brief Get the text prompt size.
 * 
 * @param app 
 * @param char_count 
 * @param total 
 * @return t_rect 
 */
static t_rect	get_text_prompt_size(t_app *app, int text_index)
{
	t_rect	area;

	area.w = app->text_lengths[text_index] * 12;
	if (area.w > WIN_W / 2)
		area.w = WIN_W / 2;
	area.w += 24;
	area.h = (get_modal_line_count(app->texts[text_index]) + 1) * 20;
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
		char_count = app->text_lengths[app->textmodal.text];
	if (char_count <= 0)
		return ;
	while (app->texts[app->textmodal.text][char_count]
		&& app->texts[app->textmodal.text][char_count] != ' ')
		char_count++;
	char_save = app->texts[app->textmodal.text][char_count];
	app->texts[app->textmodal.text][char_count] = 0;
	render_text_prompt(app, get_text_prompt_size(app, app->textmodal.text), 1,
		app->texts[app->textmodal.text]);
	app->texts[app->textmodal.text][char_count] = char_save;
}
