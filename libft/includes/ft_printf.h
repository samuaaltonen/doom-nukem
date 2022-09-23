/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:23:37 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:36:45 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define DEFAULT_FD 1
# define MSG_ALLOC_FAILED "Failed to allocate memory."
# define LENGTH_SIZE_T 0
# define LENGTH_CHAR 1
# define LENGTH_SHORT 2
# define LENGTH_LONG 3
# define LENGTH_LONG_LONG 4
# define LENGTH_LONG_DOUBLE 5
# include <stdarg.h>
# include "libft.h"

typedef struct s_conf
{
	va_list	ap;
	int		fd;
	int		n;
	int		width;
	int		length;
	int		precision;
	int		flag_hashtag;
	int		flag_zeropadded;
	int		flag_zeropadded_override;
	int		flag_leftadjusted;
	int		flag_addspace;
	int		flag_addsign;
	int		is_uppercase;
	int		is_negative;
	int		is_nan;
	int		is_inf;
}	t_conf;

typedef struct s_dispatch_identifier
{
	char	identifier;
	void	(*function)(t_conf*);
}	t_dispatch_identifier;

typedef struct t_color_identifier
{
	char	*identifier;
	char	*color;
}	t_color_identifier;

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);

int					ft_printf_init_conf(t_conf **conf);
void				ft_printf_reset_conf(t_conf *conf);

void				handle_color(t_conf *conf, char **cursor);
void				handle_flags(t_conf *conf, char **cursor);
void				handle_width(t_conf *conf, char **cursor);
void				handle_precision(t_conf *conf, char **cursor);
void				handle_length(t_conf *conf, char **cursor);
void				handle_conversion(t_conf *conf, char **cursor);

long long			get_va_arg(t_conf *conf);
unsigned long long	get_va_arg_unsigned(t_conf *conf);

void				ft_printf_exit_error(char *message);
void				out_char(char c, t_conf *conf);
void				out_char_repeat(char c, int repeat, t_conf *conf);
void				out_str(char *str, t_conf *conf);
void				out_str_case(char *str, int is_uppercase, t_conf *conf);

void				ft_printf_print_str(t_conf *conf, char *str, int len);

void				conversion_percent(t_conf *conf);
void				conversion_string(t_conf *conf);
void				conversion_char(t_conf *conf);
void				conversion_pointer(t_conf *conf);
void				conversion_n(t_conf *conf);
void				conversion_hexadecimal(t_conf *conf);
void				conversion_hexadecimal_lower(t_conf *conf);
void				conversion_hexadecimal_upper(t_conf *conf);
void				conversion_octal(t_conf *conf);
void				conversion_int(t_conf *conf);
void				conversion_unsigned(t_conf *conf);
void				conversion_unsigned_capital_u(t_conf *conf);
void				conversion_float(t_conf *conf);
void				conversion_binary(t_conf *conf);
void				conversion_anybase(t_conf *conf);

#endif
