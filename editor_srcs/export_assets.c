/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_assets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:40:36 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/01 17:46:49 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Exports game assets
 * 
 * @param info 
 * @param fd 
 */
void	export_assets(t_import_info *info, int fd)
{
	export_surfaces(info, fd);
	export_wavs(info, fd);
	export_texts(info, fd);
}
