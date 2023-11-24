/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:56:33 by abelov            #+#    #+#             */
/*   Updated: 2023/11/20 21:56:35 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static inline void	*free_and_return(t_string_list_node *node)
{
	free(node);
	return (NULL);
}

size_t	ft_strcspn(const char *s1, const char *s2)
{
	const char	*s;
	const char	*c;

	s = s1;
	while (*s1)
	{
		c = s2;
		while (*c)
		{
			if (*s1 == *c)
				break ;
			c++;
		}
		if (*c)
			break ;
		s1++;
	}
	return (s1 - s);
}

int	ft_fclose(t_ft_file *fp)
{
	int	r;

	if (fp->_flags == 0)
		return (EOF);
	r = 0;
	if (fp->_flags & MALLOC_BUF)
		free((char *)fp->s_buf.base);
	fp->_r = 0;
	fp->_flags = 0;
	return (r);
}

#include <stdio.h>

char *get_next_line(int fd)
{
	t_ft_file			*fp;
	char				buf[MAXC] = {0};
	size_t				len;
	t_string_list_node	*node;
	char * string;

	if (fd < 0 || fd > SHRT_MAX || read(fd, 0,0 ) < 0)
		return (NULL);
	fp = ft_prep_fp((short)fd);
	if (fp == NULL)
		return (NULL);

	len = 0;
	node = (t_string_list_node *)malloc(sizeof(t_string_list_node));
	if (!node)
		return (NULL);
	string = ft_fget_string(buf, MAXC, fp);
	if (string)
	{
		len = ft_strcspn(buf, "\n");
		buf[len] = 0;
		node->data = (char *)malloc(len + 1);
		if (!node->data)
		{
			free_and_return(node);
			return (data);
		}
		node->data = ft_strncpy(node->data, buf, len + 1);
		node->next = (NULL);
	}
	free(data);
	data = node->data;
	free_and_return(node);
	ft_fclose(fp);
	free(fp);
	if (string != buf)
		free(string);
	return (data);
}
