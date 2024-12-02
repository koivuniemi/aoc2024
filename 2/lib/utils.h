struct data {
	int* lens;
	int** datas;
};

int scan(struct data* data, char* filename);
int count_safe(const struct data D, const int LEN,
		const int MIN_DIF, const int MAX_DIF, const int TOLERABLE);
