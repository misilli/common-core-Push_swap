/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azdursun <azdursun@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:04:51 by azdursun          #+#    #+#             */
/*   Updated: 2026/09/21 09:50:36 by azdursun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_list
{
	int				content;
	int				index;
	struct s_list	*next;
}	t_list;

typedef struct s_counter
{
	int	sa_count;
	int	sb_count;
	int	ss_count;
	int	pa_count;
	int	pb_count;
	int	ra_count;
	int	rb_count;
	int	rr_count;
	int	rra_count;
	int	rrb_count;
	int	rrr_count;
}	t_counter;

typedef struct s_main
{
	t_list		*a;
	t_list		*b;
	char		**flags;
	char		*bench;
	char		*algorithm;
	int			fcount;
	double		disorder;
	t_counter	*counts;
}	t_main;

/* moves */
void	ft_lstswap(t_list **lst);
int		sa(t_list **a_st);
int		sb(t_list **b_st);
int		ss(t_list **a_st, t_list **b_st);
void	ft_atob(t_list **ap, t_list **bp);
int		pa(t_list **a_st, t_list **b_st);
int		pb(t_list **a_st, t_list **b_st);
void	rotate(t_list **lst);
int		ra(t_list **a_st);
int		rb(t_list **b_st);
int		rr(t_list **a_st, t_list **b_st);
void	reverse_rotate(t_list **lst);
int		rra(t_list **a_st);
int		rrb(t_list **b_st);
int		rrr(t_list **a_st, t_list **b_st);

/* parsing */
char	***flag_finder(char **argv);
int		flag_control(char ***temp, t_main **data);
int		is_valid_number_token(char *token, t_main *state);
int		is_valid_number(char *s);
int		ft_atoi(const char *str);
t_list	*ft_lstnew(int content);
int		ft_lstadd_back(t_list **lst, t_list *new_node);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

/* utils */
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
int		ft_isdigit(int c);
int		ft_lstsize(t_list *lst);
void	ft_index(t_list *stack);
double	compute_disorder(t_list *a);
int		ft_has_duplicates(t_list *a);
void	ft_putstr(char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_error(void);

/* memory */
void	free_stack(t_list **stack);
void	free_args(char ***args);
void	free_all(char ***args, t_main *data);

/* algorithms & bench */
int		ft_set_algorithm(t_main *data);
int		ft_run_algorithm(t_main *data);
int		simple(t_list **a, t_list **b, t_counter *counts);
void	ft_bench(t_main *data);
char	*strategy_name(char *algorithm);
char	*strategy_class(char *strategy);

#endif