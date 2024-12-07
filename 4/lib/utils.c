#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int readfile(char** dest, char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (file == NULL)
		return 0;
	fseek(file, 0, SEEK_END);
	int len = ftell(file);
	fseek(file, 0, SEEK_SET);
	*dest = malloc(len);
	fread(*dest, 1, len, file);
	fclose(file);
	return len;
}
