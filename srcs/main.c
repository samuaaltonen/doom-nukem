/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:21:47 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/19 16:48:46 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Main function to run the game.
 * 
 * @return int 
 */
int	main(void)
{
	t_app	*app;

	app_init(&app);
	sdl_init(app);
	config_init(app);
	load_data(app);
	level_validation(app);
	define_enemies(app);
	app_loop(app);
	return (0);
}
