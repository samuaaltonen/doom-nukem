/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liblinearalgebra.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:46:18 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/13 12:17:49 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLINEARALGEBRA_H
# define LIBLINEARALGEBRA_H
# include "math.h"

enum e_vertex_resize_side {
	EXTEND_CORNER_A,
	EXTEND_CORNER_B,
	EXTEND_BOTH
};

typedef struct s_vector2 {
	double	x;
	double	y;
}	t_vector2;

typedef struct s_vector3 {
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_matrix2 {
	t_vector2	a;
	t_vector2	b;
}	t_matrix2;

typedef struct s_vertex2 {
	t_vector2	a;
	t_vector2	b;
}	t_vertex2;

double		ft_vector_length(t_vector2 a);
t_vector2	ft_vector_multiply_matrix(t_vector2 vector, t_matrix2 matrix);
t_vector2	ft_vector_perpendicular(t_vector2 a);
t_vector2	ft_vector_resize(t_vector2 a, double size);
t_matrix2	ft_matrix_inverse(t_matrix2 matrix);
int			ft_vertex_intersection(t_vertex2 vertex_a, t_vertex2 vertex_b,
				t_vector2 *intersection);
int			ft_vertex_intersection_through(t_vertex2 vertex_a,
				t_vertex2 vertex_b, t_vector2 *intersection);
t_vertex2	ft_vertex_resize(t_vertex2 vertex, double length, int side);
double		ft_vector_dotproduct(t_vector2 a, t_vector2 b);
double		ft_vector_crossproduct(t_vector2 a, t_vector2 b);
double		ft_vector_angle(t_vector2 a, t_vector2 b);
int			ft_vertex_side(t_vertex2 vertex, t_vector2 coord);

#endif
