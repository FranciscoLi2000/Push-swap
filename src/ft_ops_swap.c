/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_ops_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_swap(t_stack *s)
{
	int	tmp;

	tmp = s->value;
	s->value = s->next->value;
	s->next->value = tmp;
	tmp = s->index;
	s->index = s->next->index;
	s->next->index = tmp;
}

void	ft_sa(t_stack **a)
{
	if (!*a || !(*a)->next)
		return ;
	ft_swap(*a);
	write(1, "sa\n", 3);
}

void	ft_sb(t_stack **b)
{
	if (!*b || !(*b)->next)
		return ;
	ft_swap(*b);
	write(1, "sb\n", 3);
}

void	ft_ss(t_stack **a, t_stack **b)
{
	if (*a && (*a)->next)
		ft_swap(*a);
	if (*b && (*b)->next)
		ft_swap(*b);
	write(1, "ss\n", 3);
}
