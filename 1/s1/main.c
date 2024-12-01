#include <stdio.h>
#include <stdlib.h>
#include "../lib/utils.h"


int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "input file needed\n");
		return 1;
	}
	
	int* list0;
	int* list1;
	int len = scan(&list0, &list1, argv[1]);

	sort_list(list0, len);
	sort_list(list1, len);

	int distance = 0;
	for (int i = 0; i < len; i++)
		distance += abs(list0[i] - list1[i]);

	printf("%d\n", distance);

	free(list0);
	free(list1);
	return 0;
}
