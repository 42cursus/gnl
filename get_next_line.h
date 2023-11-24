/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:57:29 by abelov            #+#    #+#             */
/*   Updated: 2023/11/20 21:57:31 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <limits.h>
#include <stddef.h>
#include <stddef.h>
#include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif //BUFFER_SIZE

# ifndef MAXC
#  define MAXC 80
# endif //MAXC
# define OFFSET_IS_CORRECT	0x1000		/* set iff _offset is in fact correct */
typedef struct s_string_glue {
	char						*data;
	struct s_string_glue		*next;
}	t_string_list_node;

/*
 * FT_IO_FILE object type capable of recording all the information needed to
 * control a stream, including its file position indicator, a pointer to its
 * associated buffer (if any), an error indicator that records whether a
 * read/write error has occurred, and an end-of-file indicator that records
 * whether the end of the file has been reached;
 */
typedef struct s_ft_io_file {
	size_t			_r;
	int				_offset;
	void			*_cookie;
	ssize_t			(*_read)(void*, char*, int);
	char	*ptr;
	short			_flags;
	short			_file;
	struct {
		char	*base;
		int				size;
	}	s_buf;
	struct {
		char	*base;
		int				size;
	}	s_line_buf;
}	t_ft_file;

typedef struct s_pointers
{
	char			*s;
	unsigned char	*p;
	unsigned char	*t;
}						t_pointers;

# define NOT_SAFE	0x0000
# define SAFE_TO_READ	0x0004
# define SAFE_TO_WRITE	0x0008
/* RD and WR are never simultaneously asserted */
# define SAFE_TO_READ_AND_WRITE	0x0010
# define FOUND_EOF	0x0020		/* found EOF */
# define FOUND_ERR	0x0040		/* found error */
# define MALLOC_BUF	0x0080		/* _buf is from malloc */
# define OFFSET_IS_CORRECT	0x1000		/* set iff _offset is in fact correct */

/* The value returned by fgetc and similar functions to indicate the
   end of the file.  */
#define EOF (-1)

char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	*ft_memchr(const void *s, int c, size_t n);
ssize_t	ft_fread(void *cookie, char *buf, int n);
t_ft_file	*ft_prep_fp(short fd);
int		ft_fclose(t_ft_file *fp);
char	*get_next_line(int fd);
char	*get_string(char *buf, t_ft_file *fp, size_t len, t_pointers pointers);
char	*ft_fget_string(char *buf, size_t n, t_ft_file *fp);
#endif //GET_NEXT_LINE_H