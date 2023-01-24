/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:40:17 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/23 15:25:33 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Start of application.
*/
int	main(const int argc, const char **argv)
{
	t_app	*app;

	if (argc != 2)
		exit_success(MSG_USAGE);
	if (!app_init(&app))
		exit_error(MSG_ERROR_ALLOC);
	app_prepare(app);
	import_init(app, (const char *)argv[1]);
	import_file(app);
	app_loop(app);
	return (0);
}
