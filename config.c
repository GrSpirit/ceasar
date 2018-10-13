#include "config.h"

int read_alphabet(const char *file_name, alphabet_range *range, size_t range_size)
{
	FILE *afile;
	if (!(afile = fopen(file_name, "r")))
	{
		return -1;
	}


	return 0;
}

int next_char(FILE *afile)
{
	int c;
	while ((c = fgetc(afile)) != EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '-') continue;
		return c;
	}
	return EOF;
}
