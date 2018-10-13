#include <stddef.h>
#ifndef uchar_t
typedef unsigned char uchar_t;
#endif

size_t utf8_to_unicode(wchar_t *dst, const uchar_t *src, size_t len);
size_t unicode_to_utf8(uchar_t *dst, const wchar_t *src, size_t len);
