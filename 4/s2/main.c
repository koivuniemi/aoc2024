#include <stdio.h>
#include <stdlib.h>
#include "../lib/utils.h"


int is_mas(const char* const data, const int x, const int y, const int width)
{
	if (data[x + y * width] != 'A')
		return 0;
	const char ne = data[x + 1 + (y - 1) * width];
	const char nw = data[x - 1 + (y - 1) * width];
	const char se = data[x + 1 + (y + 1) * width];
	const char sw = data[x - 1 + (y + 1) * width];
	if ((ne == 'M' && sw == 'S' || ne == 'S' && sw == 'M') &&
	    (nw == 'M' && se == 'S' || nw == 'S' && se == 'M'))
		return 1;
	return 0;
}

int count_mas(const char* const data, const int len)
{
	int width = 0;
	int height = 0;
	while (data[width] != '\n')
		width++;
	width++; // newline
	for (int i = 0; i < len; i++) {
		if (data[i] == '\n')
			height++;
	}
	int count = 0;
	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1 - 1 /* skip newline */; x++) {
			if (is_mas(data, x, y, width))
				count++;
		}
	}
	return count;
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "need input file\n");
		return 1;
	}

	char* data;
	int len = readfile(&data, argv[1]);
	if (len == 0) {
		fprintf(stderr, "file '%s' does not exist\n", argv[1]);
		return 1;
	}

	printf("%d\n", count_mas(data, len));

	free(data);
	return 0;
}
