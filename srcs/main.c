/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:21:47 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/20 13:45:04 by dpalacio         ###   ########.fr       */
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
	//---level and game conf (To move after level selection)
	SDL_ShowCursor(SDL_DISABLE);
	app->player = (t_player){(t_vector2){POSITION_START_X, POSITION_START_Y},
		(t_vector2){DIRECTION_START_X, DIRECTION_START_Y},
		(t_vector2){0.0, 0.0}, 1.0, 0.5, 0};
	init_camera_plane(app);
	import_file(app, "./test.test");
	//---
	app_loop(app);
	return (0);
}
