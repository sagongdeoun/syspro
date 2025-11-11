#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	int ch;
	int option;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s option source_file dest_file\n", argv[0]);
		return 1;
	}

	option = atoi(argv[1]);
	if (option < 0 || option > 2) {
		fprintf(stderr, "Error: option must be 0, 1, or 2\n");
		return 1;
	}

	fp1 = fopen(argv[2], "r");
	if (fp1 == NULL) {
		fprintf(stderr, "Error:  cannot open source file %s\n", argv[2]);
		return 2;
	}

	fp2 = fopen(argv[3], "w");
	if (fp2 == NULL) {
		fprintf(stderr, "Error: cannot open destination file %s\n", argv[3]);
		fclose(fp1);
		return 3;
	}

	while ((ch = fgetc(fp1)) != EOF) {
		if (option == 1) {
			if (ch >= 'A' && ch <= 'Z')
				ch = ch - 'A' + 'a';
		}
		else if (option == 2) {
			if (ch >= 'a' && ch <= 'z')
				ch = ch - 'a' + 'A';
		}

		if (fputc(ch, fp2) == EOF) {
			fprintf(stderr, "Error\n");
			fclose(fp1);
			fclose(fp2);
			return 4;
		}
	}

	if (ferror(fp1)) {
		fprintf(stderr, "Error\n");
		fclose(fp1);
		fclose(fp2);
		return 5;
	}

	fclose(fp1);
	fclose(fp2);

	fp2 = fopen(argv[3], "r");
	if (fp2 == NULL) {
		fprintf(stderr, "Error: cannot re-open destination file %s\n", argv[3]);
		return 6;
	}

	while ((ch = fgetc(fp2)) != EOF)
		putchar(ch);

	fclose(fp2);

	return 0;
}
