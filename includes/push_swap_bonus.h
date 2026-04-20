/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* push_swap_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include "push_swap.h"

# define LINEBUF_SIZE 128

/* bonus: silent stack operations */
void	ft_apply_swap(t_stack **s);
void	ft_apply_push(t_stack **from, t_stack **to);
void	ft_apply_rotate(t_stack **s);
void	ft_apply_rrotate(t_stack **s);

/* bonus: execute operation by name (returns 1=ok, 0=invalid) */
int		ft_exec_op(char *op, t_stack **a, t_stack **b);

/* bonus: read one line from fd (caller must free) */
char	*ft_get_line(int fd);

#endif
