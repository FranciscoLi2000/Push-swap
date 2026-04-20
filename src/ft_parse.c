/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* ft_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_has_duplicates(t_stack *a)
{
	t_stack	*curr;
	t_stack	*tmp;

	curr = a;
	while (curr)
	{
		tmp = curr->next;
		while (tmp)
		{
			if (curr->value == tmp->value)
				return (1);
			tmp = tmp->next;
		}
		curr = curr->next;
	}
	return (0);
}

static void	ft_parse_word(char *word, t_stack **a, t_stack **b)
{
	t_stack	*node;
	long	n;

	if (!ft_is_valid_num(word))
		ft_error_exit(a, b);
	n = ft_atol(word);
	node = ft_stack_new((int)n);
	if (!node)
		ft_error_exit(a, b);
	ft_stack_add_back(a, node);
}

static void	ft_parse_str(char *str, t_stack **a, t_stack **b)
{
	int		i;
	int		j;
	char	word[20];

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break ;
		j = 0;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
		{
			if (j >= 19)
				ft_error_exit(a, b);
			word[j++] = str[i++];
		}
		word[j] = '\0';
		ft_parse_word(word, a, b);
	}
}

void	ft_parse_args(int argc, char **argv, t_stack **a, t_stack **b)
{
	int	i;

	if (argc < 2)
		return ;
	if (argc == 2)
		ft_parse_str(argv[1], a, b);
	else
	{
		i = 1;
		while (i < argc)
		{
			ft_parse_word(argv[i], a, b);
			i++;
		}
	}
	if (ft_has_duplicates(*a))
		ft_error_exit(a, b);
}
