# ceasar

Usage: ceasar [options]

	Options:
		-s --shift size          	Shift size.
		-i --input input_file    	Path to input file. If not specified reads from stdin.
		-o --output output_file  	Path to output file. If not specified prints to stdout.
		-a --alphabet alphabet_file	Path to alphabet file. By default latin only.
	
		Aphabet file struct:
			start_char1 - end_char1
			start_char2 - end_char2
			... - ...
			start_charN - end_charN
