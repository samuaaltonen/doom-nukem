/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:40:17 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/13 17:35:57 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"


/**
 * Exits the application when window is destroyed.
 */
int	events_window_destroy(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * Exits the program and prints an error message to stderr (either with perror
 * or from variable).
 */
void	exit_error(char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	else
		perror(MSG_ERROR);
	exit(EXIT_FAILURE);
}

int main(void)
{
	t_app	*app;

	//testing
	t_vec2list walls1 = (t_vec2list){(t_vector2){1.0f,10.f},-1, 0, NULL};
	t_vec2list walls2 = (t_vec2list){(t_vector2){10.0f,0.f},-1, 0, NULL};
	t_vec2list walls3 = (t_vec2list){(t_vector2){7.0f,7.0f},-1, 0, NULL};
	t_vec2list walls4 = (t_vec2list){(t_vector2){0.0f,-10.f},-1, 0, NULL};
	t_vec2list walls5 = (t_vec2list){(t_vector2){-10.0f,0.f},-1, 0, NULL};
	t_vec2list walls6 = (t_vec2list){(t_vector2){-10.0f,-10.f},-1, 0, NULL};
	walls1.next = &walls2;
	walls2.next = &walls3;
	walls3.next = &walls1;
	walls4.next = &walls5;
	walls5.next = &walls6;
	walls6.next = &walls4;

	if (!app_init(&app))
		exit_error(NULL);
	app_prepare(app);
	put_sector_lst(app, new_sector_list(&walls1));
	//put_sector_lst(app, new_sector_list(&walls4));
	app_loop(app);
	return (0);
}