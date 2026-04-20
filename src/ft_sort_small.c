/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_sort_small.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_two(t_stack **a)
{
	if ((*a)->index > (*a)->next->index)
		ft_sa(a);
}

static int	ft_find_min_pos(t_stack *a)
{
	int	min_pos;
	int	min_idx;
	int	pos;

	min_pos = 0;
	min_idx = a->index;
	pos = 0;
	while (a)
	{
		if (a->index < min_idx)
		{
			min_idx = a->index;
			min_pos = pos;
		}
		pos++;
		a = a->next;
	}
	return (min_pos);
}

static void	ft_push_min(t_stack **a, t_stack **b, int size)
{
	int	pos;

	pos = ft_find_min_pos(*a);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ft_ra(a);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			ft_rra(a);
	}
	ft_pb(a, b);
}

void	ft_sort_small(t_stack **a, t_stack **b)
{
	int	size;

	size = ft_stack_size(*a);
	if (size == 2)
		ft_sort_two(a);
	else if (size == 3)
		ft_sort_three(a);
	else if (size == 4)
	{
		ft_push_min(a, b, size);
		ft_sort_three(a);
		ft_pa(a, b);
	}
	else
	{
		ft_push_min(a, b, size);
		ft_push_min(a, b, size - 1);
		ft_sort_three(a);
		ft_pa(a, b);
		ft_pa(a, b);
	}
}
