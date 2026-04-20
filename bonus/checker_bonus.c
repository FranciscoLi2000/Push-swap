/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* checker_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static int	ft_is_sorted_val(t_stack *a)
{
	while (a && a->next)
	{
		if (a->value > a->next->value)
			return (0);
		a = a->next;
	}
	return (1);
}

static int	ft_apply_all_ops(t_stack **a, t_stack **b)
{
	char	*line;

	line = ft_get_line(0);
	while (line)
	{
		if (!ft_exec_op(line, a, b))
		{
			free(line);
			return (0);
		}
		free(line);
		line = ft_get_line(0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	ft_parse_args(argc, argv, &a, &b);
	if (!ft_apply_all_ops(&a, &b))
	{
		ft_free_stack(&a);
		ft_free_stack(&b);
		write(2, "Error\n", 6);
		return (1);
	}
	if (ft_is_sorted_val(a) && !b)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	ft_free_stack(&a);
	ft_free_stack(&b);
	return (0);
}
