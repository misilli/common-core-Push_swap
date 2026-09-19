NAME		= push_swap
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

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
			  bench.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re
