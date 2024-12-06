#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/utils.h"


int calc(char* data)
{
	int sum = 0;
	while ((data = strstr(data, "mul")) != NULL) {
		data += strlen("mul");
		char c0, c1;
		int n0, n1;
		int r = sscanf(data, "%c%d,%d%c", &c0, &n0, &n1, &c1);
		if (r == 4 && c0 == '(' && c1 == ')')
			sum += n0 * n1;
	}
	return sum;
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "need input file\n");
		return 1;
	}

	char* data = readfile(argv[1]);
	if (data == NULL) {
		fprintf(stderr, "file '%s' does not exist\n", argv[1]);
		return 1;
	}

	printf("%d\n", calc(data));

	free(data);
	return 0;
}
