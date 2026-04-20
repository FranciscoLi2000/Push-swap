/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_exec_op_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static int	ft_streq(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == s2[i]);
}

static int	ft_exec_swap_push(char *op, t_stack **a, t_stack **b)
{
	if (ft_streq(op, "sa"))
		ft_apply_swap(a);
	else if (ft_streq(op, "sb"))
		ft_apply_swap(b);
	else if (ft_streq(op, "ss"))
	{
		ft_apply_swap(a);
		ft_apply_swap(b);
	}
	else if (ft_streq(op, "pa"))
		ft_apply_push(b, a);
	else if (ft_streq(op, "pb"))
		ft_apply_push(a, b);
	else
		return (0);
	return (1);
}

static int	ft_exec_rot(char *op, t_stack **a, t_stack **b)
{
	if (ft_streq(op, "ra"))
		ft_apply_rotate(a);
	else if (ft_streq(op, "rb"))
		ft_apply_rotate(b);
	else if (ft_streq(op, "rr"))
	{
		ft_apply_rotate(a);
		ft_apply_rotate(b);
	}
	else if (ft_streq(op, "rra"))
		ft_apply_rrotate(a);
	else if (ft_streq(op, "rrb"))
		ft_apply_rrotate(b);
	else if (ft_streq(op, "rrr"))
	{
		ft_apply_rrotate(a);
		ft_apply_rrotate(b);
	}
	else
		return (0);
	return (1);
}

int	ft_exec_op(char *op, t_stack **a, t_stack **b)
{
	if (!op || !op[0])
		return (0);
	if (ft_exec_swap_push(op, a, b))
		return (1);
	return (ft_exec_rot(op, a, b));
}
