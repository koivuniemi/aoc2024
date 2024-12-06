#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

char* readfile(char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (file == NULL)
		return NULL;
	fseek(file, 0, SEEK_END);
	int flen = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* fdata = malloc(flen + 1);
	fread(fdata, 1, flen, file);
	fdata[flen] = '\0';
	fclose(file);
	return fdata;
}
