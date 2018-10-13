#include <stdlib.h>
#include "config.h"
#include "utf8.h"

extern alphabet_range alphabets[ALPHABET_MAX_SIZE];
extern size_t alphabet_size;
wchar_t* next_char(wchar_t *ubuff_begin, wchar_t *ubuff_end);

int read_alphabet(const char *buff, size_t buff_size)
{
	wchar_t ubuff[BUFF_SIZE];
	size_t ubuff_size = utf8_to_unicode(ubuff, buff, buff_size);
	wchar_t *char_iter = ubuff;
	while((char_iter = next_char(char_iter, ubuff + ubuff_size)) != NULL) {
		alphabets[alphabet_size].start = *char_iter;
		char_iter++;
		if ((char_iter = next_char(char_iter, ubuff + ubuff_size)) == NULL) {
			return -1;
		}
		alphabets[alphabet_size].end = *char_iter;
		char_iter++;
		alphabet_size++;
	}

	return 0;
}

wchar_t* next_char(wchar_t *ubuff_begin, wchar_t *ubuff_end)
{
	wchar_t c;
	while ((c = *ubuff_begin) != 0 && ubuff_begin < ubuff_end)
	{
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '-') {
			ubuff_begin++;
			continue;
		}
		return ubuff_begin;
	}
	return NULL;
}
