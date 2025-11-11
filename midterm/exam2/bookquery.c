#include <stdio.h>
#include <stdlib.h>
#include "book.h"

int main(int argc, char *argv[])
{
	struct book rec;
	FILE *fp;
	int mode;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s db_filename\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
		return 2;
	}

	printf("0: list of all books, 1: list of available books ) ");
	if (scanf("%d", &mode) != 1) {
		fprintf(stderr, "Error: invalid input\n");
		fclose(fp);
		return 3;
	}

	printf("id bookname author year numofborrow borrow\n");

	while (fread(&rec, sizeof(rec), 1, fp) == 1) {
		if (mode == 1) {
			if (rec.borrow == 0)
				continue;
		}

		printf("%d %s %s %d %d %s\n",
				rec.id,
				rec.bookname,
				rec.author,
				rec.year,
				rec.numofborrow,
				(rec.borrow != 0) ? "True" : "False");
	}

	fclose(fp);
	return 0;
}
