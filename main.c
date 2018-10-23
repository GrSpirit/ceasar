#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ceasar.h"
#include "config.h"
#include "utf8.h"

alphabet_range alphabets[ALPHABET_MAX_SIZE];
size_t alphabet_size;

void usage() {
    printf(
        "Usage: ceasar [options]\n"
        "Options:\n"
        "\t-s --shift size          	Shift size.\n"
        "\t-i --input input_file    	Path to input file. If not specified reads from stdin.\n"
        "\t-o --output output_file  	Path to output file. If not specified prints to stdout.\n"
		"\t-a --alphabet alphabet_file	Path to alphabet file. By default latin only.\n\n"
		"\tAphabet file struct:\n"
		"\t\tstart_char1 - end_char1\n"
		"\t\tstart_char2 - end_char2\n"
		"\t\t... - ...\n"
		"\t\tstart_charN - end_charN\n"
		);
}

int main(int argc, char const *argv[])
{
    int shift = 0;
    char input_file[MAX_FILE_NAME] = {0};
    char output_file[MAX_FILE_NAME] = {0};
    char alphabet_file[MAX_FILE_NAME] = {0};
    FILE *ifile;    // Input file
    FILE *ofile;    // Output file
    FILE *afile;    // Alphabet file
    char buff[BUFF_SIZE];
    int buff_len;

    // Parse arguments
    if (argc > 2) {
        for (int i = 1; i < argc; ++i) {
            if (i < (argc - 1) && (!strcmp("-s", argv[i]) || !strcmp("--shift", argv[i]))) {
                shift = strtol(argv[++i], NULL, 10);
            }
            else if (i < (argc - 1) && (!strcmp("-i", argv[i]) || !strcmp("--input", argv[i]))) {
                strncpy(input_file, argv[++i], sizeof(input_file) - 1);
            }
            else if (i < (argc - 1) && (!strcmp("-o", argv[i]) || !strcmp("--output", argv[i]))) {
                strncpy(output_file, argv[++i], sizeof(output_file) - 1);
            }
            else if (i < (argc - 1) && (!strcmp("-a", argv[i]) || !strcmp("--alphabet", argv[i]))) {
                strncpy(alphabet_file, argv[++i], sizeof(output_file) - 1);
			}
        }
    }

    // Check shift size
    if (!shift) {
        usage();
        return -1;
    }

    // Check input file
    if (input_file[0]) {
        ifile = fopen(input_file, "r");
    }
    else {
        ifile = stdin;
    }
    if (!ifile) {
        perror("Cannot open input file");
        return -2;
    }

    // Check output file
    if (output_file[0]) {
        ofile = fopen(output_file, "w");
    }
    else {
        ofile = stdout;
    }
    if (!ofile) {
        perror("Cannot open output file");
        return -3;
    }

    if (alphabet_file[0]) {
        afile = fopen(alphabet_file, "r");
        buff_len = fread(buff, sizeof(char), BUFF_SIZE, afile);
        read_alphabet(buff, buff_len);
        fclose(afile);
    }
    else {
        // English alphabet by default
        alphabets[0].start = 'a';
        alphabets[0].end = 'z';
        alphabets[1].start = 'A';
        alphabets[1].end = 'Z';
        alphabet_size = 2;
    }

    while ((buff_len = fread(buff, sizeof(char), BUFF_SIZE, ifile)) != 0) {
        ceasar(buff, buff, buff_len, shift);
        fwrite(buff, sizeof(char), buff_len, ofile);
    }

    if (ifile != stdin)
        fclose(ifile);
    if (ofile != stdout)
        fclose(ofile);

    return 0;
}
