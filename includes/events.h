/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:52 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/19 16:41:09 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

enum e_keystate {
	UP		= 1 << 0,
	LEFT	= 1 << 1,
	DOWN	= 1 << 2,
	RIGHT	= 1 << 3,
	W		= 1 << 4,
	A		= 1 << 5,
	S		= 1 << 6,
	D		= 1 << 7,
	SPACE	= 1 << 8,
	SHIFT	= 1 << 9,
	CTRL	= 1 << 10,
	Q 		= 1 << 11,
	E 		= 1 << 12,
	R 		= 1 << 13,
	C 		= 1 << 14
};

enum e_buttonstate {
	LEFT_MOUSE		= 1 << 0,
	RIGHT_MOUSE		= 1 << 1,
	MIDDLE_MOUSE	= 1 << 2
};

#endif
