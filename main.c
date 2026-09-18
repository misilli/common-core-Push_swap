/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mumidill <mumidill@student.42istanbul.com. +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/09/02 22:09:27 by mumidill          #+#    #+#             */
/*   Updated: 2026/09/02 22:09:27 by mumidill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	int content;
	struct s_list *next;
} t_list;

typedef struct s_main
{
	t_list *a;
	t_list *b;
	char **flags;
	int fcount;

} t_main;
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
	int (*total)(struct s_counter *counter); // buna bir toplama fonksiyonu yaz
} t_counter;
void ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
#pragma region movements.c
void ft_lstswap(t_list **lst)
{
	t_list *first;
	t_list *second;

	if (!lst || !*lst || !(*lst)->next)
		return;
	first = *lst;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*lst = second;
}

int sa(t_list **a_st)
{
	if (a_st == NULL || *a_st == NULL || (*a_st)->next == NULL)
		return (0);
	ft_lstswap(a_st);
	ft_putstr("sa\n");
	return (1);
}

int sb(t_list **b_st)
{
	if (b_st == NULL || *b_st == NULL || (*b_st)->next == NULL)
		return (0);
	ft_lstswap(b_st);
	ft_putstr("sb\n");
	return (1);
}

int ss(t_list **a_st, t_list **b_st)
{
	if (a_st == NULL || *a_st == NULL || (*a_st)->next == NULL)
		return (0);
	if (b_st == NULL || *b_st == NULL || (*b_st)->next == NULL)
		return (0);
	ft_lstswap(a_st);
	ft_lstswap(b_st);
	ft_putstr("ss\n");
	return (1);
}

/*void ft_lstswap(t_list **lst)
{
	t_list *tmp;

	if (!lst || !*lst || !(*lst)->next) What the fuck? You can't be serious.
		return ;						burayı silelim ya lazım olmaz muhtemelen ama kalsın
	tmp = (*lst)->next;       // 2. eleman
	(*lst)->next = tmp->next; // 1. eleman -> 3. eleman
	tmp->next = *lst;         // 2. eleman -> 1. eleman
	*lst = tmp;               // başı 2. elemana al
}*/
void ft_atob(t_list **ap, t_list **bp) // aslında bu push
{
	t_list *temp;
	temp = (*ap)->next;
	(*ap)->next = *bp;
	*bp = *ap;
	*ap = temp;
}

int pa(t_list **a_st, t_list **b_st)
{
	if (!a_st || !b_st || !*b_st)
		return (0);
	ft_atob(b_st, a_st);
	ft_putstr("pa\n");
	return (1);
}

int pb(t_list **a_st, t_list **b_st)
{
	if (!a_st || !b_st || !*a_st)
		return (0);
	ft_atob(a_st, b_st);
	ft_putstr("pb\n");
	return (1);
}

unsigned int ft_lstsize(t_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void rotate(t_list **lst)
{
	t_list *first;
	t_list *last;

	if (!lst || !*lst || !(*lst)->next)
		return;
	first = *lst;
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	*lst = first->next;
	first->next = NULL;
	last->next = first;
}

int ra(t_list **a_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	rotate(a_st);
	ft_putstr("ra\n");
	return (1);
}

int rb(t_list **b_st)
{
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	rotate(b_st);
	ft_putstr("rb\n");
	return (1);
}

int rr(t_list **a_st, t_list **b_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	rotate(a_st);
	rotate(b_st);
	ft_putstr("rr\n");
	return (1);
}

void reverse_rotate(t_list **lst)
{
	t_list *last;

	if (!lst || !*lst || !(*lst)->next)
		return;
	last = *lst;
	while ((last->next)->next != NULL)
	{
		last = last->next;
	}
	(last->next)->next = *lst;
	*lst = last->next;
	last->next = NULL;
}

int rra(t_list **a_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	reverse_rotate(a_st);
	ft_putstr("rra\n");
	return (1);
}

int rrb(t_list **b_st)
{
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	reverse_rotate(b_st);
	ft_putstr("rrb\n");
	return (1);
}

int rrr(t_list **a_st, t_list **b_st)
{
	if (!a_st || !*a_st || !(*a_st)->next)
		return (0);
	if (!b_st || !*b_st || !(*b_st)->next)
		return (0);
	reverse_rotate(a_st);
	reverse_rotate(b_st);
	ft_putstr("rrr\n");
	return (1);
}
#pragma endregion

int ft_atoi(const char *str)
{
	long value;
	int i;
	int sign;

	i = 0;
	value = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = sign * (44 - str[i]);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return (value * sign);
}

t_list *ft_lstnew(int content)
{
	t_list *test;

	test = malloc(sizeof(t_list));
	if (!test)
		return (NULL);
	test->content = content;
	test->next = NULL;
	return (test);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (!lst || !new)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

int siralamacheck(t_list *a)
{
	while (a && a->next)
	{
		if (a->content > a->next->content)
			return (0);
		a = a->next;
	}
	return (1);
}
int ft_getmin(t_list *a)
{
	t_list *head;
	int min;

	head = a;
	if (!head)
		return (0);
	min = head->content;
	while (head)
	{
		if (head->content < min)
			min = head->content;
		head = head->next;
	}
	return (min);
}

size_t ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	while (i + 1 < size && src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	if (size != 0)
	{
		dest[i] = '\0';
	}
	while (src[j])
	{
		j++;
	}
	return (j);
}

void simple(t_list **a, t_list **b)
{
	int enkuck;
	while (*a)
	{
		enkuck = ft_getmin(*a);
		while (enkuck != (*a)->content)
		{
			ra(a);
		}
		pb(a, b);
	}

	while (*b)
	{
		pa(a, b);
	}

	/*int i;
	int len;

	if (!a || !*a || !(*a)->next)
		return ;
	pb(a, b);
	while (*a )
	{
		if ((*a)->next && (*a)->content < (*a)->next->content)
			sa(a);

		if (*b && *a && (*b)->content < (*a)->content)
			pb(a, b);
		else
			ra(a);


	}
	while (*b)
			pa(a, b);
	if (!siralamacheck(*a))
		return ;
	simple(a, b);*/
}

char *ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		while ((i + j) < len && big[i + j] == little[j] && big[i + j] != '\0')
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
		j = 0;
	}
	return (NULL);
}

double compute_disorder(t_list *a)
{
	double total_pairs = 0;
	double mistakes = 0;
	t_list *i;
	t_list *j;

	i = a;
	while (i)
	{
		j = i->next;
		while (j)
		{
			total_pairs++;
			if (i->content > j->content)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	if (total_pairs == 0)
		return (0.0);
	return (mistakes / total_pairs);
}
#pragma region ft_split
static char **free_memory(char **final, int j)
{
	while (j >= 0)
	{
		free(final[j]);
		j--;
	}
	free(final);
	return (NULL);
}

static int ft_wordlen(char const *s, char c)
{
	size_t len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static char **ft_splitfill(char **final, char const *s, char c)
{
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			k = ft_wordlen(s + i, c);
			final[j] = malloc(sizeof(char) * (k + 1));
			if (!final[j])
				return (free_memory(final, j - 1));
			ft_strlcpy(final[j++], s + i, k + 1);
			i = i + k;
		}
		else
			i++;
	}
	final[j] = NULL;
	return (final);
}

char **ft_split(char const *s, char c)
{
	char **final;
	int i;
	int word;

	i = 0;
	word = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word++;
		i++;
	}
	final = malloc(sizeof(char *) * (word + 1));
	if (!final)
		return (NULL);
	return (ft_splitfill(final, s, c));
}
#pragma endregion

char ***flagbulucu(char **argv) // falagı argüamn olrak al
{
	char ***temp;
	int i;

	i = 1;
	while (argv[i])
		i++;
	temp = malloc(sizeof(char ***) * (i + 1));
	if (!temp)
		return (NULL);
	i = 1;
	while (argv[i])						  // temp herseferinde üzerine yazılıyor ayrı bir pointera at kaybolmasın
	{									  // her seferinde temp[0] temp[1] temp[2] temp[3]
		temp[i] = ft_split(argv[i], ' '); //"adaptive" "1" "2" "3" "4" "5" "6" "7" bunları boşver uc  boyutlşu yaocam
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
int ft_sayiyerlestirme(char ***temp, t_main **arguments2)
{
	int i;
	int j;

	i = 1;

	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (ft_strnstr(temp[i][j], "--", 2))
			{
				j++;
				continue;
			}
			if (!ft_isdigit(temp[i][j][0]))
				return (0);
			ft_lstadd_back(&((*arguments2)->a),
						   ft_lstnew(ft_atoi(temp[i][j])));
			j++;
		}
		i++;
	}

	return (1);
}

int	flagkontrol(char ***temp, t_main **arguments2)
{
	int	i;
	int	j;

	*arguments2 = malloc(sizeof(t_main));
	if (!*arguments2)
		return (0);
	(*arguments2)->fcount = 0;
	(*arguments2)->a = NULL;
	(*arguments2)->b = NULL;
	(*arguments2)->flags = malloc(sizeof(char *) * 3);
	if (!(*arguments2)->flags)
		return (0);
	i = 1;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (ft_strnstr(temp[i][j], "--", 2))
			{
				if ((*arguments2)->fcount == 2)
					return (0);
				(*arguments2)->flags[(*arguments2)->fcount++] = temp[i][j];
			}
			j++;
		}
		i++;
	}
	return (ft_sayiyerlestirme(temp, arguments2));
}

int main(/*int argc, char **argv*/) // hareketleri saymalıyız
{
	char *argv[]={"burayiokumapls","--kalitesizflag","--kaliesizflag","--kaliteliflag","9","2","3", NULL};
	char ***arguments;
	t_main *arguments2 = NULL;
	// argümanları kontrol eden fonksioynu
	/*if (argc < 2)
		return (0);*/
	// if (ft_strnstr(argv[i], "--", 2))
	// alsında split bunların hepsini ayırcak sonra bunu çalıştırcaz
	// flags = argv[i++];

	// printf("%s", flags);
	arguments = flagbulucu(argv);
	// 4 tane string var zaten birde sayılar kontrol edilcek tekrar eden olmıcak printf("Error"); yazdırcak
	if (!flagkontrol(arguments, &arguments2))
	{
		printf("hata\n");
		return (1);//1 nin değeri döenrse terminal hata yazar
	}

	// a = ft_lstnew(atoi(argv[i++]));		 // split kullan "1 2 3" şeklinde kullanıyor

	/*while (i < argc)
	{
		ft_lstadd_back(&a, ft_lstnew(atoi(argv[i++])));
	}*/
	double disorder = compute_disorder(arguments2->a);
	printf("Disorder: %.2f\n", disorder);
	int len = 0;
	t_list *tmp = arguments2->a;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	printf("liste boyu: %d\n", len);
	simple(&arguments2->a, &arguments2->b);

	/*while (a)
	{
		if (a->next != NULL && a->content > (a->next)->content)
		{
			ft_lstswap(&a);
			printf("kosul");
		}

		ft_atob(&a, &b);
	}*/

	while (arguments2->b)
	{
		printf("b stck :%d\n", arguments2->b->content);
		arguments2->b = arguments2->b->next;
	}
	while (arguments2->a)
	{
		printf("a stck :%d\n", arguments2->a->content);
		arguments2->a = arguments2->a->next;
	}
	/*
	while (a)
	{
		printf("%d\n",a->content);
		a = a->next;
	}*/
	// freelist(a);
	// freelist(b);
}