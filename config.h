#ifndef CONFIG_H
#define CONFIG_H

#define MAX_FILE_NAME 1024
#define BUFF_SIZE 2048
#define ALPHABET_MAX_SIZE 1024

typedef struct {
	unsigned long start;
	unsigned long end;
} alphabet_range;

int read_alphabet(const char *buff, size_t buff_size);

#endif