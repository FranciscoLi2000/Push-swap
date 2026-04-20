/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_ops_rrotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_rrotate(t_stack **s)
{
	t_stack	*tmp;
	t_stack	*prev;

	tmp = *s;
	prev = NULL;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = NULL;
	tmp->next = *s;
	*s = tmp;
}

void	ft_rra(t_stack **a)
{
	if (!*a || !(*a)->next)
		return ;
	ft_rrotate(a);
	write(1, "rra\n", 4);
}

void	ft_rrb(t_stack **b)
{
	if (!*b || !(*b)->next)
		return ;
	ft_rrotate(b);
	write(1, "rrb\n", 4);
}

void	ft_rrr(t_stack **a, t_stack **b)
{
	if (*a && (*a)->next)
		ft_rrotate(a);
	if (*b && (*b)->next)
		ft_rrotate(b);
	write(1, "rrr\n", 4);
}
