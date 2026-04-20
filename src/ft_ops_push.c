/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_ops_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_pa(t_stack **a, t_stack **b)
{
	t_stack	*tmp;

	if (!*b)
		return ;
	tmp = *b;
	*b = tmp->next;
	tmp->next = *a;
	*a = tmp;
	write(1, "pa\n", 3);
}

void	ft_pb(t_stack **a, t_stack **b)
{
	t_stack	*tmp;

	if (!*a)
		return ;
	tmp = *a;
	*a = tmp->next;
	tmp->next = *b;
	*b = tmp;
	write(1, "pb\n", 3);
}
