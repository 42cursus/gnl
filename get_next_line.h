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
#include <limits.h>
#include <stddef.h>

char	*get_next_line(int fd);
#endif //GET_NEXT_LINE_H