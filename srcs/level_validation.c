/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:45:06 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/12 16:58:13 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Performs validation checks level data.
 * 
 * @param app 
 */
void	level_validation(t_app *app)
{
	level_validation_sectors(app);
	level_validation_assets(app);
}
