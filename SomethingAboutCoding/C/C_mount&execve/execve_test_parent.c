#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int j;
	char *newargv[] = { NULL, "hello", "world", NULL };
	char *newenviron[] = { NULL };
	
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	for (j = 0; j < argc; j++)
		printf("[PARENT]: argv[%d]: %s\n", j, argv[j]);
	newargv[0] = argv[1];
	printf("[PARENT]: before execve \n");
	execve(argv[1], newargv, newenviron);
	printf("[PARENT]: after execve \n");
	perror("execve");   /* execve() only returns on error */
	exit(EXIT_FAILURE);
}
