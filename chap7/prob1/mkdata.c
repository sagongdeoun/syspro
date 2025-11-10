#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[])
{
	int fd;
	struct student record;

	if (argc < 2) {
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) == -1) {
		perror(argv[1]);
		exit(2);
	}
	printf("%-9s %-8s %-4s\n", "StuID", "Name", "Score");

	while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3) {
		off_t off = (off_t)(record.id - START_ID) * (off_t)sizeof(record);
		if (lseek(fd, off, SEEK_SET) == (off_t)-1) {
			perror("lseek");
			close(fd);
			exit(3);
		}
		if (write(fd, (char *)&record, sizeof(record)) != sizeof(record)) {
			perror("write");
			close(fd);
			exit(4);
		}
	}

	close(fd);
	exit(0);
}
