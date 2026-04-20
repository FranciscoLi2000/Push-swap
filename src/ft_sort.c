/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_sort_three_cases(t_stack **a, int top, int mid, int bot)
{
	if (top < mid && mid < bot)
		return ;
	if (top < bot && bot < mid)
	{
		ft_rra(a);
		ft_sa(a);
	}
	else if (mid < top && top < bot)
		ft_sa(a);
	else if (mid < bot && bot < top)
		ft_ra(a);
	else if (bot < top && top < mid)
		ft_rra(a);
	else
	{
		ft_sa(a);
		ft_rra(a);
	}
}

void	ft_sort_three(t_stack **a)
{
	ft_sort_three_cases(a, (*a)->index,
		(*a)->next->index,
		(*a)->next->next->index);
}

void	ft_radix_sort(t_stack **a, t_stack **b)
{
	int	size;
	int	max_bits;
	int	i;
	int	j;

	size = ft_stack_size(*a);
	max_bits = 0;
	i = size - 1;
	while ((i >> max_bits) > 0)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if (((*a)->index >> i) & 1)
				ft_ra(a);
			else
				ft_pb(a, b);
			j++;
		}
		while (*b)
			ft_pa(a, b);
		i++;
	}
}

void	ft_sort(t_stack **a, t_stack **b)
{
	int	size;

	size = ft_stack_size(*a);
	if (size <= 5)
		ft_sort_small(a, b);
	else
		ft_radix_sort(a, b);
}
