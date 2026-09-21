NAME		= push_swap
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCS		= main.c \
			  error.c \
			  input_numbers.c \
			  argument_flags.c \
			  split_utils.c \
			  string_utils.c \
			  simple.c \
			  swap_moves.c \
			  push_moves.c \
			  rotate_moves.c \
			  reverse_moves.c \
			  bench.c \
			  put_utils.c \
			  strategy_utils.c \
			  complex.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
