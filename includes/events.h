/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:52 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/25 10:43:02 by saaltone         ###   ########.fr       */
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
};

#endif
