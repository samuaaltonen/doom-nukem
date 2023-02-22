/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:40:31 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/21 13:55:54 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns random float between 0 and max.
 * 
 * @param app 
 * @param max 
 * @return double 
 */
double	ft_random_double(t_app *app, double max)
{
	static int	count = 0;

	count++;
	return (app->conf->fps_clock.tv_nsec * count % RANDOM_GENERATOR_RANGE * max
		/ RANDOM_GENERATOR_RANGE);
}
