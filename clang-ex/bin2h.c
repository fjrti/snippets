#include <stdio.h>
#include <string.h>	/* strncpy */
#include <unistd.h>	/* getopt  */
#include <stdlib.h>	/* strtoul */

int main(int argc, char *argv[])
{
	FILE *input;
	char filename[64], *file_extention;
	int i, c, col = 8, decimal = 0;
	char ch;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file.bin\n", argv[0]);
		return 1;
	}

	input = fopen(argv[1], "rb");
	if (input == NULL) {
		fprintf(stderr, "%s: open binary file %s failed\n", argv[0], argv[1]);
		return 1;
	}

	/* retrieve file name */
	strncpy(filename, argv[1], strlen(argv[1]));
	file_extention = rindex(filename, '.');

	if (file_extention)
		*file_extention = '\0';

	/* options */
	while ((c = getopt(argc, argv, "dl:")) != -1) {
		switch (c) {
		case 'l':
			col = strtoul(optarg, NULL, 10);
			printf("%d %d \n", col, *optarg);
			break;
		case 'd':
			decimal = 1;
			break;
		default:
			break;
		}
	}


	printf("static const unsigned char %s[] = {\n\t", filename);

	for (i = 0; ; i++) {
		ch = fgetc(input);
		if (ch == EOF)
			break;

		if (i != 0)
			printf(",%s", (i % col) ? " " : "\n\t");

		if (decimal)
			printf("%.3d", ch);
		else
			printf("0x%.2x", (unsigned char)ch);
	}

	printf("\n};\n");
	printf("\n#define\t%s_len %d\n", filename, i);

	fclose(input);

	return 0;
}
