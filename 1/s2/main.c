#include <stdio.h>
#include <stdlib.h>
#include "../lib/utils.h"


int count_sorted(int* list, int len, int elem)
{
	int* p = bsearch(&elem, list, len, sizeof(*list), cmp_int);
	if (p == NULL)
		return 0;

	while (p > list && *(p - 1) == elem)
		p--;

	int count = 0; 
	while (p < list + len && *p == elem) {
		count++;
		p++;
	}

	return count;
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "need input file\n");
		return 1;
	}

	int* list0;
	int* list1;
	int len = scan(&list0, &list1, argv[1]);

	sort_list(list1, len);

	int similarity_score = 0;
	for (int i = 0; i < len; i++)
		similarity_score += list0[i] * count_sorted(list1, len, list0[i]);

	printf("%d\n", similarity_score);

	free(list0);
	free(list1);
	return 0;
}
