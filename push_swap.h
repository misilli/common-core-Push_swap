#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <stdlib.h>

typedef struct s_list
{
	int		content;
	int		index;
	struct s_list	*next;
} t_list;
typedef struct s_counter
{
	int sa_count;
	int sb_count;
	int ss_count;
	int pa_count;
	int pb_count;
	int ra_count;
	int rb_count;
	int rr_count;
	int rra_count;
	int rrb_count;
	int rrr_count;
} t_counter;

typedef struct s_main
{
	t_list	*a;
	t_list	*b;
	char	**flags;
	char	*bench;
	char	*algorithm;
	int		fcount;
	double	disorder;
	t_counter	*counts;
} t_main;

void	ft_error(void);
void	ft_putstr(char *s);
void	ft_lstswap(t_list **lst);
int		sa(t_list **a_st);
int		sb(t_list **b_st);
int		ss(t_list **a_st, t_list **b_st);
void	ft_atob(t_list **ap, t_list **bp);
int		pa(t_list **a_st, t_list **b_st);
int		pb(t_list **a_st, t_list **b_st);
unsigned int	ft_lstsize(t_list *lst);
void	rotate(t_list **lst);
int		ra(t_list **a_st);
int		rb(t_list **b_st);
int		rr(t_list **a_st, t_list **b_st);
void	reverse_rotate(t_list **lst);
int		rra(t_list **a_st);
int		rrb(t_list **b_st);
int		rrr(t_list **a_st, t_list **b_st);

char	***flagbulucu(char **argv);
int		flagkontrol(char ***temp, t_main **arguments2);
int		ft_atoi(const char *str);
int		ft_lstadd_back(t_list **lst, t_list *new_node);
t_list	*ft_lstnew(int content);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_isdigit(int c);
double	compute_disorder(t_list *a);
void	ft_index(t_list *stack);
int		ft_set_algorithm(t_main *arguments2);
int		ft_adaptive(t_main *arguments2);
int		ft_run_algorithm(t_main *arguments2);
void		ft_bench(t_main *data);
int simple(t_list **a, t_list **b, t_counter *counts);

#endif
