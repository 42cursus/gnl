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


void	makebuf(t_fp *fp)
{
	void	*p;

	p = malloc(BUFFER_SIZE);
	if (!p)
	{
		fp->_flags |= __SNBF;
		fp->ptr = fp->nbuf;
		fp->sbf._base = fp->ptr;
		fp->sbf._size = 1;
		return;
	}
	fp->_flags |= __SMBF;
	fp->ptr = p;
	fp->sbf._base = p;
	fp->sbf._size = BUFFER_SIZE;
}

int	refill(t_fp *fp)
{
	if (fp->sbf._base == NULL)
		makebuf(fp);
	fp->_r = read(fp->_file, (char *)fp->ptr, fp->sbf._size);
	fp->_flags &= ~__SMOD;	/* buffer contents are again pristine */
	if (fp->_r <= 0) {
		if (fp->_r == 0)
			fp->_flags |= __SEOF;
		else {
			fp->_r = 0;
			fp->_flags |= __SERR;
		}
		return (EOF);
	}
	return (0);
}

t_fp	*sfp(int fd)
{
	t_fp	*fp;

	fp = (t_fp *)malloc(sizeof(t_fp) * 1);
	if (!fp)
		return (NULL);
	fp->ptr = NULL;
	fp->_flags = 1;
	fp->_r = 0;
	fp->sbf._base = NULL;
	fp->sbf._size = 0;
	fp->_file = fd;
	fp->lbf._base = NULL;
	fp->lbf._size = 0;
	return (fp);
}

char *get_next_line(int fd)
{
	static t_fp	*fp = NULL;
	char		*buf;

	if (fd > SHRT_MAX || fd < 0)
		return (NULL);
	if (!fp)
		fp = sfp(fd);
	refill(fp);
	buf = (char *)fp->lbf._base;
	if (fp->_flags & __SNBF)
	{
		buf = (char *) malloc(1);
		if (!buf)
			return (NULL);
		*buf = '\0';
	}
	return (buf);
}
