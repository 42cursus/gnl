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

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <bsd/stdlib.h>

/**
 * ft_memset() fills memory with a constant byte,
 * returns a pointer to the memory area s.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*d;

	d = s;
	while (n-- != 0)
		*d++ = (unsigned char)c;
	return (s);
}

static inline bool	check_buf_size(size_t memb, size_t size)
{
	return ((memb >= ((size_t) 1 << (sizeof(size_t) * 4)) || size >= ((size_t) 1
			<< (sizeof(size_t) * 4)))
			&& memb > 0 && SIZE_MAX / memb < size);
}

size_t	calculate_new_size(size_t oldnmemb, size_t newnmemb, size_t size)
{
	size_t	old_size;
	size_t	new_size;

	old_size = oldnmemb * size;
	new_size = newnmemb * size;
	if (new_size <= old_size)
		return (0);
	return (new_size - old_size);
}

void	*allocate_and_copy_data(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	char	*dst;

	new_ptr = (char *)ft_memset(malloc(new_size), '\0', new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		ft_strncpy(new_ptr, ptr, old_size);
		if (new_size > old_size)
		{
			dst = (char *)(new_ptr + old_size);
			ft_memset(dst, 0, new_size - old_size);
		}
	}
	return (new_ptr);
}

void	*ft_recallocarray(void *ptr,
						  size_t oldnmemb, size_t newnmemb, size_t size)
{
	void	*new_ptr;
	size_t	new_size;

	if (check_buf_size(newnmemb, size)
		|| check_buf_size(oldnmemb, size))
		return (NULL);
	new_size = calculate_new_size(oldnmemb, newnmemb, size);
	if (new_size == 0)
		return (ptr);
	new_ptr = allocate_and_copy_data(ptr, oldnmemb * size, new_size);
	if (new_ptr == NULL)
		return (NULL);
	free(ptr);
	return (new_ptr);
}

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


ssize_t	ft_fread(void *cookie, char *buf, int n)
{
	ssize_t			ret;
	t_ft_file	*fp;

	fp = cookie;
	ret = read(fp->_file, buf, n);
	if (ret >= 0)
		fp->_offset += ret;
	else
		fp->_flags &= ~OFFSET_IS_CORRECT;
	return (ret);
}

/*
 * Prepare an FT_FILE for ft_fopen()
 */
t_ft_file	*ft_prep_fp(short fd)
{
	t_ft_file	*fp;
	char				*data;

	fp = malloc(sizeof(t_ft_file));
	if (!fp)
		return (NULL);
	data = (char *)malloc(sizeof(char) * 1);
	if (!data)
		return (NULL);
	*data = '\0';
	fp->_r = 0;
	fp->_flags = 1;
	fp->ptr = NULL;
	fp->s_buf.base = data;
	fp->s_buf.size = 1;
	fp->_file = fd;
	fp->_cookie = fp;
	fp->_read = ft_fread;
	fp->s_line_buf.base = NULL;
	fp->s_line_buf.size = 0;
	return (fp);
}

/*
 * Copy src to dest, truncating or null-padding to always copy n bytes.
 * Return dest.
 * If there is no terminating null byte in the first n bytes of src, strncpy()
 * produces an unterminated string in dest.
 * `const char*` is a mutable pointer to an immutable character/string.
 * You cannot change the contents of the location(s) this pointer points to.
 */
char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	const char		*s = src;
	char *const		save_pointer = dest;
	unsigned int	i;

	if(!dest || !src)
		return (NULL);
	i = 0;
	while (*s && (i++ < n))
		*dest++ = *s++;
	while (i++ < n)
		*dest++ = '\0';
	return (save_pointer);
}

char	*get_string(char *buf, t_ft_file *fp, size_t len, t_pointers pointers)
{
	len = ++pointers.t - pointers.p;
	fp->_r -= len;
	fp->ptr = pointers.t;
	if (!pointers.s) {
		(void) ft_strncpy((void *) pointers.s, (void *) pointers.p, len);
		pointers.s[len] = '\0';
	}
	return (buf);
}

/*
 * Expand the line buffer.  Return -1 on error.
 */
static int	ft_expand_buffer(t_ft_file *fp, int newsize)
{
	void	*p;

	if (fp->s_buf.size >= newsize)
		return (0);
	p = ft_recallocarray(fp->s_buf.base, fp->s_buf.size, newsize, 1);
	if (p == NULL)
		return (-1);
	fp->s_buf.base = p;
	fp->s_buf.size = newsize;
	return (0);
}

int	ft_refill(t_ft_file *fp)
{
	fp->_r = 0;
	if ((fp->_flags & SAFE_TO_READ) == 0)
		fp->_flags |= SAFE_TO_READ;
	if (fp->s_buf.base == NULL)
	{
		ft_expand_buffer(fp, MAXC);
		fp->_flags |= MALLOC_BUF;
	}
	fp->ptr = fp->s_buf.base;
	fp->_r = (*fp->_read)(fp->_cookie, (char *)fp->ptr, fp->s_buf.size);
	if (fp->_r <= 0)
	{
		if (fp->_r == 0)
			fp->_flags |= FOUND_EOF;
		else
		{
			fp->_r = 0;
			fp->_flags |= FOUND_ERR;
		}
		return (EOF);
	}
	return (0);
}


/*
* Read at most n-1 characters from the given file.
* Stop when a newline has been read, or the count runs out.
* Return first argument, or NULL if no characters were read.
* Do not return NULL if n == 1.
*/
char	*ft_fget_string_check(char *buf, size_t n, t_ft_file *fp)
{
	size_t		len;
	t_pointers	pointers;

	pointers.s = buf;
	pointers.p = NULL;
	n--;
	while (n != 0)
	{
		if ((fp->_r) <= 0 && (ft_refill(fp)))
			if (pointers.s == buf) {
				ft_fclose(fp);
				return (NULL);
			}
		if ((fp->_r) <= 0 && (ft_refill(fp)))
			break ;
		len = fp->_r;
		if (len > n)
			len = n;
		pointers.t = ft_memchr(fp->ptr, '\n', len);
		if (pointers.t != NULL)
			return (get_string(buf, fp, len, pointers));
		fp->_r -= len;
		fp->ptr += len;
		(void)ft_strncpy((void *)pointers.s, (void *)pointers.p, len);
		pointers.s += len;
		n -= len;
	}
	*pointers.s = '\0';
	return (buf);
}

char	*ft_fget_string(char *buf, size_t n, t_ft_file *fp)
{
	if (n <= 0)
		return (NULL);
	return (ft_fget_string_check(buf, n, fp));
}