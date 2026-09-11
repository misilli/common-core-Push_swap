/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumidill <mumidill@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 00:34:33 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/11 00:34:33 by mumidill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_list
{
	int				content;
	struct s_list	*next;
}					t_list;

void				ft_lstswap(t_list **lst);
void				ft_putstr(char *s);
int					sa(t_list **a_st);
int					sb(t_list **b_st);
int					ss(t_list **a_st, t_list **b_st);
void				ft_atob(t_list **ap, t_list **bp);
int					pa(t_list **a_st, t_list **b_st);
int					pb(t_list **a_st, t_list **b_st);
unsigned int		ft_lstsize(t_list *lst);
void				rotate(t_list **lst);
int					ra(t_list **a_st);
int					rb(t_list **b_st);
int					rr(t_list **a_st, t_list **b_st);
void				reverse_rotate(t_list **lst);
int					rra(t_list **a_st);
int					rrb(t_list **b_st);
int					rrr(t_list **a_st, t_list **b_st);
