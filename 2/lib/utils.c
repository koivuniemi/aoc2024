#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


int scan(struct data* data, char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (file == NULL)
		return -1;
	fseek(file, 0, SEEK_END);
	int flen = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* fdata = malloc(flen + 1);
	fread(fdata, 1, flen, file);
	fdata[flen] = '\0';
	fclose(file);

	char* tmp = fdata;
	int line_len = 0;
	for (tmp = fdata; *tmp != '\0'; tmp++) {
		if (*tmp == '\n')
			line_len++;
	}
	data->lens = malloc(sizeof(int*[line_len]));
	data->datas = malloc(sizeof(int**[line_len]));

	int tmp_data[200];
	char* line = strtok(fdata, "\n");
	for (int i = 0; i < line_len; i++) {
		int len = 0;
		while (*line != '\0')
			tmp_data[len++] = strtol(line, &line, 10);
		data->lens[i] = len;
		data->datas[i] = malloc(sizeof(int[len]));
		memcpy(data->datas[i], tmp_data, sizeof(int[len]));
		line = strtok(NULL, "\n");
	}

	free(fdata);
	return line_len;
}

// returns -1 if is safe, else returns index where error occured
int is_safe(const int* D, const int LEN, int min_dif, int max_dif)
{
	if (D[0] > D[1]) {
		int tmp_min_dif = min_dif;
		min_dif = -max_dif;
		max_dif = -tmp_min_dif;
	}
	for (int i = 0; i < LEN - 1; i++) {
		int diff = D[i + 1] - D[i];
		if (diff < min_dif || diff > max_dif)
			return i;
	}
	return -1;
}

static inline void delete(int* data, const int LEN, const int INDEX)
{
	memmove(data + INDEX, data + INDEX + 1, sizeof(int) * (LEN - INDEX - 1));
}

int count_safe(const struct data D, const int LEN, const int MIN_DIF, const int MAX_DIF, const int TOLERABLE)
{
	int count = LEN;
	for (int i = 0; i < LEN; i++) {
		int index = is_safe(D.datas[i], D.lens[i], MIN_DIF, MAX_DIF);
		if (index == -1)
			continue;
		if (TOLERABLE) {
			int tmp[50];
			int tmp_len = D.lens[i] - 1;
			if (index == 1) {
				memcpy(tmp, D.datas[i], sizeof(int) * D.lens[i]);
				delete(tmp, D.lens[i], index - 1);
				if (is_safe(tmp, tmp_len, MIN_DIF, MAX_DIF) == -1)
					continue;
			}
			memcpy(tmp, D.datas[i], sizeof(int) * D.lens[i]);
			delete(tmp, D.lens[i], index);
			if (is_safe(tmp, tmp_len, MIN_DIF, MAX_DIF) == -1)
				continue;
			memcpy(tmp, D.datas[i], sizeof(int) * D.lens[i]);
			delete(tmp, D.lens[i], index + 1); 
			if (is_safe(tmp, tmp_len, MIN_DIF, MAX_DIF) == -1)
				continue;
		}
		count--;
	}
	return count;
}
