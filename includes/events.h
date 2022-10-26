/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:52 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/26 11:23:25 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

enum e_keystate {
	FORWARD_DOWN = 1 << 0,
	LEFT_DOWN = 1 << 1,
	BACKWARD_DOWN = 1 << 2,
	RIGHT_DOWN = 1 << 3,
	W_DOWN = 1 << 4,
	A_DOWN = 1 << 5,
	S_DOWN = 1 << 6,
	D_DOWN = 1 << 7,
	SPACE_DOWN = 1 << 8,
	SHIFT_DOWN = 1 << 9,
	CTRL_DOWN = 1 << 10
};

#endif
