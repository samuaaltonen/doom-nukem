/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:21:47 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/12 15:46:44 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

int	main(void)
{
	t_app	*app;

	app_init(&app);
	sdl_init(app);
	if (!config_init(app))
		exit_error(NULL);
	load_data(app);
	level_validation(app);
	define_enemies(app);
	app_loop(app);
	return (0);
}
