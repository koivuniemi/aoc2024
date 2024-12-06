#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/utils.h"


int calc(char* data)
{
	const char* STR_DO = "do()";
	const char* STR_DONT = "don't()";
	const char* STR_MUL = "mul";
	char cs[] = "dm";
	char c0, c1;
	int n0, n1;
	int sum = 0;
	while ((data = strpbrk(data, cs)) != NULL) {
		if (strncmp(data, STR_DO, strlen(STR_DO)) == 0) {
			strncpy(cs, "dm", 2);
			data += strlen(STR_DO);
			continue;
		}
		if (strncmp(data, STR_DONT, strlen(STR_DONT)) == 0) {
			strncpy(cs, "d\0", 2);
			data += strlen(STR_DONT);
			continue;
		}
		if (strncmp(data, STR_MUL, strlen(STR_MUL)) == 0) {
			data += strlen(STR_MUL);
			int r = sscanf(data, "%c%d,%d%c", &c0, &n0, &n1, &c1);
			if (r == 4 && c0 == '(' && c1 == ')')
				sum += n0 * n1;
			continue;
		}
		data += 1;
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
