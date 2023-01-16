/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:10:43 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 15:31:47 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

t_vector3	ft_vec2_to_vec3(t_vector2 vector, double z)
{
	return ((t_vector3){vector.x, vector.y, z});
}
