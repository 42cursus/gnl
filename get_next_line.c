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

char *get_next_line(int fd)
{
	char	*buf = NULL;

	if (fd > SHRT_MAX || fd < 0)
		return (NULL);
	if (!buf)
	{
		 buf = (char *) malloc(1);
		 *buf = '\0';
	}
	return (buf);
}
