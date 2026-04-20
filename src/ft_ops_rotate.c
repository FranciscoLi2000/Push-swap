/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_ops_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_rotate(t_stack **s)
{
	t_stack	*tmp;
	t_stack	*last;

	tmp = *s;
	*s = tmp->next;
	tmp->next = NULL;
	last = *s;
	while (last->next)
		last = last->next;
	last->next = tmp;
}

void	ft_ra(t_stack **a)
{
	if (!*a || !(*a)->next)
		return ;
	ft_rotate(a);
	write(1, "ra\n", 3);
}

void	ft_rb(t_stack **b)
{
	if (!*b || !(*b)->next)
		return ;
	ft_rotate(b);
	write(1, "rb\n", 3);
}

void	ft_rr(t_stack **a, t_stack **b)
{
	if (*a && (*a)->next)
		ft_rotate(a);
	if (*b && (*b)->next)
		ft_rotate(b);
	write(1, "rr\n", 3);
}
