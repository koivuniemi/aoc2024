#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/utils.h"


int scan(const char* const data, int len, const char* const str,
		const int x, const int y, const int width)
{
	if (data[x + y * width] != str[0])
		return 0;
	int count = 0;
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if (dy == 0 && dx == 0)
				continue;
			int is_pattern = 1;
			for (int k = 0; k < strlen(str); k++) {
				int i = x + dx*k + (y + dy*k) * width;
				if (i < 0 || i >= len || data[i] != str[k]) {
					is_pattern = 0;
					break;
				}
			}
			if (is_pattern)
				count++;
		}
	}
	return count;
}

int count(const char* const data, const int len, const char* const str)
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
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width - 1 /* skip newlines */; x++)
			count += scan(data, len, str, x, y, width);
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

	printf("%d\n", count(data, len, "XMAS"));

	free(data);
	return 0;
}
