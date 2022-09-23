/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbtoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:22:31 by saaltone          #+#    #+#             */
/*   Updated: 2022/01/17 17:58:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_rgbtoint(int red, int green, int blue)
{
	int	total;

	total = red;
	total = (total << 8) + green;
	total = (total << 8) + blue;
	return (total);
}
