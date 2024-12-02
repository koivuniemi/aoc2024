#include <stdio.h>
#include <stdlib.h>
#include "../lib/utils.h"

#define MIN_DIF 1
#define MAX_DIF 3
#define TOLERABLE 0


int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "need input file\n");
		return 1;
	}

	struct data data;
	int len = scan(&data, argv[1]);
	if (len == -1) {
		fprintf(stderr, "no such file '%s'\n", argv[1]);
		return 1;
	}

	printf("%d\n", count_safe(data, len, MIN_DIF, MAX_DIF, TOLERABLE));

	for (int i = 0; i < len; i++)
		free(data.datas[i]);
	free(data.lens);
	free(data.datas);
	return 0;
}
