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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif //BUFFER_SIZE
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define	__SLBF	0x0001		/* line buffered */
# define	__SNBF	0x0002		/* unbuffered */
# define	__SEOF	0x0020		/* found EOF */
# define	__SERR	0x0040		/* found error */
# define	__SMBF	0x0080		/* _buf is from malloc */
# define	__SMOD	0x2000		/* true => fgetln modified _p text */

/* stdio buffers */
typedef struct s_buf {
	unsigned char *_base;
	int	_size;
} t_buf;

/*
 * _IO_FILE object type capable of recording all the information needed to
 * control a stream, including its file position indicator, a pointer to its
 * associated buffer (if any), an error indicator that records whether a
 * read/write error has occurred, and an end-of-file indicator that records
 * whether the end of the file has been reached;
 */
typedef struct s_io_file {
	int				_r;
	void			*_cookie;
	int				(*_close)(void*);
	int				(*_read)(void*, char*, int);
	unsigned char	*ptr;
	short			_flags;
	short			_file;
	unsigned char	nbuf[1];
	t_buf			sbf;
	t_buf			lbf;
}							t_fp;

char	*get_next_line(int fd);
#endif //GET_NEXT_LINE_H