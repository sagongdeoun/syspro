#include <stdio.h>
#include <stdlib.h>
#include "book.h"

int main(int argc, char *argv[])
{
	struct book rec;
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s db_filename\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1], "wb");
	if (fp == NULL) {
		fprintf(stderr, "File %s Open Error\n", argv[1]);
		exit(2);
	}

	printf("id bookname author year numofborrow borrow(0:False,1:True)\n");

	while (scanf("%d %s %s %d %d %d",
				&rec.id,
				rec.bookname,
				rec.author,
				&rec.year,
				&rec.numofborrow,
				&rec.borrow) == 6)
	{
		fwrite(&rec, sizeof(rec), 1, fp);
	}

	fclose(fp);
	return 0;
}
