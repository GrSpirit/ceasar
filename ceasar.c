#include "ceasar.h"
#include "utf8.h"

const size_t ALPHABET_NUMBER = 4;
const wchar_t ALPHABET_RANGES[][2] = {
	{0x61, 0x7A},
    {0x41, 0x5A},
    {0x410, 0x42F},
    {0x430, 0x44F}};


int ceasar(char *dst, const char *src, int size, int shift) {
	wchar_t usrc[size];
    wchar_t udst[size];
    size_t usize = utf8_to_unicode(usrc, (const uchar_t*)src, size);

    for (int i = 0; i < usize; ++i) {
        int found = 0;
		for (int j = 0; j < ALPHABET_NUMBER; ++j){
			if (usrc[i] >= ALPHABET_RANGES[j][0] && usrc[i] <= ALPHABET_RANGES[j][1]) {
                int alphabet_length = ALPHABET_RANGES[j][1] - ALPHABET_RANGES[j][0];
                int ushift = shift % alphabet_length;
                if (ushift < 0) 
                    ushift = alphabet_length + ushift;
                udst[i] = (usrc[i] - ALPHABET_RANGES[j][0] + ushift) % alphabet_length + ALPHABET_RANGES[j][0];
                found = 1;
                break;
            }
		}
        if (!found) {
            udst[i] = usrc[i];
        }
    }

    unicode_to_utf8((uchar_t*)dst, udst, usize);
    return 0;
}
