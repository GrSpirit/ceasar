#include "ceasar.h"
#include "utf8.h"
#include "config.h"

extern alphabet_range alphabets[ALPHABET_MAX_SIZE];
extern size_t alphabet_size;

int ceasar(char *dst, const char *src, int size, int shift) {
	wchar_t usrc[size];
    wchar_t udst[size];
    size_t usize = utf8_to_unicode(usrc, (const uchar_t*)src, size);

    for (int i = 0; i < usize; ++i) {
        int found = 0;
		for (int j = 0; j < alphabet_size; ++j){
			if (usrc[i] >= alphabets[j].start && usrc[i] <= alphabets[j].end) {
                int alphabet_length = alphabets[j].end - alphabets[j].start;
                int ushift = shift % alphabet_length;
                if (ushift < 0) 
                    ushift = alphabet_length + ushift;
                udst[i] = (usrc[i] - alphabets[j].start + ushift) % alphabet_length + alphabets[j].start;
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
