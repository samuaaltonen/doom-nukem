/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:40:31 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/23 18:21:50 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

double	ft_random_double(t_app *app, double max)
{
	static int	count;

	count++;
	return (app->conf->fps_clock.tv_nsec * count % 1000000 * max / 1000000);
}