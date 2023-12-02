/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:57:29 by abelov            #+#    #+#             */
/*   Updated: 2023/12/02 17:06:47 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif //BUFFER_SIZE
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

/**
 * The Linux kernel's current default RLIMIT_NOFILE resource limit for
 * userspace processes is set to 1024 (soft) and 4096 (hard).
 * https://github.com/systemd/systemd/blob/main/NEWS#L7942
 * However, on many Linux systems running systemd v240 or newer (since 2019),
 * this translates into a hard limit of 2^30 (1073741816).
 * https://stackoverflow.com/questions/20000077/fopen-max-and-sc-open-max
 * https://man7.org/linux/man-pages/man2/setrlimit.2.html
 * #include <unistd.h>
 * #include <stdio.h>
 * #include <sys/resource.h>
 *
 * int  main(void )
 * {
 *   struct rlimit  limit;
 *
 *   printf("_SC_OPEN_MAX: %ld\n", sysconf(_SC_OPEN_MAX)); //_SC_OPEN_MAX: 1024
 *   if (!getrlimit(RLIMIT_NOFILE, &limit)) {
 *     printf("RLIMIT_NOFILE: rlim_max %lu\n", limit.rlim_max); // 1048576
 *     printf("RLIMIT_NOFILE: rlim_cur %lu\n", limit.rlim_cur); // 1024
 *   }
 *   return (0);
 * }
 *
 * one can also test limits with bash:
 * `ulimit -n` - soft limit
 * `ulimit -Hn` - hard limit
 */
# define MY_OPEN_MAX 4096
# define OPTIMISTIC 80
# define DO_SHRINK	0x0001		/* line buffered */
# define UN_BUF	0x0002		/* unbuffered */
# define FOUND_EOF	0x0020		/* found EOF */
# define FOUND_ERR	0x0040		/* found error */
# define MBF	0x0080		/* _buf is from malloc */
# define SMOD	0x2000		/* true => fgetln modified _p text */

/* stdio buffers */
typedef struct s_buf {
	unsigned char	*_base;
	int				_size;
}	t_buf;

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
	unsigned char	nbuf[MY_OPEN_MAX][1];
	t_buf			sbf;
	t_buf			lbf;
}							t_fp;

char	*get_next_line(int fd);
int		get_str(t_fp *fp, size_t len, size_t offset);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		lbchange(t_fp *fp, size_t newsize, int flag);
void	*ft_reallocarray(void *ptr,
			size_t oldnmemb, size_t newnmemb, size_t size);
#endif //GET_NEXT_LINE_BONUS_H
