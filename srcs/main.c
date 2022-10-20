/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:21:47 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/20 14:11:47 by htahvana         ###   ########.fr       */
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
	load_assets(app);
	//---level and game conf
	SDL_ShowCursor(SDL_DISABLE);
	app->player = (t_player){(t_vector2){POSITION_START_X, POSITION_START_Y},
		(t_vector2){DIRECTION_START_X, DIRECTION_START_Y},
		(t_vector2){0.0, 0.0}, 1.0, 0.5, 0};
	init_camera_plane(app);
	import_file(app, MAP_PATH);
	//---
	app_loop(app);
	return (0);
}
