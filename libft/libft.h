/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* libft.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(const char *s, char c);
void	ft_putstr_fd(const char *s, int fd);

#endif
