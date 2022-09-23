/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:42:36 by saaltone          #+#    #+#             */
/*   Updated: 2022/08/04 14:28:58 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 255
# define COLOR_BLACK "\033[0;30m"
# define COLOR_RED "\033[0;31m"
# define COLOR_GREEN "\033[0;32m"
# define COLOR_YELLOW "\033[0;33m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_PURPLE "\033[0;35m"
# define COLOR_CYAN "\033[0;36m"
# define COLOR_WHITE "\033[0;37m"
# define COLOR_RESET "\033[0m"
# define BG_BLACK "\033[0;40m"
# define BG_RED "\033[0;41m"
# define BG_GREEN "\033[0;42m"
# define BG_YELLOW "\033[0;43m"
# define BG_BLUE "\033[0;44m"
# define BG_PURPLE "\033[0;45m"
# define BG_CYAN "\033[0;46m"
# define BG_WHITE "\033[0;47m"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef enum e_bool {
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef unsigned long long	t_ull;
typedef signed long long	t_sll;

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}	t_list;

typedef struct s_gnl_list
{
	void				*content;
	size_t				content_size;
	struct s_gnl_list	*next;
	int					fd;
}	t_gnl_list;

typedef struct s_array
{
	void	*data;
	int		element_size;
	int		allocated;
	int		used;
}	t_array;

typedef union u_double_cast {
	double	f;
	struct {
		t_ull	mantissa : 52;
		t_ull	exponent : 11;
		t_ull	sign : 1;
	} s_parts;
}	t_double_cast;

typedef union u_ldouble_cast {
	long double	f;
	struct {
		t_ull	mantissa : 63;
		t_ull	int_part : 1;
		t_ull	exponent : 15;
		t_ull	sign : 1;
	} s_parts;
}	t_ldouble_cast;

typedef struct s_superint
{
	int	allocated;
	int	count;
	int	*numbers;
}	t_superint;

typedef struct vector2 {
	double	x;
	double	y;
}	t_vector2;

typedef struct vector3 {
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct matrix2 {
	t_vector2	a;
	t_vector2	b;
}	t_matrix2;

int			ft_get_next_line(const int fd, char **line);
void		ft_putchar(char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr(char const *s);
void		ft_putstr_fd(char const *s, int fd);
void		ft_putendl(char const *s);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putnbr(int n);
void		ft_putnbr_fd(int n, int fd);
void		*ft_memalloc(size_t size);
void		ft_memdel(void **ap);
char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
void		ft_strclr(char *s);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s);
char		**ft_strsplit(char const *s, char c);
char		*ft_itoa(int n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		ft_bzerofree(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
size_t		ft_memchr_len(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strdup(const char *s);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strchr_count(char *str, char c);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_str_isalnum(char *str);
t_list		*ft_lstnew(void const *content, size_t content_size);
void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstadd(t_list **alst, t_list *new_el);
void		ft_lstput(t_list **alst, t_list *new_el);
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int			ft_split_count(char *str, char c);
int			ft_count_digits(long long number);
int			ft_count_digits_ull(unsigned long long number);
int			ft_count_digits_ld(long double number);
void		ft_putstr_color(char *str, char *color);
double		ft_pow(double number, double power);
int			ft_abs(int number);
double		ft_abs_double(double number);
long double	ft_abs_ldouble(long double number);
void		ft_lstpop(t_list **start, t_list **pop, void (*del)(void*, size_t));
int			ft_rgbtoint(int red, int green, int blue);
int			ft_hextoint(char *hex);
int			ft_color_between(float pos, int start, int end);
t_array		*ft_array_create(int element_size, int count);
t_array		*ft_array_expand(t_array **array);
void		*ft_array_insert(t_array **array, void *data);
void		ft_array_foreach(t_array **array, void (*f)(void *));
void		ft_free_array(void **arr);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
int			ft_toggle(int value);
void		ft_append_char(char **str, char append);
char		*ft_itoa_base(long long number, int base);
char		*ft_itoa_base_ull(unsigned long long number, int base, int isneg);
int			ft_floatsign(long double number);
char		*ft_ftoa(long double number, int precision);
long double	ft_floor(long double number);
int			ft_fa_round(char **number, int start, int leftover, int divnotzero);
void		ft_fa_trim(char **str, int precision);
int			ft_log10(long double number);
int			ft_iszero(long double number);
int			ft_ftdiv(long double number, t_superint **n, t_superint **d);
int			ft_ftdiv_scale(int log10, t_superint **n, t_superint **d);
int			ft_ftdiv_logcheck(int *log10, t_superint **n, t_superint **d);
t_superint	*ft_superint_new(t_ull start, int count);
void		ft_superint_destroy(t_superint **superint);
int			ft_superint_expand(t_superint **addto);
void		ft_superint_print(t_superint **superint);
void		ft_superint_swap(t_superint **a, t_superint **b);
int			ft_superint_zero(t_superint **superint);
int			ft_superint_iszero(t_superint **superint);
int			ft_superint_clone(t_superint **to, t_superint **from);
t_ull		ft_superint_to_ull(t_superint **superint);
int			ft_superint_compare(t_superint **a, t_superint **b);
int			ft_superint_plus(t_superint **addto, t_superint **add);
int			ft_superint_plus_int(t_superint **addto, int plus);
int			ft_superint_plus_ull(t_superint **addto, t_ull plus);
int			ft_superint_minus(t_superint **from, t_superint **minus);
int			ft_superint_minus_int(t_superint **from, int minus);
int			ft_superint_minus_int_log10(t_superint **from, int minus, int log);
int			ft_superint_multiply(t_superint **target, t_superint **multiplier);
int			ft_superint_multiply_int(t_superint **target, int multiplier);
int			ft_superint_divide_samesize(t_superint **num, t_superint **denum,
				t_superint **mod, t_ull *result);
int			ft_superint_log10(t_superint **superint);
int			ft_superint_shift(t_superint **target, int shift);
int			ft_superint_shift_block(t_superint **target, int shift);
int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
double		ft_vector_length(t_vector2 a);
t_vector2	ft_vector_multiply_matrix(t_vector2 vector, t_matrix2 matrix);
t_vector2	ft_vector_perpendicular(t_vector2 a);
t_vector2	ft_vector_resize(t_vector2 a, double size);
t_matrix2	ft_matrix_inverse(t_matrix2 matrix);

#endif
