/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_index.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_fill_arr(t_stack *a, int *arr)
{
	int	i;

	i = 0;
	while (a)
	{
		arr[i] = a->value;
		i++;
		a = a->next;
	}
}

static void	ft_isort(int *arr, int n)
{
	int	i;
	int	j;
	int	tmp;

	i = 1;
	while (i < n)
	{
		j = i;
		while (j > 0 && arr[j - 1] > arr[j])
		{
			tmp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;
			j--;
		}
		i++;
	}
}

void	ft_assign_index(t_stack **a)
{
	t_stack	*curr;
	int		*sorted;
	int		n;
	int		i;

	n = ft_stack_size(*a);
	sorted = malloc(sizeof(int) * n);
	if (!sorted)
		ft_error_exit(a, NULL);
	ft_fill_arr(*a, sorted);
	ft_isort(sorted, n);
	curr = *a;
	while (curr)
	{
		i = 0;
		while (i < n && sorted[i] != curr->value)
			i++;
		curr->index = i;
		curr = curr->next;
	}
	free(sorted);
}
