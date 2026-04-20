NAME		= push_swap
CHECKER		= checker
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./includes -I./libft

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		=	src/ft_main.c \
				src/ft_parse.c \
				src/ft_parse_utils.c \
				src/ft_stack_utils.c \
				src/ft_ops_swap.c \
				src/ft_ops_push.c \
				src/ft_ops_rotate.c \
				src/ft_ops_rrotate.c \
				src/ft_index.c \
				src/ft_sort.c \
				src/ft_sort_small.c

BONUS_SRCS	=	bonus/checker_bonus.c \
				bonus/ft_apply_bonus.c \
				bonus/ft_exec_op_bonus.c \
				bonus/ft_get_line_bonus.c \
				src/ft_parse.c \
				src/ft_parse_utils.c \
				src/ft_stack_utils.c

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft -o $(CHECKER)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(CHECKER)

re: fclean all

.PHONY: all bonus clean fclean re
