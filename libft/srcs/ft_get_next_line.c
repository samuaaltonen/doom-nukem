/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:54:16 by saaltone          #+#    #+#             */
/*   Updated: 2022/01/17 12:49:02 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	gnl_clear_lst(t_gnl_list **lst, int fd, int nl_stop, int return_i)
{
	t_gnl_list	*l;
	t_gnl_list	*tmp;
	size_t		move;

	l = *lst;
	while (l)
	{
		if (l->fd != fd)
		{
			l = l->next;
			continue ;
		}
		tmp = l;
		move = ft_memchr_len(l->content, '\n', l->content_size) + 1;
		if (nl_stop && ft_memchr((l->content), '\n', l->content_size)
			&& move < l->content_size)
		{
			ft_memmove(l->content, l->content + move, l->content_size - move);
			l->content_size = l->content_size - move;
			break ;
		}
		l = tmp->next;
		ft_lstpop((t_list **)lst, (t_list **)&tmp, ft_bzerofree);
	}
	return (return_i);
}

static int	gnl_create_line(t_gnl_list **lst, char **line, int fd)
{
	size_t		len;
	t_gnl_list	*l;

	len = 0;
	l = *lst;
	while (l)
	{
		if (l->fd == fd)
			len += ft_memchr_len(l->content, '\n', l->content_size);
		l = l->next;
	}
	*line = ft_strnew(len);
	if (!(*line))
		return (0);
	l = *lst;
	while (l)
	{
		if (l->fd == fd)
		{
			len = ft_memchr_len(l->content, '\n', l->content_size);
			ft_strncat(*line, l->content, len);
		}
		l = l->next;
	}
	return (1);
}

static int	gnl_check_lst(t_gnl_list **lst, int fd, int check_nl)
{
	t_gnl_list	*l;

	l = *lst;
	while (l)
	{
		if (l->fd == fd)
		{
			if (!check_nl)
				return (1);
			if (check_nl
				&& ft_memchr((char *)(l->content), '\n', l->content_size))
				return (1);
		}
		l = l->next;
	}
	return (0);
}

static int	gnl_append_lst(t_gnl_list **lst, void *content, size_t size, int fd)
{
	t_gnl_list	*new;

	new = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!new)
		return (0);
	new->content = NULL;
	new->content_size = 0;
	new->next = NULL;
	new->fd = fd;
	if (content && size)
	{
		new->content = ft_memalloc(size);
		if (!(new->content))
		{
			free(new);
			return (0);
		}
		ft_memcpy(new->content, content, size);
		new->content_size = size;
	}
	ft_lstput((t_list **)lst, (t_list *)new);
	return (1);
}

int	ft_get_next_line(const int fd, char **line)
{
	int					read_count;
	char				buf[BUFF_SIZE];
	static t_gnl_list	*buff_list;

	if (!line || fd < 0 || BUFF_SIZE < 1)
		return (-1);
	read_count = 1;
	while (!buff_list || !gnl_check_lst(&buff_list, fd, 1))
	{
		read_count = read(fd, buf, BUFF_SIZE);
		if (read_count == 0 && gnl_check_lst(&buff_list, fd, 0))
			break ;
		if (read_count <= 0)
		{
			gnl_clear_lst(&buff_list, fd, 0, 0);
			return (read_count);
		}
		if (!gnl_append_lst(&buff_list, buf, read_count, fd))
			return (gnl_clear_lst(&buff_list, fd, 0, -1));
	}
	if (!gnl_create_line(&buff_list, line, fd))
		return (gnl_clear_lst(&buff_list, fd, 0, -1));
	gnl_clear_lst(&buff_list, fd, 1, 0);
	return (1);
}
