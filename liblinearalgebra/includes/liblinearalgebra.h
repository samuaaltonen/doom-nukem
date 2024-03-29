/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liblinearalgebra.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:46:18 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/07 18:11:04 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLINEARALGEBRA_H
# define LIBLINEARALGEBRA_H

# include "math.h"
# define LINE_POINT_EPSILON 0.0001

# ifndef LIBFT_H

typedef enum e_bool {
	FALSE = 0,
	TRUE = 1
}	t_bool;

# endif

enum e_line_resize_side {
	EXTEND_CORNER_A,
	EXTEND_CORNER_B,
	EXTEND_BOTH
};

/**
 * Integer type definitions
 */
typedef unsigned char	t_uint8;
typedef unsigned short	t_uint16;
typedef unsigned int	t_uint32;

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

typedef struct s_line {
	t_vector2	a;
	t_vector2	b;
}	t_line;

/**
 * Struct for integer coordinate point.
 */
typedef struct s_point
{
	int				x;
	int				y;
}	t_point;

typedef struct s_triangle
{
	t_point	a;
	t_point	b;
	t_point	c;
}	t_triangle;

typedef union u_colors
{
	int	color;
	struct
	{
		t_uint8	b;
		t_uint8	g;
		t_uint8	r;
		t_uint8	a;
	}	s_bgra;
}	t_colors;

double		ft_vector_length(t_vector2 a);
t_vector2	ft_vector_multiply_matrix(t_vector2 vector, t_matrix2 matrix);
t_vector2	ft_vector_perpendicular(t_vector2 a);
t_vector2	ft_vector_resize(t_vector2 a, double size);
t_matrix2	ft_matrix_inverse(t_matrix2 matrix);
int			ft_line_intersection(t_line line_a, t_line line_b,
				t_vector2 *intersection);
int			ft_line_intersection_full(t_line a, t_line b);
int			ft_line_intersection_through(t_line line_a, t_line line_b);
int			ft_line_intersection_segment(t_line line_a, t_line line_b,
				t_vector2 *intersection);
t_line		ft_line_resize(t_line line, double length, int side);
double		ft_vector_dotproduct(t_vector2 a, t_vector2 b);
double		ft_vector_crossproduct(t_vector2 a, t_vector2 b);
double		ft_vector_angle(t_vector2 a, t_vector2 b);
double		ft_vector_angle_left(t_vector2 a, t_vector2 b);
int			ft_line_point(t_line line, t_vector2 coord);
int			ft_line_side(t_line line, t_vector2 coord);
t_vector2	ft_vector2_sub(t_vector2 a, t_vector2 b);
t_vector2	ft_vector2_add(t_vector2 a, t_vector2 b);
t_vector3	ft_vector3_sub(t_vector3 a, t_vector3 b);
t_vector3	ft_vector3_add(t_vector3 a, t_vector3 b);
double		ft_lerp(double a, double b, double f);
void		ft_vector2_limit(t_vector2 *a, double limit);
void		ft_vector3_limit(t_vector3 *a, double limit);
t_vector2	ft_vector2_normalize(t_vector2 a);
t_vector3	ft_vec3_lerp(t_vector3 a, t_vector3 b, double f);
t_vector2	ft_vec2_lerp(t_vector2 a, t_vector2 b, double f);
t_vector2	ft_vec2_mult(t_vector2 a, double f);
t_vector2	ft_closest_point(t_vector2 point, t_line line);
double		ft_point_distance(t_vector2 a, t_vector2 b);
int			ft_point_on_segment(t_line line, t_vector2 point);
int			ft_point_on_segment_epsilon(t_line line, t_vector2 point,
				double epsilon);
int			ft_vector_compare(t_vector2 a, t_vector2 b);
void		ft_point_swap(t_point *a, t_point *b);
void		ft_swap(int *a, int *b);
t_vector3	ft_vec2_to_vec3(t_vector2 vector, double z);
void		ft_double_swap(double *a, double *b);
void		ft_vec2_swap(t_vector2 *a, t_vector2 *b);
int			blend_pixel_half(t_colors base, t_colors top);
t_bool		ft_cmp_line_points(t_line a, t_line b);

#endif
