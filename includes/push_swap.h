/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* push_swap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: fli <fli@student.42barcelona.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/* Created: 2024/01/01 00:00:00 by fli               #+#    #+#             */
/* Updated: 2024/01/01 00:00:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define MAX_NUM_LEN 20

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

/* stack utils */
t_stack	*ft_stack_new(int value);
void	ft_stack_add_back(t_stack **lst, t_stack *new_node);
int		ft_stack_size(t_stack *stack);
void	ft_free_stack(t_stack **stack);
void	ft_error_exit(t_stack **a, t_stack **b);

/* parse utils */
long	ft_atol(const char *str);
int		ft_is_valid_num(char *str);

/* parse */
void	ft_parse_args(int argc, char **argv, t_stack **a, t_stack **b);
int		ft_has_duplicates(t_stack *a);

/* operations: swap */
void	ft_sa(t_stack **a);
void	ft_sb(t_stack **b);
void	ft_ss(t_stack **a, t_stack **b);

/* operations: push */
void	ft_pa(t_stack **a, t_stack **b);
void	ft_pb(t_stack **a, t_stack **b);

/* operations: rotate */
void	ft_ra(t_stack **a);
void	ft_rb(t_stack **b);
void	ft_rr(t_stack **a, t_stack **b);

/* operations: reverse rotate */
void	ft_rra(t_stack **a);
void	ft_rrb(t_stack **b);
void	ft_rrr(t_stack **a, t_stack **b);

/* sort */
void	ft_assign_index(t_stack **a);
int		ft_is_sorted(t_stack *a);
void	ft_sort_two(t_stack **a);
void	ft_sort_three(t_stack **a);
void	ft_sort_small(t_stack **a, t_stack **b);
void	ft_radix_sort(t_stack **a, t_stack **b);
void	ft_sort(t_stack **a, t_stack **b);

#endif
