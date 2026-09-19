#include <unistd.h>

void	ft_error(void)
{
	write(2, "Error\n", 6);
}