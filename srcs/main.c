/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:21:47 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/08 16:38:33 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Main function to run the game.
 * 
 * @return int 
 */
int	main(const int argc, const char **argv)
{
	t_app	*app;

	app_init(&app);
	sdl_init(app);
	config_init(app);
	if (argc == 2)
		import_init_level(app, (const char *)argv[1]);
	else
		import_init_level(app, NULL);
	load_data(app);
	level_validation(app);
	hand_init(app);
	define_enemies(app);
	define_weapons(app);
	define_bullets(app);
	app_loop(app);
	return (0);
}
