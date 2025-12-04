#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int pid;
	pid = fork();
	if (pid == 0) {
		printf("[Child] : Hello, world pid=%d\n", getpid());
	}
	else if (pid > 0) {
		printf("[Parent] : Hello, world pid=%d\n", getpid());
	}
	else {
		perror("fork error");
	}

	return 0;
}
