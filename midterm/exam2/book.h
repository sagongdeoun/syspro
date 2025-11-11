#ifndef BOOK_H
#define BOOK_H

struct book {
	int id;
	char bookname[30];
	char author[3];
	int year;
	int numofborrow;
	int borrow;
};

#endif
