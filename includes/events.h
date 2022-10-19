/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:52 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/19 15:16:49 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "doomnukem.h"

enum e_keystate {
	FORWARD_DOWN = 1,
	FORWARD_W_DOWN = 2,
	BACKWARD_DOWN = 4,
	BACKWARD_S_DOWN = 8,
	LEFT_DOWN = 16,
	RIGHT_DOWN = 32,
	ROTATE_LEFT_DOWN = 64,
	ROTATE_RIGHT_DOWN = 128
};

#endif
