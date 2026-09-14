#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void swap_ints(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void fill_unique_numbers(int *arr, int count, int max)
{
	int i;

	for (i = 0; i < count; i++)
		arr[i] = i + 1;
	for (i = count - 1; i > 0; i--)
		swap_ints(&arr[i], &arr[rand() % (i + 1)]);
	for (i = 0; i < count; i++)
		arr[i] = (arr[i] % max) + 1;
}

int main(int argc, char **argv)
{
	int count;
	int max;
	int *numbers;
	int i;

	srand((unsigned int)time(NULL));
	if (argc < 2)
	{
		count = 10;
		max = 100;
	}
	else
	{
		count = atoi(argv[1]);
		max = (argc > 2) ? atoi(argv[2]) : count;
	}
	if (count <= 0 || max <= 0)
	{
		fprintf(stderr, "Kullanım: ./generator <adet> [max_deger]\n");
		return (1);
	}
	if (count > max)
	{
		fprintf(stderr, "Hata: adet, max_deger'den büyük olamaz.\n");
		return (1);
	}
	numbers = malloc(sizeof(int) * count);
	if (!numbers)
	{
		fprintf(stderr, "Bellek ayrılma hatası.\n");
		return (1);
	}
	fill_unique_numbers(numbers, count, max);
	for (i = 0; i < count; i++)
	{
		printf("%d", numbers[i]);
		if (i + 1 != count)
			printf(" ");
	}
	printf("\n");
	free(numbers);
	return (0);
}
