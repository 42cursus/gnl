/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:57:00 by abelov            #+#    #+#             */
/*   Updated: 2023/11/20 21:57:05 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * The ft_memchr() function scans the initial n bytes of the memory area
 * pointed to by s for the first instance of c. Both c and the  bytes  of
 * the memory area pointed to by s are interpreted as unsigned char.
 * Returns a pointer to the matching byte or NULL
 * if the character does not occur in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p = s;

	if (n != 0)
	{
		while (n-- != 0)
			if (*p++ == (unsigned char)c)
				return ((void *)(p - 1));
	}
	return (NULL);
}

/**
 * The ft_memcpy() copies n bytes from memory area src to memory area dest.
 * The memory areas must not overlap otherwise use ft_memmove().
 * ISO/IEC 9899:2023 Programming languages - C
 * https://news.ycombinator.com/item?id=36451907
 * https://stackoverflow.com/
 * questions/54964262/implement-memcpy-is-unsigned-char-needed-or-just-char
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *const			save_pointer = dest;
	const unsigned char	*s = src;

	if (!src && !dest)
		return (NULL);
	while (n-- > 0)
		*(unsigned char *)dest++ = *s++;
	return (save_pointer);
}

int	lbchange(t_fp *fp, size_t newsize, int flag)
{
	if ((size_t)fp->lbf._size >= newsize && (flag & LINE_BUF))
		return (0);
	if ((size_t)fp->lbf._size <= newsize && (flag ^ LINE_BUF))
		return (0);
	fp->lbf._base = ft_reallocarray(fp->lbf._base, fp->lbf._size,
			newsize, sizeof(char));
	if (!fp->lbf._base)
		return (-1);
	fp->lbf._size = newsize;
	return (0);
}

void	*ft_reallocarray(void *ptr,
						size_t oldnmemb, size_t newnmemb, size_t size)
{
	void	*new_ptr;
	size_t	newsize;
	size_t	oldsize;

	if (!ptr)
		return (malloc(newnmemb * size));
	oldsize = oldnmemb * size;
	newsize = newnmemb * size;
	if ((oldsize / size) != oldsize
		|| ((newsize / size) != newsize))
		return (NULL);
	new_ptr = malloc(newsize);
	if (new_ptr == NULL)
		return (NULL);
	if (newsize > oldsize)
		ft_memcpy(new_ptr, ptr, oldsize);
	else
		ft_memcpy(new_ptr, ptr, newsize);
	free(ptr);
	return (new_ptr);
}

int	get_str(t_fp *fp, size_t len, size_t offset)
{
	unsigned char	*p;

	p = ft_memchr(fp->ptr, '\n', fp->_r);
	if (!p)
		return (0);
	len = ++p - fp->ptr;
	lbchange(fp, len + 1, LINE_BUF);
	(void)ft_memcpy(fp->lbf._base + offset, fp->ptr, len);
	fp->lbf._base[offset + len] = '\0';
	fp->_r -= (int)(p - fp->ptr);
	fp->ptr = p;
	return (1);
}
