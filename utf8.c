#include "utf8.h"

size_t utf8_to_unicode(wchar_t *dst, const uchar_t *src, size_t len)
{
	size_t i = 0;
	size_t n = 0;
	size_t k = 0;
	unsigned long x = 0;
	while (i < len) {
		if ((src[i] & 0xF0) == 0xF0) {
			x = src[i] ^ 0xF0;
			n = 4;
		}
		else if ((src[i] & 0xE0) == 0xE0) {
			x = src[i] ^ 0xE0;
			n = 3;
		}
		else if ((src[i] & 0xC0) == 0xC0) {
			x = src[i] ^ 0xC0;
			n = 2;
		}
		else {
			x = src[i];
			n = 1;
		}
		for (size_t j = i + 1; j < i + n; ++j) {
			x <<= 6;
			x |= src[j] ^ 0x80;
		}
		dst[k++] = x;
		i += n;
	}
	dst[k] = 0;
	return k;
}

size_t unicode_to_utf8(uchar_t *dst, const wchar_t *src, size_t len) {
	size_t j = 0;
	size_t n = 0;
	uchar_t buff[4];
	unsigned long x;
	for (size_t i = 0; i < len; ++i) {
		x = src[i];
		if (x & 0xFFFFFF80) {
			j = 0;
			while (x != 0) {
				buff[j] = 0x80 | (x & 0x3F);
				x >>= 6;
				j++;
			}
			buff[j-1] |= 0xFF & (0xF0 << (4-j));
			while (j > 0) {
				dst[n++] = buff[j-1];
				--j;
			}
		}
		else {
			dst[n++] = (uchar_t)x;
		}
	}
	dst[n] = '\0';
	return n;
}
