#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int cmp_int(const void* n0, const void* n1)
{
	if (*(int*)n0 > *(int*)n1) return 1;
	if (*(int*)n0 < *(int*)n1) return -1;
	return 0;

}

void sort_list(int* list, int len)
{
	qsort(list, len, sizeof(*list), &cmp_int);
}

int scan(int** l0, int** l1, char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (file == NULL)
		return 0;
	fseek(file, 0, SEEK_END);
	int flen = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* fdata = malloc(flen + 1);
	fread(fdata, 1, flen, file);
	fdata[flen] = '\0';
	fclose(file);
	
	int len = 0;
	for (int i = 0; i < flen; i++) {
		if (fdata[i] == '\n')
			len++;
	}

	*l0 = malloc(sizeof(int) * len);
	*l1 = malloc(sizeof(int) * len);
	char* tmp = fdata;
	for (int i = 0; i < len; i++) {
		(*l0)[i] = strtol(tmp, &tmp, 10);
		(*l1)[i] = strtol(tmp, &tmp, 10);
	}

	free(fdata);
	return len;
}
