/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_apply_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_apply_swap(t_stack **s)
{
	int	tmp_v;
	int	tmp_i;

	if (!*s || !(*s)->next)
		return ;
	tmp_v = (*s)->value;
	tmp_i = (*s)->index;
	(*s)->value = (*s)->next->value;
	(*s)->index = (*s)->next->index;
	(*s)->next->value = tmp_v;
	(*s)->next->index = tmp_i;
}

void	ft_apply_push(t_stack **from, t_stack **to)
{
	t_stack	*tmp;

	if (!*from)
		return ;
	tmp = *from;
	*from = tmp->next;
	tmp->next = *to;
	*to = tmp;
}

void	ft_apply_rotate(t_stack **s)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*s || !(*s)->next)
		return ;
	tmp = *s;
	*s = tmp->next;
	tmp->next = NULL;
	last = *s;
	while (last->next)
		last = last->next;
	last->next = tmp;
}

void	ft_apply_rrotate(t_stack **s)
{
	t_stack	*tmp;
	t_stack	*prev;

	if (!*s || !(*s)->next)
		return ;
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
