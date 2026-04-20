/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_get_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

char	*ft_get_line(int fd)
{
	char	*line;
	char	buf[2];
	int		i;
	int		ret;

	line = malloc(LINEBUF_SIZE);
	if (!line)
		return (NULL);
	i = 0;
	ret = read(fd, buf, 1);
	while (ret > 0 && buf[0] != '\n')
	{
		if (i < LINEBUF_SIZE - 1)
			line[i++] = buf[0];
		ret = read(fd, buf, 1);
	}
	line[i] = '\0';
	if (ret <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
