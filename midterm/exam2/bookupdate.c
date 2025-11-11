#include <stdio.h>
#include <stdlib.h>
#include "book.h"

int main(int argc, char *argv[])
{
	struct book rec;
	FILE *fp;
	int mode, id;
	int found = 0;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s db_filename\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "r+b");
	if (fp == NULL) {
		fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
		return 2;
	}

	printf("0 bookId: borrow book, 1 bookId: return book ) ");
	if (scanf("%d %d", &mode, &id) != 2) {
		fprintf(stderr, "Invalid input format.\n");
		fclose(fp);
		return 3;
	}

	while (fread(&rec, sizeof(rec), 1, fp) == 1) {
		if (rec.id == id) {
			found = 1;
			if (mode == 0) {
				if (rec.borrow == 1) {
					printf("You cannat borrow below book since it has been booked.\n");
				} else {
					rec.borrow = 1;
					rec.numofborrow++;
					printf("You've got bellow book.\n");
				}
			} else if (mode == 1) {
				if (rec.borrow == 0) {
					printf("This book is not currently borrowed.\n");
				} else {
					rec.borrow = 0;
					printf("You've returned bellow book.\n");
				}
			} else {
				printf("Invalid mode: use 0 (borrow) or 1 (return).\n");
				fclose(fp);
				return 4;
			}

			fseek(fp, -sizeof(rec), SEEK_CUR);
			fwrite(&rec, sizeof(rec), 1, fp);
			fflush(fp);

			printf("id bookname author year numofborrow borrow\n");
			printf("%d %s %s %d %d %s\n",
					rec.id, rec.bookname, rec.author, rec.year,
					rec.numofborrow, (rec.borrow ? "True" : "False"));
			break;
		}
	}
	if (!found)
		printf("Book ID %d not found.\n", id);

	fclose(fp);
	return 0;
}
